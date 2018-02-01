#include <stdio.h>

/**
 * 克隆数组
 * @param {int[]} 源数组
 * @param {int[]} 目标数组
 * @param {int[]} 克隆长度
 * @param {int[]} 起始位置
 */
void copyArray(int source[], int dest[], int len, int first)    
{    
   int i;    
   int j = first;

   for(i = 0; i < len; i ++)
   {    
      dest[j] = source[i];
      j++;
   }     
}

/**
 * 克隆数组
 * @param {int[]} 源数组
 * @param {int} 混合左侧起始位置
 * @param {int} 混合右侧起始位置
 */
void merge(int arr[], int left, int right)    
{    
   int begin1 = left;    
   int mid = (left + right) / 2 ;    
   int begin2 = mid + 1;    
   int k = 0;    
   int newArrayLen = right - left + 1;    
   int *b = (int*)malloc(newArrayLen * sizeof(int));

   while(begin1 <= mid && begin2 <= right)
   {
      if (arr[begin1] <= arr[begin2]) {    
         b[k ++] = arr[begin1 ++];    
      } else {    
         b[k ++] = arr[begin2 ++];
      }
   }

   while(begin1 <= mid) {
      b[k ++] = arr[begin1 ++];
   }

   while(begin2 <= right) {
      b[k ++] = arr[begin2 ++];
   }

   copyArray(b, arr, newArrayLen, left);
   free(b);
}

/**
 * 归并排序
 * @param {int[]} 源数组
 * @param {int} 排序位置左起
 * @param {int} 排序位置最右侧
 */
void mergeSort(int arr[], int left, int right)    
{    
   int i;

   if (left < right)    
   {
      i = (left + right) / 2;
      mergeSort(arr, left, i);
      mergeSort(arr, i + 1, right);
      merge(arr, left, right);
   }
}

/**
 * 归并排序
 * @param {int[]} 源数组
 */
void MergeSort(int arr[])
{
   int len = sizeof(arr);
   mergeSort(arr, 0, len - 1);  
}
