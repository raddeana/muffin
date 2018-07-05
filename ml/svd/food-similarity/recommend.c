
double recommend(double *dataMat,int n, int m, int user, func simMeas, Est estMethod)
{
	int i,count, item,j;
	int *record=0;
	double *temp_vote=0;
	double temp=0, temp2=0;
 
	record = (int *)malloc(sizeof(int)*n);
	memset(record, 0, sizeof(int)*n);
	count = 0;
 
	//寻找user用户未评价物品
	for(i = 0;i < n;i++)
	{
		if(dataMat[user*n+i] == 0)
		{
			record[count++] = i;
		}
	}
	if (count == 0)
	{
		printf("该用户评价了所有的物品\n");
		return -1; //用户评价了所有的物品
	}
 
	temp_vote = (double *)malloc(sizeof(double)*count);
	memset(temp_vote,0,sizeof(double)*count);
 
	for(i=0;i<count;i++)
	{
		item = record[i];
		temp_vote[i] = estMethod(dataMat, user, simMeas, item, m, n);
	}
 
	//排序
	for(i=0;i<count;i++)
	{
		for(j=0;j<count - i;j++)
		{
			if(temp_vote[j]<temp_vote[j+1])
			{
				temp = temp_vote[j];
				temp_vote[j] = temp_vote[j+1];
				temp_vote[j+1] = temp;
 
				temp2 = record[j];
				record[j] = record[j+1];
				record[j+1] = temp2;
			}
		}
	}
 
	//dump result
	for(i = 0;i < count;i++)
	{
		printf("food label %d,value to recommand %f\n", record[i], temp_vote[i]);
	}
	free(record);
	return 0;
}
