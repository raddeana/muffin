// svd.cpp : 定义控制台应用程序的入口点。
//
 
#include "stdafx.h"
#include "bmuav.c"
#include "brmul.c"
 
extern void brmul(double *a,double *b,int m,int n,int k,double *c);
extern int bmuav(double *a,int m,int n,double *u,double *v,double eps,int ka);
 
int _tmain(int argc, _TCHAR* argv[])
{
	int i,j;
    static double a[4][3]={ {1.0,1.0,-1.0},{2.0,1.0,0.0},
                           {1.0,-1.0,0.0},{-1.0,2.0,1.0}};
    static double b[3][4]={ {1.0,1.0,-1.0,-1.0},{2.0,1.0,
                            0.0,2.0},{1.0,-1.0,0.0,1.0}};
    static double u[4][4],v[3][3],c[4][3],d[3][4];
    double eps;
    eps=0.000001;
    i=bmuav(&a[0][0],4,3,&u[0][0],&v[0][0],eps,5);
    printf("\n");
    printf("EXAMPLE(1)\n");
    printf("\n");
    printf("i=%d\n",i);
    printf("\n");
    printf("MAT U IS:\n");
    for (i=0; i<=3; i++)
      { for (j=0; j<=3; j++)
          printf("%13.7e ",u[i][j]);
        printf("\n");
      }
    printf("\n");
    printf("MAT V IS:\n");
    for (i=0; i<=2; i++)
      { for (j=0; j<=2; j++)
          printf("%13.7e ",v[i][j]);
        printf("\n");
      }
    printf("\n");
    printf("MAT A IS:\n");
    for (i=0; i<=3; i++)
      { for (j=0; j<=2; j++)
          printf("%13.7e ",a[i][j]);
        printf("\n");
      }
    printf("\n\n");
    printf("MAT UAV IS:\n");
    brmul(&u[0][0],&a[0][0],4,4,3,&c[0][0]);
    brmul(&c[0][0],&v[0][0],4,3,3,&a[0][0]);
    for (i=0; i<=3; i++)
      { for (j=0; j<=2; j++)
          printf("%13.7e ",a[i][j]);
        printf("\n");
      }
    printf("\n\n");
    printf("EXAMPLE(2)\n");
    printf("\n");
    i=bmuav(&b[0][0],3,4,&v[0][0],&u[0][0],eps,5);
    printf("i=%d\n",i);
    printf("\n");
    printf("MAT U IS:\n");
    for (i=0; i<=2; i++)
      { for (j=0; j<=2; j++)
          printf("%13.7e ",v[i][j]);
        printf("\n");
      }
    printf("\n");
    printf("MAT V IS:\n");
    for (i=0; i<=3; i++)
      { for (j=0; j<=3; j++)
          printf("%13.7e ",u[i][j]);
        printf("\n");
      }
    printf("\n");
    printf("MAT B IS:\n");
    for (i=0; i<=2; i++)
      { for (j=0; j<=3; j++)
          printf("%13.7e ",b[i][j]);
        printf("\n");
      }
    printf("\n\n");
    printf("MAT UBV IS:\n");
    brmul(&v[0][0],&b[0][0],3,3,4,&d[0][0]);
    brmul(&d[0][0],&u[0][0],3,4,4,&b[0][0]);
    for (i=0; i<=2; i++) { for (j=0; j<=3; j++)
          printf("%13.7e ",b[i][j]);
        printf("\n");
      }
    printf("\n");
	return 0;
}
