#include <stdio.h>

void selection (int arr[]);

/**
 * 选择排序
 * @param {int[]} 参与排序的数组
 */
void selection (int arr[]) {
  int len = sizeof(arr);
  
  for (int i = 0; i < len; i ++) {
    int min = arr[i];
    
    for (int j = i + 1; j < len; j ++) {
      if (arr[j] < min) {
        min = arr[j];
      }
    }
    
    arr[i] = min;
  }
}
