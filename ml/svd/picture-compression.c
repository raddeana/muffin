#include "stdafx.h"
#include "cv.h"
#include "highgui.h"
#include "bmuav.c"
#include "brmul.c"
#define max(a,b)            (((a) > (b)) ? (a) : (b))
 
extern void brmul(double *a,double *b,int m,int n,int k,double *c);
extern int bmuav(double *a,int m,int n,double *u,double *v,double eps,int ka);
int Process(IplImage *src);
 
int _tmain (int argc, _TCHAR* argv[]) {
	IplImage *src = cvLoadImage("test1.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	Process(src);
	return 0;
}
 
int Process (IplImage *src) {
	double *data, *u, *v, *c;
	int height, width, i, j, ka;
	double eps;
	int scale;
	IplImage *dst;
	
	dst = cvCreateImage(cvSize(src->width,src->height),IPL_DEPTH_8U,1);
 
	eps=0.000001;
	height = src->height;
	width = src->widthStep;
	
	// allocate memory for matrix
	data = (double *)malloc(sizeof(double)*height*width);
	u = (double *)malloc(sizeof(double)*height*height);
	v = (double *)malloc(sizeof(double)*width*width);
	memset(u,0,sizeof(double)*height*height);
	memset(v,0,sizeof(double)*width*width);
	
	if (NULL == data || NULL == u || NULL == v) {
		return -1;
	}
 
	// assign value
	for (i = 0;i < height;i++) {
		for (j = 0;j < width;j++) {
			data[i*width+j] = (double)(unsigned char)src->imageData[i*width+j];
		}
	}
	
	ka = max(height,width) + 1;
	bmuav(data, height, width, u, v, eps, ka);
	
	// dump svd, scale is selected by watching top xxx large data
	for (i = 0; i <= 100; i ++) { 
		for (j = 0; j <= 100; j ++) {
			printf("%f", data[i*width+j]);
    }
    
		printf("\n");
	}
	
	// reconstruction
	scale = 50;
	for(i = scale;i < height;i ++) {
		data[i*width+i] = 0;
	}
 
	/*c needs to be initilized here ,but in matrix mutiply funciton*/
	c = (double *)malloc(sizeof(double)*height*width);
	
	brmul(u, data ,height, height, width, c);
	brmul(c, v, height, width, width, data);
 
	// assign value
	for(i = 0; i < height; i ++) {
		for(j = 0; j < width; j ++) {
			dst->imageData[i*width+j] = (unsigned char)data[i*width+j];
		}
	}
  
	cvSaveImage("result.jpg",dst);
	free(data);
  free(u);
  free(v);
	cvReleaseImage(&dst);
  
	return 0;
}
