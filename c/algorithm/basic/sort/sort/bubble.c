/**
 * 冒泡排序
 * @author mulberry
 */

#include <stdio.h>
#include <swap.h>

/**
 * 冒泡排序
 * @param {int[]} 排序数组
 * @return void
 */
void bubble_sort(int arr[])
{
  bool isSorted = true;
  int len = sizeof(arr) - 1;
  
  for (int i = 0; i < len; i ++) {
    for (int j = 0; j < len - i; j ++) {
      if (arr[j] > arr[j + 1]) {
        isSorted = false;
        swap(arr[j], arr[j+1]);
      }
    }
    
    if (isSorted) {
      break;
    }
  }
}
