
double svdEst(double *dataMat, int user, func simMeas, int item, int m, int n)
{
	double *u, *v, *data_new, *I, *dataMat2, *dataMatCopy, *svdMat;
	double simTotal=0, ratSimTotal=0, userRating=0, similarity=0, eps=0;
	int i=0, j=0, k=0, count=0, ka=0,scale=0;
 
	u = (double *)malloc(sizeof(double)*m*m);
	v = (double *)malloc(sizeof(double)*n*n);
	dataMat2 = (double *)malloc(sizeof(double)*m*n);
	dataMatCopy = (double *)malloc(sizeof(double)*m*n);
	for(i=0;i<m*n;i++) 
		dataMatCopy[i] = dataMat[i];
	for(i=0;i<m*m;i++) 
		u[i] = 0;
	for(i=0;i<n*n;i++) 
		v[i] = 0;
 
	eps = 0.000001;
	ka = max(m,n) + 1;
 
	//奇异值分解
	bmuav(&dataMatCopy[0], m, n, u, v, eps, ka);
 
	//挑选合适的奇异值：打印出所有的，再挑选，此处打印略
	scale = 4;
	I = (double *)malloc(sizeof(double)*scale*scale);
	for(i=0;i<scale*scale;i++) 
		I[i] = 0.0;
 
	for(i = 0;i < scale;i++)
	{
		I[i*scale+i] = dataMatCopy[i*n+i];
		//printf("%f ", I[i*scale+i]);
	}
	//printf("\n");
 
	//将物品转换到低维空间，data_new = dataMat' * U[:,0:scale] * I
	data_new = (double *)malloc(sizeof(double)*n*scale);
	svdMat = (double *)malloc(sizeof(double)*n*scale);
	
	matrix_reverse(dataMat, dataMat2, m, n);
    brmul(dataMat2, u, n, m, scale, data_new);
	brmul(data_new, I, n, scale, scale, svdMat);
 
	for (j = 0;j < n;j++)
	{
		userRating = dataMat[user*n+j];		//user用户评价过的
		if((userRating == 0) || (j == item))
			continue;
 
		similarity = simMeas(svdMat, NULL, scale, scale, item, j);  //由于是SVD压缩的，不用考虑交集了		
		simTotal += similarity;
		ratSimTotal += similarity * userRating;
	}
 
	free(u);free(v);
	free(data_new);free(dataMat2);
	free(dataMatCopy);free(I);free(svdMat);
 
	if(0 == simTotal)
	{
		return 0.0;
	}else
	{
		return ratSimTotal/simTotal;
	}
	
}
