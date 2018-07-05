#include "stdafx.h"
#include "cv.h"
#include "highgui.h"
#include "bmuav.c"
#include "brmul.c"
#define max(a,b) (((a) > (b)) ? (a) : (b))
 
extern void brmul(double *a,double *b,int m,int n,int k,double *c);
extern int bmuav(double *a,int m,int n,double *u,double *v,double eps,int ka);
int Process(IplImage *src);
 
int _tmain (int argc, _TCHAR* argv[]) {
	IplImage *src = cvLoadImage("test3.jpg", CV_LOAD_IMAGE_UNCHANGED);
	Process(src);
	return 0;
}
 
int Process (IplImage *src) {
	double *data_r, *u_r, *v_r, *c_r;
	double *data_g, *u_g, *v_g, *c_g;
	double *data_b, *u_b, *v_b, *c_b;
	int height, width, i, j, ka;
	double eps;
	int scale;
	IplImage *dst;
	
	dst = cvCreateImage(cvSize(src->width,src->height),IPL_DEPTH_8U,3);
 
	eps = 0.000001;
	height = src->height;
	width = src->width;
	
	// allocate memory for matrix
	data_r = (double *)malloc(sizeof(double)*height*width);
	u_r = (double *)malloc(sizeof(double)*height*height);
	v_r = (double *)malloc(sizeof(double)*width*width);
 
	data_g = (double *)malloc(sizeof(double)*height*width);
	u_g = (double *)malloc(sizeof(double)*height*height);
	v_g = (double *)malloc(sizeof(double)*width*width);
 
	data_b = (double *)malloc(sizeof(double)*height*width);
	u_b = (double *)malloc(sizeof(double)*height*height);
	v_b = (double *)malloc(sizeof(double)*width*width);
 
	memset(u_r,0,sizeof(double)*height*height);
	memset(v_r,0,sizeof(double)*width*width);
 
	memset(u_g,0,sizeof(double)*height*height);
	memset(v_g,0,sizeof(double)*width*width);
 
	memset(u_b,0,sizeof(double)*height*height);
	memset(v_b,0,sizeof(double)*width*width);
 
	// assign value
	for(i = 0;i < height;i ++) {
		for(j = 0;j < width;j ++) {
			data_r[i*width+j] = (double)(unsigned char)src->imageData[i*src->widthStep+j*src->nChannels+2];
			data_g[i*width+j] = (double)(unsigned char)src->imageData[i*src->widthStep+j*src->nChannels+1];
			data_b[i*width+j] = (double)(unsigned char)src->imageData[i*src->widthStep+j*src->nChannels+0];
		}
	}
	
	ka = max(height,width) + 1;
	bmuav(data_r, height, width, u_r, v_r, eps, ka);
	bmuav(data_g, height, width, u_g, v_g, eps, ka);
	bmuav(data_b, height, width, u_b, v_b, eps, ka);
	
	// dump svd, scale is selected by watching top xxx large data
	for (i = 0; i <= 100; i ++) {
		for (j = 0; j <= 100; j ++) {
			printf("%f", data[i*width+j]);
    }
    
		printf("\n");
	}
	
	// reconstruction
	scale = 50;
	for(i = scale;i<height;i++)
	{
		data_r[i*width+i] = 0;
		data_g[i*width+i] = 0;
		data_b[i*width+i] = 0;
	}
 
	// c needs to be initilized here ,but in matrix mutiply funciton
	c_r = (double *)malloc(sizeof(double)*height*width);
	c_g = (double *)malloc(sizeof(double)*height*width);
	c_b = (double *)malloc(sizeof(double)*height*width);
	
	brmul(u_r, data_r ,height, height, width, c_r);
	brmul(c_r, v_r, height, width, width, data_r);
 
	brmul(u_g, data_g ,height, height, width, c_g);
	brmul(c_g, v_g, height, width, width, data_g);
 
	brmul(u_b, data_b ,height, height, width, c_b);
	brmul(c_b, v_b, height, width, width, data_b);
 
	// assign value
	for (i = 0;i < height;i++) {
		for (j = 0;j < width;j++) {
			dst->imageData[i*src->widthStep+j*src->nChannels + 0] = (unsigned char)data_b[i*width+j];
			dst->imageData[i*src->widthStep+j*src->nChannels + 1] = (unsigned char)data_g[i*width+j];
			dst->imageData[i*src->widthStep+j*src->nChannels + 2] = (unsigned char)data_r[i*width+j];
		}
	}
  
	cvSaveImage("result.jpg", dst);
	cvReleaseImage(&dst);
  
	free(u_r);free(v_r);free(c_r);free(data_r);
	free(u_g);free(v_g);free(c_g);free(data_g);
	free(u_b);free(v_b);free(c_b);free(data_b);
  
	return 0;
}
