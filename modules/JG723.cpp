#include "JG723.h"
#include "JLinkObj.h"
#include "JIntegerData.h"
#include "JMath.h"

JG723State::JG723State() {
  int cnta;
  yl = 34816;
  yu = 544;
  dms = 0;
  dml = 0;
  ap = 0;
  for (cnta = 0; cnta < 2; cnta++) {
    a[cnta] = 0;
    pk[cnta] = 0;
    sr[cnta] = 32;
  }
  for (cnta = 0; cnta < 6; cnta++) {
    b[cnta] = 0;
    dq[cnta] = 32;
  }
  td = 0;
  prev = 0;
}

const char* JG723::className() const { return "JG723";}
JObject* JG723::clone() const { return new JG723(*this);}

static short power2[15] = {1, 2, 4, 8, 0x10, 0x20, 0x40, 0x80,
  0x100, 0x200, 0x400, 0x800, 0x1000, 0x2000, 0x4000};

/*
 * quantizes the input val against the table of size short integers.
 * It returns i if table[i - 1] <= val < table[i].
 * Using linear search for simple coding.
 */
int JG723::quan(int val, short *table, int size) {
  int i;
  for (i = 0; i < size; i++)
    if (val < *table++)	break;
  return (i);
}

/*
 * returns the integer product of the 14-bit integer "an" and
 * "floating point" representation (4-bit exponent, 6-bit mantessa) "srn".
 */
int JG723::fmult(int an, int srn) {
  short anmag, anexp, anmant;
  short wanexp, wanmant;
  short retval;
  anmag = (an > 0) ? an : ((-an) & 0x1FFF);
  anexp = quan(anmag, power2, 15) - 6;
  anmant = (anmag == 0) ? 32 :
    (anexp >= 0) ? anmag >> anexp : anmag << -anexp;
  wanexp = anexp + ((srn >> 6) & 0xF) - 13;
  wanmant = (anmant * (srn & 077) + 0x30) >> 4;
  retval = (wanexp >= 0) ? ((wanmant << wanexp) & 0x7FFF) :
    (wanmant >> -wanexp);
  return (((an ^ srn) < 0) ? -retval : retval);
}

/*
 * computes the estimated signal from 6-zero predictor.
 */
int JG723::predictor_zero(JG723State &state) {
  int sezi = fmult(state.b[0] >> 2, state.dq[0]);
  for (int i = 1; i < 6; i++) /* ACCUM */
    sezi += fmult(state.b[i] >> 2, state.dq[i]);
  return (sezi);
}

/*
 * computes the estimated signal from 2-pole predictor.
 */
int JG723::predictor_pole(JG723State &state) {
  return (fmult(state.a[1] >> 2, state.sr[1]) +
    fmult(state.a[0] >> 2, state.sr[0]));
}

/*
 * computes the quantization step size of the adaptive quantizer.
 */
int JG723::step_size(JG723State &state) {
  if (state.ap >= 256) return (state.yu);
  int y = state.yl >> 6;
  int dif = state.yu - y;
  int al = state.ap >> 2;
  if (dif > 0)
    y += (dif * al) >> 6;
  else if (dif < 0)
    y += (dif * al + 0x3F) >> 6;
  return (y);
}

/*
 * Given a raw sample, 'd', of the difference signal and a
 * quantization step size scale factor, 'y', this routine returns the
 * ADPCM codeword to which that sample gets quantized.  The step
 * size scale factor division operation is done in the log base 2 domain
 * as a subtraction.
 */
int JG723::quantize(int d, int y, short *table, int size) {
  short	dqm;	/* Magnitude of 'd' */
  short	exp;	/* Integer part of base 2 log of 'd' */
  short	mant;	/* Fractional part of base 2 log */
  short	dl;	/* Log of magnitude of 'd' */
  short	dln;	/* Step size scale factor normalized log */
  int	i;
  dqm = jabs(d);
  exp = quan(dqm >> 1, power2, 15);
  mant = ((dqm << 7) >> exp) & 0x7F;
  dl = (exp << 7) + mant;
  dln = dl - (y >> 2);
  i = quan(dln, table, size);
  if (d < 0) return ((size << 1) + 1 - i);
  else if (i == 0) return ((size << 1) + 1);
  else return (i);
}

/*
 * Returns reconstructed difference signal 'dq' obtained from
 * codeword 'i' and quantization step size scale factor 'y'.
 * Multiplication is performed in log base 2 domain as addition.
 */
