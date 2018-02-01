#include <stdio.h>

void selection (int arr[]);

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
