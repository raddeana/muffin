void matrix_reverse (double *src, double *dest, int row, int col) {
	int i,j;
 
	for(i = 0; i < col; i ++) {
		for(j = 0; j < row; j ++) {
			dest[i * row + j] = src[j * col + i];
		}
	}
}
 
/*欧氏距离*/
double ecludSim (double *dataMat,int *overLap, int n, int count, int item, int j) {
	double total = 0.0;
	int i=0, index=0;
 
	for(i = 0;i < count;i++)
	{
		index = overLap[i];
		total = total + (dataMat[index*n+item] - dataMat[index*n+j]) * (dataMat[index*n+item] - dataMat[index*n+j]);
	}
	total = sqrt(total);
 
	return 1.0/(1.0 + total);
}

double ecludSim2 (double *dataMat,int *overLap, int n, int scale, int item, int j) {
	double total = 0.0;
	int i = 0;
 
	for(i = 0;i < scale;i++)
	{
		total = total + (dataMat[item*n+i] - dataMat[j*n+i]) * (dataMat[item*n+i] - dataMat[j*n+i]);
	}
  
	total = sqrt(total);
	return 1.0 / (1.0 + total);
}
 
/*余弦距离*/
double cosSim (double *dataMat,int *overLap, int n, int count, int item, int j) {
	double totalA=0.0, totalB=0.0, totalM=0.0;
	double result=0.0;
	int i, index;
 
	for(i = 0;i < count;i ++) {
		index = overLap[i];
		totalA = totalA + dataMat[index*n+item] * dataMat[index*n+item];
		totalB = totalB + dataMat[index*n+j] * dataMat[index*n+j];
		totalM = totalM + dataMat[index*n+item] * dataMat[index*n+j];
	}
  
	result = totalM / (sqrt(totalA) * sqrt(totalB));
	return 0.5 + 0.5 * result;
}
 
double cosSim2 (double *dataMat,int *overLap, int n, int scale, int item, int j) {
	double totalA=0.0, totalB=0.0, totalM=0.0;
	double result=0.0;
	int i;
 
	for(i = 0;i < scale;i ++) {
		totalA = totalA + dataMat[item*n+i] * dataMat[item*n+i];
		totalB = totalB + dataMat[j*n+i] * dataMat[j*n+i];
		totalM = totalM + dataMat[item*n+i] * dataMat[j*n+i];
	}
  
	result = totalM / (sqrt(totalA) * sqrt(totalB));
	return 0.5 + 0.5 * result;
}