int JG723::reconstruct(int sign, int dqln, int y) {
  short dql = dqln + (y >> 2);	/* ADDA */
  if (dql < 0) return ((sign) ? -0x8000 : 0);
  short dex = (dql >> 7) & 15;
  short dqt = 128 + (dql & 127);
  short dq = (dqt << 7) >> (14 - dex);
  return ((sign) ? (dq - 0x8000) : dq);
}

/*
 * updates the state variables for each output code
 */
void JG723::update(int code_size, int y, int wi, int fi, int dq,
  int sr, int dqsez, JG723State &state) {
  int cnt;
  short	mag, exp;	/* Adaptive predictor, FLOAT A */
  short	a2p;		/* LIMC */
  short	a1ul;		/* UPA1 */
  short	pks1;	/* UPA2 */
  short	fa1;
  char	tr;		/* tone/transition detector */
  short	ylint, thr2, dqthr;
  short	ylfrac, thr1;
  short	pk0;
  pk0 = (dqsez < 0) ? 1 : 0;	/* needed in updating predictor poles */
  mag = dq & 0x7FFF;		/* prediction difference magnitude */
  /* TRANS */
  ylint = (short)(state.yl >> 15); /* exponent part of yl */
  ylfrac = (short)(state.yl >> 10) & 0x1F;	/* fractional part of yl */
  thr1 = (32 + ylfrac) << ylint;		/* threshold */
  thr2 = (short)((ylint > 9) ? 31 << 10 : thr1);	/* limit thr2 to 31 << 10 */
  dqthr = (thr2 + (thr2 >> 1)) >> 1;	/* dqthr = 0.75 * thr2 */
  if (state.td == 0)		/* signal supposed voice */
    tr = 0;
  else if (mag <= dqthr)		/* supposed data, but small mag */
    tr = 0;			/* treated as voice */
  else				/* signal is data (modem) */
    tr = 1;
  /*
   * Quantizer scale factor adaptation.
   */
  /* FUNCTW & FILTD & DELAY */
  /* update non-steady state step size multiplier */
  state.yu = y + ((wi - y) >> 5);
  /* LIMB */
  if (state.yu < 544)	/* 544 <= yu <= 5120 */
    state.yu = 544;
  else if (state.yu > 5120)
    state.yu = 5120;
  /* FILTE & DELAY */
  /* update steady state step size multiplier */
  state.yl += state.yu + ((-state.yl) >> 6);
  /*
   * Adaptive predictor coefficients.
   */
  if (tr == 1) { /* reset a's and b's for modem signal */
    state.a[0] = 0;
    state.a[1] = 0;
    state.b[0] = 0;
    state.b[1] = 0;
    state.b[2] = 0;
    state.b[3] = 0;
    state.b[4] = 0;
    state.b[5] = 0;
  } else {	/* update a's and b's */
    pks1 = pk0 ^ state.pk[0];		/* UPA2 */
    /* update predictor pole a[1] */
    a2p = state.a[1] - (state.a[1] >> 7);
    if (dqsez != 0) {
      fa1 = (pks1) ? state.a[0] : -state.a[0];
      if (fa1 < -8191)	/* a2p = function of fa1 */
	a2p -= 0x100;
      else if (fa1 > 8191)
        a2p += 0xFF;
      else
	a2p += fa1 >> 5;
      if (pk0 ^ state.pk[1])
      /* LIMC */
	if (a2p <= -12160)
  	  a2p = -12288;
	else if (a2p >= 12416)
	  a2p = 12288;
	else
	  a2p -= 0x80;
      else if (a2p <= -12416)
	a2p = -12288;
      else if (a2p >= 12160)
	a2p = 12288;
      else
	a2p += 0x80;
    }
    /* TRIGB & DELAY */
    state.a[1] = a2p;
    /* UPA1 */
    /* update predictor pole a[0] */
    state.a[0] -= state.a[0] >> 8;
    if (dqsez != 0)
      if (pks1 == 0)
 	state.a[0] += 192;
      else
	state.a[0] -= 192;
      /* LIMD */
    a1ul = 15360 - a2p;
    if (state.a[0] < -a1ul)
      state.a[0] = -a1ul;
    else if (state.a[0] > a1ul)
      state.a[0] = a1ul;
    /* UPB : update predictor zeros b[6] */
    for (cnt = 0; cnt < 6; cnt++) {
      if (code_size == 5) /* for 40Kbps G.723 */
 	state.b[cnt] -= state.b[cnt] >> 9;
      else /* for G.721 and 24Kbps G.723 */
	state.b[cnt] -= state.b[cnt] >> 8;
      if (dq & 0x7FFF) {			/* XOR */
	if ((dq ^ state.dq[cnt]) >= 0)
  	  state.b[cnt] += 128;
	else
	  state.b[cnt] -= 128;
      }
    }
  }
  for (cnt = 5; cnt > 0; cnt--)
    state.dq[cnt] = state.dq[cnt-1];
  /* FLOAT A : convert dq[0] to 4-bit exp, 6-bit mantissa f.p. */
  if (mag == 0) {
    state.dq[0] = (dq >= 0) ? 0x20 : 0xFC20;
  } else {
    exp = quan(mag, power2, 15);
    state.dq[0] = (dq >= 0) ?
      (exp << 6) + ((mag << 6) >> exp) :
      (exp << 6) + ((mag << 6) >> exp) - 0x400;
  }
  state.sr[1] = state.sr[0];
  /* FLOAT B : convert sr to 4-bit exp., 6-bit mantissa f.p. */
  if (sr == 0) {
    state.sr[0] = 0x20;
  } else if (sr > 0) {
    exp = quan(sr, power2, 15);
    state.sr[0] = (exp << 6) + ((sr << 6) >> exp);
  } else if (sr > -32768) {
    mag = -sr;
    exp = quan(mag, power2, 15);
    state.sr[0] =  (exp << 6) + ((mag << 6) >> exp) - 0x400;
  } else
    state.sr[0] = (short)0xFC20;
  /* DELAY A */
  state.pk[1] = state.pk[0];
  state.pk[0] = pk0;
  /* TONE */
  if (tr == 1)		/* this sample has been treated as data */
    state.td = 0;	/* next one will be treated as voice */
  else if (a2p < -11776)	/* small sample-to-sample correlation */
    state.td = 1;	/* signal may be data */
  else				/* signal is voice */
    state.td = 0;
  /*
   * Adaptation speed control.
   */
  state.dms += (fi - state.dms) >> 5;		/* FILTA */
  state.dml += (((fi << 2) - state.dml) >> 7);	/* FILTB */
  if (tr == 1)
    state.ap = 256;
  else if (y < 1536) /* SUBTC */
    state.ap += (0x200 - state.ap) >> 4;
  else if (state.td == 1)
    state.ap += (0x200 - state.ap) >> 4;
  else if (jabs((state.dms << 2) - state.dml) >= (state.dml >> 3))
    state.ap += (0x200 - state.ap) >> 4;
  else
    state.ap += (-state.ap) >> 4;
}

