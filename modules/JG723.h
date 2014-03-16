#if !defined( _JG723_h )
#define _JG723_h

#include "JObject.h"

class JG723State {
  public:
    JG723State();
    long yl;	/* Locked or steady state step size multiplier. */
    short yu;	/* Unlocked or non-steady state step size multiplier. */
    short dms;	/* Short term energy estimate. */
    short dml;	/* Long term energy estimate. */
    short ap;	/* Linear weighting coefficient of 'yl' and 'yu'. */
    short a[2];	/* Coefficients of pole portion of prediction filter. */
    short b[6];	/* Coefficients of zero portion of prediction filter. */
    short pk[2];/* Signs of previous two samples of a partially
		 * reconstructed signal. */
    short dq[6];/* Previous 6 samples of the quantized difference
		 * signal represented in an internal floating point
		 * format. */
    short sr[2];/* Previous 2 samples of the quantized difference
		 * signal represented in an internal floating point
		 * format. */
    char td;	/* delayed tone detect, new in 1988 version */
    short prev;
};

class JG723 : public JObject {
  public:
    enum { ULAW, ALAW, LINEAR};
    static int search(int val,	short *table, int size);
    static unsigned char linear2alaw(int pcm_val);
    static int alaw2linear(unsigned char a_val);
    static unsigned char linear2ulaw(int pcm_val);
    static int ulaw2linear(unsigned char u_val);
    static unsigned char alaw2ulaw(unsigned char aval);
    static unsigned char ulaw2alaw(unsigned char uval);
    virtual const char* className() const;
    virtual JObject* clone() const;
    static short encode4(int sl, int in_coding, JG723State &state);
    static short decode4(int i, int out_coding, JG723State &state);
    static short encode3(int sl, int in_coding, JG723State &state);
    static short decode3(int i, int out_coding, JG723State &state);
    static short encode5(int sl, int in_coding, JG723State &state);
    static short decode5(int i, int out_coding, JG723State &state);
  protected:
    static int quan(int val, short *table, int size);
    static int fmult(int an, int srn);
    static int predictor_zero(JG723State &state);
    static int predictor_pole(JG723State &state);
    static int step_size(JG723State &state);
    static int quantize(int d, int y, short *table, int size);
    static int reconstruct(int	sign, int dqln,	int y);
    static void update(int code_size, int y, int wi, int fi, int dq,
      int sr, int dqsez, JG723State &state);
    static int tandem_adjust_alaw(int sr, int se, int y, int i, int sign, short *qtab);
    static int tandem_adjust_ulaw(int sr, int se, int y, int i, int sign, short *qtab);
};

#endif
