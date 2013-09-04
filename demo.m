
fSigma = 15;

img = double(imread('lena_color_256.tif'));
% img = double(imread('lena.bmp'));

nimg = img + randn(size(img)) * fSigma;

tic;
denoised = mexnlmeans_ipol(single(nimg),fSigma);
t1 = toc;

fprintf('Eclpase time: %f\n',t1);

imshow(uint8(denoised));