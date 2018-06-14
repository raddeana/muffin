#include <stdio.h>

/**
 * 绘制直方图
 * @param {int []}
 * @param {int}
 * @param {char}
 */
void DrawHistogram(int nArray[], int nCount, char ch) {
    for (int i = 0; i < nCount; i++) {
        for (int j = 0; j < nArray[i]; j++)
            printf("%c", ch);
        printf(" %d\n", nArray[i]);
    }
    
    printf("\n");
}

/**
 * 范围量计算
 * @param {int []}
 * @param {int}
 * @param {int []}
 */
void CountRangeItems(int dArray[], int nDataItems, int nArray[]) {
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

int main() {
    int height[] = { 158, 176, 165, 159, 160, 182, 173, 159, 178, 169, 166, 182, 179, 171, 159, 166, 157, 176, 171, 159 };
    int nArray[5] = { 0 };
    int nCount = 5, size = sizeof(height) / sizeof(height[0]);
    CountRangeItems(height, size, nArray);
    DrawHistogram(nArray, nCount, '*');
    printf("\n");

    // 直方图归一化
    float histPDF[] = { 0 };
    printf("直方图归一化：\n");
    
    for (int i = 0; i < nCount; i++) {
        histPDF[i] = float(nArray[i])/20.0;
        // printf(" (%d) ", nArray[i]);
        printf("%.2f ", histPDF[i]);
    }

    // 累积直方图
    printf("\n累积直方图：\n");
    float histCDF[] = { 0 };
    
    for (int i = 0; i < nCount; i++) {
        if (0 == i)
            histCDF[i] = histPDF[i];
        else 
            histCDF[i] = histCDF[i - 1] + histPDF[i];
        printf("%.2f ",histCDF[i]);

    }
    
    // 直方图均衡化，映射
    printf("\n直方图均衡化：\n");
    int histEQU[] = {0};
    
    for (int i = 0; i < nCount; i++) {
        histEQU[i] = (int)(5.0 * histCDF[i] + 0.5);
        printf("%d ",histEQU[i]);
    }
    
    getchar();
    return 0;
}