/*
 * At the end of ADPCM decoding, it simulates an encoder which may be receiving
 * the output of this decoder as a tandem process. If the output of the
 * simulated encoder differs from the input to this decoder, the decoder output
 * is adjusted by one level of A-law or u-law codes.
 *
 * Input:
 *	sr	decoder output linear PCM sample,
 *	se	predictor estimate sample,
 *	y	quantizer step size,
 *	i	decoder input code,
 *	sign	sign bit of code i
 *
 * Return:
 *	adjusted A-law or u-law compressed sample.
 */
int JG723::tandem_adjust_alaw(int sr, int se, int y, int i, int sign, short *qtab) {
  unsigned char	sp;	/* A-law compressed 8-bit code */
  short		dx;	/* prediction error */
  char		id;	/* quantized prediction error */
  int		sd;	/* adjusted A-law decoded sample value */
  int		im;	/* biased magnitude of i */
  int		imx;	/* biased magnitude of id */
  if (sr <= -32768) sr = -1;
  sp = linear2alaw((sr >> 1) << 3);	/* short to A-law compression */
  dx = (alaw2linear(sp) >> 2) - se;	/* 16-bit prediction error */
  id = quantize(dx, y, qtab, sign - 1);
  if (id == i) return (sp);
  /* ADPCM codes : 8, 9, ... F, 0, 1, ... , 6, 7 */
  im = i ^ sign;    /* 2's complement to biased unsigned */
  imx = id ^ sign;
  if (imx > im) {   /* sp adjusted to next lower value */
    if (sp & 0x80) {
      sd = (sp == 0xD5) ? 0x55 :
      ((sp ^ 0x55) - 1) ^ 0x55;
    } else {
      sd = (sp == 0x2A) ? 0x2A :
      ((sp ^ 0x55) + 1) ^ 0x55;
    }
  } else {  /* sp adjusted to next higher value */
    if (sp & 0x80)
      sd = (sp == 0xAA) ? 0xAA : ((sp ^ 0x55) + 1) ^ 0x55;
    else
      sd = (sp == 0x55) ? 0xD5 : ((sp ^ 0x55) - 1) ^ 0x55;
  }
  return (sd);
}

