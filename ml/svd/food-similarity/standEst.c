double standEst(double *dataMat, int user, func simMeas, int item, int m, int n)
{
	double simTotal=0, ratSimTotal=0, userRating=0, similarity=0;
	int j=0, k=0, count=0;
	int *overLap=0;	//记录交集
	
	overLap = (int *)malloc(sizeof(int)*m);
	
	for (j = 0;j < n;j++)
	{
		userRating = dataMat[user*n+j];		//user用户评价过的
		if(userRating == 0)
			continue;
		
		count = 0;
		memset(overLap, 0, sizeof(int)*m);
 
		for(k = 0;k < m;k++)
		{
			if(dataMat[k*n+item] > 0 && dataMat[k*n+j] > 0)		//寻找用户都评级的两个物品
			{	
				overLap[count++] = k;
			}
		}
 
		if (count == 0)
		{
			similarity = 0;
		}else
		{
			similarity = simMeas(dataMat, overLap, n, count, item, j);
		}
		
		simTotal += similarity;
		ratSimTotal += similarity * userRating;
	}
 
	free(overLap);
	if(0 == simTotal)
	{
		return 0.0;
	}else
	{
		return ratSimTotal/simTotal;
	}
}
