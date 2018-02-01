#include <stdio.h>

void insert (int arr[]);

/**
 * 插入排序
 * @param {int[]} 排序整形数组 
 */
void insert (int arr[]) {
  int len = sizeof(arr);
  
  for (int i = 1; i < len; i ++) {
    int val = arr[i];
    int j = i - 1;
    
    arr[i] = arr[j];
    
    while(j >= 0 && val < arr[j]) {
      arr[j] = arr[j + 1];
      j --;
    }
    
    arr[j + 1] = val;
  }
}

int arr[] = { 3, 4, 5, 1, 2, 3, 0, 9 };