int JG723::tandem_adjust_ulaw(int sr, int se, int y, int i, int sign, short *qtab) {
  unsigned char	sp;	/* u-law compressed 8-bit code */
  short		dx;	/* prediction error */
  char		id;	/* quantized prediction error */
  int		sd;	/* adjusted u-law decoded sample value */
  int		im;	/* biased magnitude of i */
  int		imx;	/* biased magnitude of id */
  if (sr <= -32768)
    sr = 0;
  sp = linear2ulaw(sr << 2);	/* short to u-law compression */
  dx = (ulaw2linear(sp) >> 2) - se;	/* 16-bit prediction error */
  id = quantize(dx, y, qtab, sign - 1);
  if (id == i) return (sp);
  /* ADPCM codes : 8, 9, ... F, 0, 1, ... , 6, 7 */
  im = i ^ sign;  /* 2's complement to biased unsigned */
  imx = id ^ sign;
  if (imx > im) {  /* sp adjusted to next lower value */
    if (sp & 0x80)
      sd = (sp == 0xFF) ? 0x7E : sp + 1;
    else
      sd = (sp == 0) ? 0 : sp - 1;
  } else {  /* sp adjusted to next higher value */
    if (sp & 0x80)
      sd = (sp == 0x80) ? 0x80 : sp - 1;
    else
      sd = (sp == 0x7F) ? 0xFE : sp + 1;
  }
  return (sd);
}

/*
 * g711.c
 *
 * u-law, A-law and linear PCM conversions.
 */
#define	SIGN_BIT	(0x80)		/* Sign bit for a A-law byte. */
#define	QUANT_MASK	(0xf)		/* Quantization field mask. */
#define	NSEGS		(8)		/* Number of A-law segments. */
#define	SEG_SHIFT	(4)		/* Left shift for segment number. */
#define	SEG_MASK	(0x70)		/* Segment field mask. */

static short seg_end[8] = {0xFF, 0x1FF, 0x3FF, 0x7FF,
  0xFFF, 0x1FFF, 0x3FFF, 0x7FFF};

/* copy from CCITT G.711 specifications */
unsigned char _u2a[128] = {			/* u- to A-law conversions */
	1,	1,	2,	2,	3,	3,	4,	4,
	5,	5,	6,	6,	7,	7,	8,	8,
	9,	10,	11,	12,	13,	14,	15,	16,
	17,	18,	19,	20,	21,	22,	23,	24,
	25,	27,	29,	31,	33,	34,	35,	36,
	37,	38,	39,	40,	41,	42,	43,	44,
	46,	48,	49,	50,	51,	52,	53,	54,
	55,	56,	57,	58,	59,	60,	61,	62,
	64,	65,	66,	67,	68,	69,	70,	71,
	72,	73,	74,	75,	76,	77,	78,	79,
	81,	82,	83,	84,	85,	86,	87,	88,
	89,	90,	91,	92,	93,	94,	95,	96,
	97,	98,	99,	100,	101,	102,	103,	104,
	105,	106,	107,	108,	109,	110,	111,	112,
	113,	114,	115,	116,	117,	118,	119,	120,
	121,	122,	123,	124,	125,	126,	127,	128};

unsigned char _a2u[128] = {			/* A- to u-law conversions */
	1,	3,	5,	7,	9,	11,	13,	15,
	16,	17,	18,	19,	20,	21,	22,	23,
	24,	25,	26,	27,	28,	29,	30,	31,
	32,	32,	33,	33,	34,	34,	35,	35,
	36,	37,	38,	39,	40,	41,	42,	43,
	44,	45,	46,	47,	48,	48,	49,	49,
	50,	51,	52,	53,	54,	55,	56,	57,
	58,	59,	60,	61,	62,	63,	64,	64,
	65,	66,	67,	68,	69,	70,	71,	72,
	73,	74,	75,	76,	77,	78,	79,	79,
	80,	81,	82,	83,	84,	85,	86,	87,
	88,	89,	90,	91,	92,	93,	94,	95,
	96,	97,	98,	99,	100,	101,	102,	103,
	104,	105,	106,	107,	108,	109,	110,	111,
	112,	113,	114,	115,	116,	117,	118,	119,
	120,	121,	122,	123,	124,	125,	126,	127};

int JG723::search(int val, short *table, int size) {
  for (int i = 0; i < size; i++)
    if (val <= *table++) return (i);
  return (size);
}

