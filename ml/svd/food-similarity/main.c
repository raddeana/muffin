// recommand.c
 
#include "stdafx.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "bmuav.c"
#include "brmul.c"
#define max(a,b) (((a) > (b)) ? (a) : (b))
 
typedef double (*func)(double *dataMat,int *overLap, int n, int count, int item, int j);
typedef double (*Est)(double *dataMat, int user, func simMeas, int item, int m, int n);
 
extern void brmul(double *a,double *b,int m,int n,int k,double *c);
extern int bmuav(double *a,int m,int n,double *u,double *v,double eps,int ka);
extern void matrix_reverse(double *src,double *dest,int row,int col);
 
double standEst(double *dataMat, int user, func simMeas, int item, int m, int n);
double svdEst(double *dataMat, int user, func simMeas, int item, int m, int n);
double cosSim(double *dataMat,int *overLap, int n, int count, int item, int j);
double cosSim2(int *dataMat,int *overLap, int n, int scale, int item, int j);
double ecludSim(double *dataMat,int *overLap, int n, int count, int item, int j);
double ecludSim2(double *dataMat,int *overLap, int n, int count, int item, int j);
double recommend(double *dataMat,int n, int m, int user, func simMeas=cosSim, Est estMethod=standEst);
 
int _tmain (int argc, _TCHAR* argv[]) {
	int user;
	double data[7][5] = {{4, 4, 0, 2, 2},
					{4, 0, 0, 3, 3},
					{4, 0, 0, 1, 1},
					{1, 1, 1, 2, 0},
					{2, 2, 2, 0, 0},
					{5, 5, 5, 0, 0},
					{1, 1, 1, 0, 0}};
	double data_2[11][11] 
          = {{2, 0, 0, 4, 4, 0, 0, 0, 0, 0, 0},
						{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5},
						{0, 0, 0, 0, 4, 0, 0, 1, 0, 4, 0},
						{3, 3, 4, 0, 3, 0, 0, 2, 2, 0, 0},
						{5, 5, 5, 0, 0, 0, 0, 0, 0, 0, 0},
						{0, 0, 0, 0, 0, 0, 5, 0, 0, 5, 0},
						{4, 0, 4, 0, 0, 0, 0, 0, 0, 0, 5},
						{0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 4},
						{0, 0, 0, 0, 0, 0, 5, 0, 0, 5, 0},
						{0, 0, 0, 3, 0, 0, 0, 0, 4, 5, 0},
						{1, 1, 2, 1, 1, 2, 1, 0, 4, 5, 0}};
            
	user = 2;
 
	recommend(&data_2[0][0], 11, 11, user, cosSim2, svdEst);
	return 0;
}
