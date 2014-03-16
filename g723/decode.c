/*
 * original code taken from decode.c in the suite of programs
 * from ftp.cwi.nl:/pub/audio/ccitt-adpcm.tar.Z...
 * it's mostly all still there!
 * 
 * NB: when you retrieve the package, change
 *     CC = acc -> CC = cc
 *     in the Makefile
 *
 * I've added a bit to read the NeXT .snd header, use
 * that to determine what compression technique was used,
 * change the header to that required for specified output
 * format, and write that out.
 * I've guessed at the compression format conversion:
 * SND_FORMAT_ADPCM_G721 seems to be right, but this is the only
 * type I've ben able to test on.
 *
 * This has only been tested on one file, on Motorola h/w
 * I am not sure what will happen to data on Intel h/w: I suspect
 * that bytes should be swapped...
 * as you'd probably guess this is experimental and not guaranteed
 * to do anything you might want it to.  Use it at your own risk!
 * I would, however, be grateful for any feedback, comments,
 * criticisms etc. so that this can be improved.
 *
 * Have fun,
 *
 * mmalcolm  (Malcolm Crawford)
 *
 *  SHeffield Auditory Group  |  Vox  : (+44) 742 768555 ext 5569
 *  Dept. Computer Science    |         direct :  825569
 *  Sheffield University      |  Fax  : (+44) 742 780972
 *  Regent Court              |  Email: malc@dcs.shef.ac.uk
 *  211 Portobello Street     |  (NeXTMail welcome)
 *  Sheffield S1 4DP, UK.     |  (Read-Receipts discouraged :-)
 *
 */



/*
 * decode.c
 *
 * CCITT ADPCM decoder
 *
 * Usage : decode [-3|4|5] [-a|u|l] < infile > outfile
 */
#include <stdio.h>
#include "g72x.h"
#include <sound/sound.h>
#include <architecture/byte_order.h>

#define STDIN_FD 0
#define STDOUT_FD 1
#define STDERR_FD 2

/*
 * Unpack input codes and pass them back as bytes.
 * Returns 1 if there is residual input, returns -1 if eof, else returns 0.
 */
int
unpack_input(
	unsigned char		*code,
	int			bits)
{
	static unsigned int	in_buffer = 0;
	static int		in_bits = 0;
	unsigned char		in_byte;

	if (in_bits < bits) {
		if (fread(&in_byte, sizeof (char), 1, stdin) != 1) {
			*code = 0;
			return (-1);
		}
		in_buffer |= (in_byte << in_bits);
		in_bits += 8;
	}
	*code = in_buffer & ((1 << bits) - 1);
	in_buffer >>= bits;
	in_bits -= bits;
	return (in_bits > 0);
}


main(int argc, char **argv)
{
	short			sample;
	unsigned char		code;
	int			n;
	struct g72x_state	state;
	int			out_coding;
	int			out_size;
	int			(*dec_routine)();
	int			dec_bits;
	SNDSoundStruct		*sound;
	int			writeHeader;

   g72x_init_state(&state);
   out_coding = AUDIO_ENCODING_ULAW;
   out_size = sizeof (char);
   dec_routine = g721_decoder;
   dec_bits = 4;
   writeHeader = 1;
   
   /* Process encoding argument, if any */
   while ((argc > 1) && (argv[1][0] == '-')) {
      switch (argv[1][1]) {
	 case 'u':
	       out_coding = AUDIO_ENCODING_ULAW;
	       out_size = sizeof (char);
	       break;
	 case 'a':
               /* NB NeXT cannot play this format */
	       out_coding = AUDIO_ENCODING_ALAW;
	       out_size = sizeof (char);
	       break;
	 case 'l':
	       out_coding = AUDIO_ENCODING_LINEAR;
	       out_size = sizeof (short);
	       break;
	 case 'n':
	       writeHeader = 0;
	       break;
	 default:
fprintf(stderr, "CCITT ADPCM Decoder -- usage:\n");
fprintf(stderr, "\tdecode [-a|u|l] -n < infile > outfile\n");
fprintf(stderr, "where:\n");
fprintf(stderr, "\t-a\tGenerate 8-bit A-law data\n");
fprintf(stderr, "\t-u\tGenerate 8-bit u-law data [default]\n");
fprintf(stderr, "\t-l\tGenerate 16-bit linear PCM data\n");
fprintf(stderr, "\t-n\tonly output data (no header)\n");
	       exit(1);
	 }
	 argc--;
	 argv++;
   }

   /*
    * read the Sound header to find the compression format
    */
   SNDReadHeader(STDIN_FD, &sound);
   
   /*
    * oddly, after SNDReadHeader(), next byte read is beginning of Sound
    * header: so skip along input to beginning of data...
    */
   lseek(STDIN_FD, sound->dataLocation, SEEK_SET);

   switch (sound->dataFormat) {
      case SND_FORMAT_ADPCM_G723_3:
	 dec_routine = g723_24_decoder;
	 dec_bits = 3;
	 break;
      case SND_FORMAT_ADPCM_G721:
	 dec_routine = g721_decoder;
	 dec_bits = 4;
	 break;
      case SND_FORMAT_ADPCM_G723_5:
	 dec_routine = g723_40_decoder;
	 dec_bits = 5;
	 break;
      default:
         fprintf(stderr, "not a recognised compression format.\nexiting...");
	 exit(1);
   }

   /*
    * write the Sound header if necessary
    */
   if (writeHeader) {
	int	samps;
      /*
       * alter the Sound header to reflect required output format
       */
      samps = SNDBytesToSamples(sound->dataSize, sound->channelCount,
				sound->dataFormat);
      switch (out_coding) {
	 case AUDIO_ENCODING_ULAW:
	    sound->dataFormat = SND_FORMAT_MULAW_8;
	    break;
	 case AUDIO_ENCODING_ALAW:
	    sound->dataFormat = SND_FORMAT_ALAW_8;
	    break;
	 case AUDIO_ENCODING_LINEAR:
	    sound->dataFormat = SND_FORMAT_LINEAR_16;
	    break;
      }
      sound->dataSize = SNDSamplesToBytes(samps, sound->channelCount,
					  sound->dataFormat);
   
      SNDWriteHeader(STDOUT_FD, sound);
   }
   
   while (unpack_input(&code, dec_bits) >= 0) {
      sample = (*dec_routine)(code, out_coding, &state);
      if (out_coding == AUDIO_ENCODING_LINEAR) {
         /* Swap if this is a little-endian machine. */
         sample = NXSwapHostShortToBig(sample);
	 fwrite(&sample, out_size, 1, stdout);
      } else {
	 code = (unsigned char)sample;
	 fwrite(&code, out_size, 1, stdout);
      }
   }
   fclose(stdout);
}