/*
 * linear2alaw() - Convert a 16-bit linear PCM value to 8-bit A-law
 *
 * linear2alaw() accepts an 16-bit integer and encodes it as A-law data.
 *
 *		Linear Input Code	Compressed Code
 *	------------------------	---------------
 *	0000000wxyza			000wxyz
 *	0000001wxyza			001wxyz
 *	000001wxyzab			010wxyz
 *	00001wxyzabc			011wxyz
 *	0001wxyzabcd			100wxyz
 *	001wxyzabcde			101wxyz
 *	01wxyzabcdef			110wxyz
 *	1wxyzabcdefg			111wxyz
 *
 * For further information see John C. Bellamy's Digital Telephony, 1982,
 * John Wiley & Sons, pps 98-111 and 472-476.
 */
unsigned char JG723::linear2alaw(int pcm_val) {
  int		mask;
  int		seg;
  unsigned char	aval;
  if (pcm_val >= 0) {
    mask = 0xD5;		/* sign (7th) bit = 1 */
  } else {
    mask = 0x55;		/* sign bit = 0 */
    pcm_val = -pcm_val - 8;
  }
  /* Convert the scaled magnitude to segment number. */
  seg = search(pcm_val, seg_end, 8);
  /* Combine the sign, segment, and quantization bits. */
  if (seg >= 8)		/* out of range, return maximum value. */
    return (0x7F ^ mask);
  else {
    aval = seg << SEG_SHIFT;
    if (seg < 2)
      aval |= (pcm_val >> 4) & QUANT_MASK;
    else
      aval |= (pcm_val >> (seg + 3)) & QUANT_MASK;
    return (aval ^ mask);
  }
}

/*
 * alaw2linear() - Convert an A-law value to 16-bit linear PCM
 */
int JG723::alaw2linear(unsigned char a_val) {
  int t;
  int seg;
  a_val ^= 0x55;
  t = (a_val & QUANT_MASK) << 4;
  seg = ((unsigned)a_val & SEG_MASK) >> SEG_SHIFT;
  switch (seg) {
    case 0:
      t += 8;
      break;
    case 1:
      t += 0x108;
      break;
    default:
      t += 0x108;
      t <<= seg - 1;
  }
  return ((a_val & SIGN_BIT) ? t : -t);
}

#define	BIAS		(0x84)		/* Bias for linear code. */

/*
 * In order to simplify the encoding process, the original linear magnitude
 * is biased by adding 33 which shifts the encoding range from (0 - 8158) to
 * (33 - 8191). The result can be seen in the following encoding table:
 *
 *	Biased Linear Input Code	Compressed Code
 *	------------------------	---------------
 *	00000001wxyza			000wxyz
 *	0000001wxyzab			001wxyz
 *	000001wxyzabc			010wxyz
 *	00001wxyzabcd			011wxyz
 *	0001wxyzabcde			100wxyz
 *	001wxyzabcdef			101wxyz
 *	01wxyzabcdefg			110wxyz
 *	1wxyzabcdefgh			111wxyz
 *
 * Each biased linear code has a leading 1 which identifies the segment
 * number. The value of the segment number is equal to 7 minus the number
 * of leading 0's. The quantization interval is directly available as the
 * four bits wxyz.  * The trailing bits (a - h) are ignored.
 *
 * Ordinarily the complement of the resulting code word is used for
 * transmission, and so the code word is complemented before it is returned.
 *
 * For further information see John C. Bellamy's Digital Telephony, 1982,
 * John Wiley & Sons, pps 98-111 and 472-476.
 */
unsigned char JG723::linear2ulaw(int pcm_val) {
  int mask;
  int seg;
  unsigned char	uval;
  /* Get the sign and the magnitude of the value. */
  if (pcm_val < 0) {
    pcm_val = BIAS - pcm_val;
    mask = 0x7F;
  } else {
    pcm_val += BIAS;
    mask = 0xFF;
  }
  /* Convert the scaled magnitude to segment number. */
  seg = search(pcm_val, seg_end, 8);
  /*
   * Combine the sign, segment, quantization bits;
   * and complement the code word.
   */
  if (seg >= 8) return (0x7F ^ mask);
  uval = (seg << 4) | ((pcm_val >> (seg + 3)) & 0xF);
  return (uval ^ mask);
}

/*
 * First, a biased linear code is derived from the code word. An unbiased
 * output can then be obtained by subtracting 33 from the biased code.
 *
 * Note that this function expects to be passed the complement of the
 * original code word. This is in keeping with ISDN conventions.
 */
