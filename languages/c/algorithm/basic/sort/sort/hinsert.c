/**
 * 二分插入
 * @author mulberry
 */
#include <stdio.h>

void hinsert (int arr[]);

/**
 * 二分插入
 * @param { int[] } 参与排序的数组
 */
void hinsert (int arr[])
{
  int len = sizeof(arr);
  
  for (int i = 1; i < len; i ++) {
    int low = 0,
        high = i;
    
    if (a[i] < a[i - 1]) {
      int x = arr[i];
      arr[i] = arr[i - 1];
      
      while (low <= high) {
        int m = (low + high) / 2;
        
        if(x < arr[m]) {
          high = m - 1;
        } else {
          low = m + 1;
        }
      }

      for(int j = i - 1;j >= high + 1;j --) {
        arr[j + 1] = a[j];
      }

      arr[j + 1] = x;    
    }
  }
}
