/**
 * 快速排序
 * @author mulberry
 */

#include <stdio.h>

void quicksort (int arr[], int low, int hight);

/**
 * 快速排序
 * @param {int []} 快速排序数组
 */
void quicksort (int arr[], int low, int hight) {
   int i, j, t, m;

   if (low < hight)
   {
      i = low;  
      j = hight;  
      t = arr[low];      // 第一个数为轴

      while(i < j)
      {
         while(i < j && arr[j] > t)
         {
            j --;
         }

         if(i < j)
         {
            m = arr[i];
            arr[i] = arr[j];
            arr[j] = m;
            i++;
         }

         while(i < j && arr[i] <= t)
         {
            i++;
         }

         if(i < j)
         {
            m = arr[j];
            arr[j] = arr[i];
            arr[i] = m;
            j --;
         }
      }
       
      arr[i] = t;  
      quicksort(arr, 0, i - 1);  
      quicksort(arr, i + 1, hight);  
   }
}