int JG723::ulaw2linear(unsigned char u_val) {
  int t;
  /* Complement to obtain normal u-law value. */
  u_val = ~u_val;
  /*
   * Extract and bias the quantization bits. Then
   * shift up by the segment number and subtract out the bias.
   */
  t = ((u_val & QUANT_MASK) << 3) + BIAS;
  t <<= ((unsigned)u_val & SEG_MASK) >> SEG_SHIFT;
  return ((u_val & SIGN_BIT) ? (BIAS - t) : (t - BIAS));
}

/* A-law to u-law conversion */
unsigned char JG723::alaw2ulaw(unsigned char aval) {
  aval &= 0xff;
  return ((aval & 0x80) ? (0xFF ^ _a2u[aval ^ 0xD5]) :
    (0x7F ^ _a2u[aval ^ 0x55]));
}

/* u-law to A-law conversion */
unsigned char JG723::ulaw2alaw(unsigned char uval) {
  uval &= 0xff;
  return ((uval & 0x80) ? (0xD5 ^ (_u2a[0xFF ^ uval] - 1)) :
    (0x55 ^ (_u2a[0x7F ^ uval] - 1)));
}

static short qtab4[7] = {-124, 80, 178, 246, 300, 349, 400};
/*
 * Maps G.721 code word to reconstructed scale factor normalized log
 * magnitude values.
 */
static short _dqlntab4[16] = {
  -2048, 4, 135, 213, 273, 323, 373, 425,
  425, 373, 323, 273, 213, 135, 4, -2048};

/* Maps G.721 code word to log of scale factor multiplier. */
static short _witab4[16] = {
  -12, 18, 41, 64, 112, 198, 355, 1122,
  1122, 355, 198, 112, 64, 41, 18, -12};
/*
 * Maps G.721 code words to a set of values whose long and short
 * term averages are computed and then compared to give an indication
 * how stationary (steady state) the signal is.
 */
static short _fitab4[16] = {
  0, 0, 0, 0x200, 0x200, 0x200, 0x600, 0xE00,
  0xE00, 0x600, 0x200, 0x200, 0x200, 0, 0, 0};

/*
 * Encodes the input vale of linear PCM, A-law or u-law data sl and returns
 * the resulting code. -1 is returned for unknown input coding value.
 */
short JG723::encode4(int sl, int in_coding, JG723State &state) {
  short sezi, se, sez;	/* ACCUM */
  short	d;		/* SUBTA */
  short	sr;		/* ADDB */
  short	y;		/* MIX */
  short	dqsez;		/* ADDC */
  short	dq, i;
  switch (in_coding) {	/* linearize input sample to 14-bit PCM */
    case ALAW:
      sl = alaw2linear(sl) >> 2;
      break;
    case ULAW:
      sl = ulaw2linear(sl) >> 2;
      break;
    case LINEAR:
      sl >>= 2;			/* 14-bit dynamic range */
      break;
    default:
      return (-1);
  }
  sezi = predictor_zero(state);
  sez = sezi >> 1;
  se = (sezi + predictor_pole(state)) >> 1;	/* estimated signal */
  d = sl - se;				/* estimation difference */
  /* quantize the prediction difference */
  y = step_size(state);		/* quantizer step size */
  i = quantize(d, y, qtab4, 7);	/* i = ADPCM code */
  dq = reconstruct(i & 8, _dqlntab4[i], y);	/* quantized est diff */
  sr = (dq < 0) ? se - (dq & 0x3FFF) : se + dq;	/* reconst. signal */
  dqsez = sr + sez - se;			/* pole prediction diff. */
  update(4, y, _witab4[i] << 5, _fitab4[i], dq, sr, dqsez, state);
  return (i);
}

/*
 * Decodes a 4-bit code of G.721 encoded data of i and
 * returns the resulting linear PCM, A-law or u-law value.
 * return -1 for unknown out_coding value.
 */
short JG723::decode4(int i, int out_coding, JG723State &state) {
  short	sezi, sei, sez, se;	/* ACCUM */
  short	y;			/* MIX */
  short	sr;			/* ADDB */
  short	dq;
  short	dqsez;
  i &= 0x0f;			/* mask to get proper bits */
  sezi = predictor_zero(state);
  sez = sezi >> 1;
  sei = sezi + predictor_pole(state);
  se = sei >> 1;			/* se = estimated signal */
  y = step_size(state);	/* dynamic quantizer step size */
  dq = reconstruct(i & 0x08, _dqlntab4[i], y); /* quantized diff. */
  sr = (dq < 0) ? (se - (dq & 0x3FFF)) : se + dq;	/* reconst. signal */
  dqsez = sr - se + sez;			/* pole prediction diff. */
  update(4, y, _witab4[i] << 5, _fitab4[i], dq, sr, dqsez, state);
  switch (out_coding) {
    case ALAW:
      return (tandem_adjust_alaw(sr, se, y, i, 8, qtab4));
    case ULAW:
      return (tandem_adjust_ulaw(sr, se, y, i, 8, qtab4));
    case LINEAR:
      return (sr << 2);	/* sr was 14-bit dynamic range */
    default:
      return (-1);
  }
}

