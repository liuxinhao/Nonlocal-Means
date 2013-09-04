#include "mex.h"
#include "libdenoising.h"

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
   
   
    
    
    if ( nrhs != 2 )
        mexErrMsgIdAndTxt("nlmeans:main", "Must have two inputs");
    if ( mxGetClassID(prhs[0]) != mxSINGLE_CLASS )
        mexErrMsgIdAndTxt("nlmeans:main", "nimg must be of type single");
    if ( mxGetClassID(prhs[1]) != mxDOUBLE_CLASS )
        mexErrMsgIdAndTxt("nlmeans:main", "fSigma must be of type double");
  
    
    
   // sigma = (float) mxGetScalar(prhs[1]);
    const mwSize *dims = mxGetDimensions(prhs[0]);
    size_t ndims = mxGetNumberOfDimensions(prhs[0]);
    
    
  
   
    
    
    
    int d_w = (int) dims[1];
    int d_h = (int) dims[0];
    int d_c = (int) ndims;
    
    if (d_c == 2) {
        d_c = 1;    // we do not use the alpha channel
    }
    if (d_c > 3) {
        d_c = 3;    // we do not use the alpha channel
    }
    
    int d_wh = d_w * d_h;
    int d_whc = d_c * d_w * d_h;
    
    // test if image is really a color image even if it has more than one channel
    /*
     * if (d_c > 1) {
     *
     * // dc equals 3
     * int i=0;
     * while (i < d_wh && d_v[i] == d_v[d_wh + i] && d_v[i] == d_v[2 * d_wh + i ])  {
     * i++;
     * }
     *
     * if (i == d_wh) d_c = 1;
     *
     * }
     */
    
    float fSigma =  (float) mxGetScalar(prhs[1]);
    float *noisy =(float *) mxGetPr(prhs[0]);
    
    float **fpI = new float*[d_c];
    float **fpO = new float*[d_c];
    float *denoised = new float[d_whc];
    
    for (int ii=0; ii < d_c; ii++) {
        
        fpI[ii] = &noisy[ii * d_wh];
        fpO[ii] = &denoised[ii * d_wh];
        
    }
    
    int bloc, win;
    float fFiltPar;
    
    if (d_c == 1) {
        
        if (fSigma > 0.0f && fSigma <= 15.0f) {
            win = 1;
            bloc = 10;
            fFiltPar = 0.4f;
            
        } else if ( fSigma > 15.0f && fSigma <= 30.0f) {
            win = 2;
            bloc = 10;
            fFiltPar = 0.4f;
            
        } else if ( fSigma > 30.0f && fSigma <= 45.0f) {
            win = 3;
            bloc = 17;
            fFiltPar = 0.35f;
            
        } else if ( fSigma > 45.0f && fSigma <= 75.0f) {
            win = 4;
            bloc = 17;
            fFiltPar = 0.35f;
            
        } else if (fSigma <= 100.0f) {
            
            win = 5;
            bloc = 17;
            fFiltPar = 0.30f;
            
        } else {
            mexPrintf("error :: algorithm parametrized only for values of sigma less than 100.0\n");
            exit(-1);
        }
        
        
        
        
        
    } else {
        
        
        if (fSigma > 0.0f && fSigma <= 25.0f) {
            win = 1;
            bloc = 10;
            fFiltPar = 0.55f;
            
        } else if (fSigma > 25.0f && fSigma <= 55.0f) {
            win = 2;
            bloc = 17;
            fFiltPar = 0.4f;
            
        } else if (fSigma <= 100.0f) {
            win = 3;
            bloc = 17;
            fFiltPar = 0.35f;
            
        } else {
            mexPrintf("error :: algorithm parametrized only for values of sigma less than 100.0\n");
            exit(-1);
        }
        
        
        
    }
    
    
    nlmeans_ipol(win, bloc, fSigma, fFiltPar, fpI,  fpO, d_c, d_w, d_h);

  
  
   
    plhs[0] = mxCreateNumericArray(ndims,dims,mxSINGLE_CLASS,mxREAL); /* Create the output matrix */
    float *B = (float *) mxGetPr(plhs[0]);
   
    
    for(int k = 0; k < d_c; k++)
    {
        for(int n = 0; n < d_w; n++)
        {
            for(int m = 0; m < d_h; m++)
            {
                B[m + d_h*n + k*d_w*d_h] = denoised[m + d_h*n + k*d_h*d_w];
            }
        }
    }
    
    
}


