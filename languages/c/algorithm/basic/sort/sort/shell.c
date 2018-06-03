/**
 * 希尔排序
 * @author mulberry
 */

#include <stdio.h>

void shell (int arr[]);

/**
 * 希尔排序
 * @param {int[]} 一个可排序数组
 */
void shell (int arr[]) {
  int h = 0;
  int len = sizeof(arr);
  
  while (h <= len)
  {
    h = 3 * h + 1;
  }
  
  while (h >= 1)
  {
    for (int i = h; i < n; i++)
    {
      int j = i - h;
      int get = arr[i];
      
      while (j >= 0 && A[j] > get)
      {
        arr[j + h] = arr[j];
        j = j - h;
      }
      
      arr[j + h] = get;
    }
    
    h = (h - 1) / 3;
  }
}