/*
 * Maps G.723_24 code word to reconstructed scale factor normalized log
 * magnitude values.
 */
static short _dqlntab3[8] = {-2048, 135, 273, 373, 373, 273, 135, -2048};
/* Maps G.723_24 code word to log of scale factor multiplier. */
static short _witab3[8] = {-128, 960, 4384, 18624, 18624, 4384, 960, -128};
/*
 * Maps G.723_24 code words to a set of values whose long and short
 * term averages are computed and then compared to give an indication
 * how stationary (steady state) the signal is.
 */
static short _fitab3[8] = {0, 0x200, 0x400, 0xE00, 0xE00, 0x400, 0x200, 0};
static short qtab3[3] = {8, 218, 331};
/*
 * Encodes a linear PCM, A-law or u-law input sample and returns its 3-bit code.
 * Returns -1 if invalid input coding value.
 */
short JG723::encode3(int sl, int in_coding, JG723State &state) {
  short	sei, sezi, se, sez;	/* ACCUM */
  short	d;			/* SUBTA */
  short	y;			/* MIX */
  short	sr;			/* ADDB */
  short	dqsez;			/* ADDC */
  short	dq, i;
  switch (in_coding) {	/* linearize input sample to 14-bit PCM */
    case ALAW:
      sl = alaw2linear(sl) >> 2;
      break;
    case ULAW:
      sl = ulaw2linear(sl) >> 2;
      break;
    case LINEAR:
      sl >>= 2;		/* sl of 14-bit dynamic range */
      break;
    default:
      return (-1);
  }
  sezi = predictor_zero(state);
  sez = sezi >> 1;
  sei = sezi + predictor_pole(state);
  se = sei >> 1;  /* se = estimated signal */
  d = sl - se;			/* d = estimation diff. */
  /* quantize prediction difference d */
  y = step_size(state);	/* quantizer step size */
  i = quantize(d, y, qtab3, 3);	/* i = ADPCM code */
  dq = reconstruct(i & 4, _dqlntab3[i], y); /* quantized diff. */
  sr = (dq < 0) ? se - (dq & 0x3FFF) : se + dq; /* reconstructed signal */
  dqsez = sr + sez - se;		/* pole prediction diff. */
  update(3, y, _witab3[i], _fitab3[i], dq, sr, dqsez, state);
  return (i);
}

/*
 * Decodes a 3-bit CCITT G.723_24 ADPCM code and returns
 * the resulting 16-bit linear PCM, A-law or u-law sample value.
 * -1 is returned if the output coding is unknown.
 */
short JG723::decode3(int i, int out_coding, JG723State &state) {
  short	sezi, sei, sez, se;	/* ACCUM */
  short	y;			/* MIX */
  short	sr;			/* ADDB */
  short	dq;
  short	dqsez;
  i &= 0x07;  /* mask to get proper bits */
  sezi = predictor_zero(state);
  sez = sezi >> 1;
  sei = sezi + predictor_pole(state);
  se = sei >> 1; /* se = estimated signal */
  y = step_size(state); /* adaptive quantizer step size */
  dq = reconstruct(i & 0x04, _dqlntab3[i], y); /* unquantize pred diff */
  sr = (dq < 0) ? (se - (dq & 0x3FFF)) : (se + dq); /* reconst. signal */
  dqsez = sr - se + sez;			/* pole prediction diff. */
  update(3, y, _witab3[i], _fitab3[i], dq, sr, dqsez, state);
  switch (out_coding) {
    case ALAW:
      return (tandem_adjust_alaw(sr, se, y, i, 4, qtab3));
    case ULAW:
      return (tandem_adjust_ulaw(sr, se, y, i, 4, qtab3));
    case LINEAR:
      return (sr << 2);	/* sr was of 14-bit dynamic range */
    default:
      return (-1);
  }
}

/*
 * Maps G.723_40 code word to ructeconstructed scale factor normalized log
 * magnitude values.
 */
