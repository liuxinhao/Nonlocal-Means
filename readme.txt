This is only a matlab wrapper for non local means denoising filter 
implemented by the original authors:
Antoni Buades, Bartomeu Coll, Jean-Michel Morel
Please refer:
http://www.ipol.im/pub/art/2011/bcm_nlm/
for more details.

usage:
1) run compile.m to generate the mex files.

2) denoise by:

denoised = mexnlmeans_ipol(single(nimg),fSigma);

** input image must be signle type.

Tested on Ubuntu 12.10 and Mac OS Lion 64 bits.

Run demo.m to try!

Xinhao Liu
vidreams@gmail.com
2013-08-30