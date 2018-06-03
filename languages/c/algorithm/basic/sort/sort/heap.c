#include <stdio.h>

void HeapAdjust(int arr[], int s, int n);
void CreatHeap(int arr[], int n);
void HeapSort(int arr[]);

/**
 * 调整堆
 * @param
 */
void HeapAdjust(int arr[], int s, int n)  
{  
  //调整为小根堆，从小到大  
  int rc = arr[s];
  for(int j = 2*s; j <= n; j *= 2)  
  {  
    if(j < n && arr[j] > arr[j + 1])      //判断左右子数大小  
      j++;

    if(rc <= arr[j])
      break;

    arr[s] = arr[j];
    s = j;
  }

  a[s] = rc;
}

/**
 * 建初堆
 * @param
 */
void CreatHeap(int a[], int n)  
{  
  // 小根堆  
  for (int i = n / 2 ; i > 0; i--)
  {
    HeapAdjust(a, i, n);
  }  
}

/**
 * 堆排序
 * @param
 */
void HeapSort(int arr[])  
{  
  int len = sizeof(arr);
  CreatHeap(arr, len);
  
  for(int i = len; i > 1; i--)  
  {
    int x = arr[1];
    arr[1] = arr[i];
    arr[i] = x;
    
    HeapAdjust(arr, 1, i - 1);
  }
}