static short _dqlntab5[32] = {
  -2048, -66, 28, 104, 169, 224, 274, 318,
  358, 395, 429, 459, 488, 514, 539, 566,
  566, 539, 514, 488, 459, 429, 395, 358,
  318, 274, 224, 169, 104, 28, -66, -2048};

/* Maps G.723_40 code word to log of scale factor multiplier. */
static short _witab5[32] = {
  448, 448, 768, 1248, 1280, 1312, 1856, 3200,
  4512, 5728, 7008, 8960, 11456, 14080, 16928, 22272,
  22272, 16928, 14080, 11456, 8960, 7008, 5728, 4512,
  3200, 1856, 1312, 1280, 1248, 768, 448, 448};

/*
 * Maps G.723_40 code words to a set of values whose long and short
 * term averages are computed and then compared to give an indication
 * how stationary (steady state) the signal is.
 */
static short _fitab5[32] = {
  0, 0, 0, 0, 0, 0x200, 0x200, 0x200,
  0x200, 0x200, 0x400, 0x600, 0x800, 0xA00, 0xC00, 0xC00,
  0xC00, 0xC00, 0xA00, 0x800, 0x600, 0x400, 0x200, 0x200,
  0x200, 0x200, 0x200, 0, 0, 0, 0, 0};

static short qtab5[15] = {
  -122, -16, 68, 139, 198, 250, 298, 339,
  378, 413, 445, 475, 502, 528, 553};

/*
 * Encodes a 16-bit linear PCM, A-law or u-law input sample and retuens
 * the resulting 5-bit CCITT G.723 40Kbps code.
 * Returns -1 if the input coding value is invalid.
 */
short JG723::encode5(int sl, int in_coding, JG723State &state) {
  short	sei, sezi, se, sez;	/* ACCUM */
  short	d;			/* SUBTA */
  short	y;			/* MIX */
  short	sr;			/* ADDB */
  short	dqsez;			/* ADDC */
  short	dq, i;
  switch (in_coding) {	/* linearize input sample to 14-bit PCM */
    case ALAW:
      sl = alaw2linear(sl) >> 2;
      break;
    case ULAW:
      sl = ulaw2linear(sl) >> 2;
      break;
    case LINEAR:
      sl >>= 2;	/* sl of 14-bit dynamic range */
      break;
    default:
      return (-1);
  }
  sezi = predictor_zero(state);
  sez = sezi >> 1;
  sei = sezi + predictor_pole(state);
  se = sei >> 1;			/* se = estimated signal */
  d = sl - se;			/* d = estimation difference */
  /* quantize prediction difference */
  y = step_size(state);	/* adaptive quantizer step size */
  i = quantize(d, y, qtab5, 15);	/* i = ADPCM code */
  dq = reconstruct(i & 0x10, _dqlntab5[i], y);	/* quantized diff */
  sr = (dq < 0) ? se - (dq & 0x7FFF) : se + dq; /* reconstructed signal */
  dqsez = sr + sez - se;		/* dqsez = pole prediction diff. */
  update(5, y, _witab5[i], _fitab5[i], dq, sr, dqsez, state);
  return (i);
}

/*
 * Decodes a 5-bit CCITT G.723 40Kbps code and returns
 * the resulting 16-bit linear PCM, A-law or u-law sample value.
 * -1 is returned if the output coding is unknown.
 */
short JG723::decode5(int i, int out_coding, JG723State &state) {
  short	sezi, sei, sez, se;	/* ACCUM */
  short	y;			/* MIX */
  short	sr;			/* ADDB */
  short	dq;
  short	dqsez;
  i &= 0x1f;			/* mask to get proper bits */
  sezi = predictor_zero(state);
  sez = sezi >> 1;
  sei = sezi + predictor_pole(state);
  se = sei >> 1;			/* se = estimated signal */
  y = step_size(state);	/* adaptive quantizer step size */
  dq = reconstruct(i & 0x10, _dqlntab5[i], y);	/* estimation diff. */
  sr = (dq < 0) ? (se - (dq & 0x7FFF)) : (se + dq); /* reconst. signal */
  dqsez = sr - se + sez;		/* pole prediction diff. */
  update(5, y, _witab5[i], _fitab5[i], dq, sr, dqsez, state);
  switch (out_coding) {
    case ALAW:
      return (tandem_adjust_alaw(sr, se, y, i, 0x10, qtab5));
    case ULAW:
      return (tandem_adjust_ulaw(sr, se, y, i, 0x10, qtab5));
    case LINEAR:
      return (sr << 2);	/* sr was of 14-bit dynamic range */
    default:
      return (-1);
  }
}

