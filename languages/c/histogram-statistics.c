#include <stdio.h>

/**
 * 绘制直方图
 * @param {int[]} 
 * @param {int nCount} 
 * @param {char ch} 
 */
void DrawHistogram (int nArray[], int nCount, char ch) {
    for (int i = 0; i < nCount; i++) {
        for (int j = 0; j < nArray[i]; j++)
            printf("%c", ch);
        printf(" %d\n", nArray[i]);
    }
    
    printf("\n");
}


/**
 * 计算范围量
 * @param {int []}
 * @param {int}
 * @param {int []}
 */
void CountRangeItems (int dArray[], int nDataItems, int nArray[]) {
    for (int i = 0; i < nDataItems; i++) {
        if (dArray[i] <= 160) { 
          nArray[0]++;
        } else if (dArray[i] < 165) {
          nArray[1]++;
        } else if (dArray[i] < 170) { 
          nArray[2]++;
        } else if (dArray[i] < 175) { 
          nArray[3]++;
        } else if (dArray[i] > 175) { 
          nArray[4]++;
        }
    }
}

int main () {
    int height[] = { 185, 176, 165, 169, 160, 152, 173, 196, 178, 169, 166, 182, 181, 171, 159, 163, 168 };
    int nArray[5] = { 0 };
    int nCount = 5,
        size = sizeof(height) / sizeof(height[0]);
    
    CountRangeItems(height, size, nArray);
    DrawHistogram(nArray, nCount, '*');
    getchar();
    
    return 0;
}
