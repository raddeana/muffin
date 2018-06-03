### 稀疏矩阵节点
#### 定义数据结构
- 节点
```c
// 定义三元组表的节点  
typedef struct{  
  int i,j;  
  int v;  
} SPNode;
```

- 矩阵
```c
// 定义三元组表  
typedef struct {
  int mu,nu,tu;
  SPNode data[SMAX];
} SPMatrix;
```

#### 具体实现
- 为了便于 B.data 寻找第k行第一个非零元素，在此引入num和rpot两个内容
- num[k] 表示矩阵B中第k行非零元素的个数
- rpot[k] 表示第k行的第一个非零元素在B.data中的位置

```c
/* 
 * 进行两个稀疏矩阵之间的乘法
 * @author n/a
 */  
#include <stdio.h>
#include <malloc.h>
#define SMAX 1024

// 定义三元组表的节点
typedef struct {
  int i, j;
  int v;
} SPNode;

// 定义三元组表  
typedef struct {
  int mu, nu, tu;
  SPNode data[SMAX];
} SPMatrix;

// 进行两个稀疏矩阵之间的乘法, 返回值为乘积矩阵
SPMatrix * MulSMatrix(SPMatrix *A, SPMatrix *B) {
  SPMatrix *C;
  int p, j, q, i, r, k, t;

  // 用于结果的暂存
  int temp[B -> nu + 1];

  int num[B -> mu + 1],
      rpot[B -> mu + 1];

  C = (SPMatrix*)malloc(sizeof(SPMatrix)); 
  
  if (C == NULL) {
    printf("申请内存空间失败！\n");
    return NULL;
  }

  // A的列值与B的行值不相等时
  if(A -> nu != B -> mu) {
    return NULL;
  }

  C->mu = A->mu;  
  C->nu = B->nu;  
  
  // 当A或B中的非零元素为0时  
  if(A -> tu*B -> tu == 0){
    C->tu = 0;
    return C;
  }

  // 计算B矩阵中每行非0元素的个数
  for(i = 1;i <= B -> mu;i++) {
    num[i] = 0;
  }

  for(i = 0;i<B->tu;i++) {
    num[B->data[i].i]++;
  }

  rpot[1] = 0;

  // 计算B矩阵中每行首位非0元素的位置  
  for (i = 2; i <= B->mu; i ++) {  
    rpot[i] = rpot[i-1]+num[i-1];
  }

  r = 0;  // 记录当前C矩阵中非0元素的个数  
  p = 0;  // 指示当前A矩阵中非零元素的位置  
  
  // 进行矩阵的乘积运算  
  for(i = 1;i <= A->mu; i ++) {
    // 将Cij的累加器初始化 
    for(j = 1;j <= B->nu; j ++) {  
        temp[j] = 0;  
    }

    // 求Cij第i行的元素集合  
    while (i == A->data[p].i) {
      k = A->data[p].j;
    }

    // 获取A矩阵中第p个非零元素的列值  
    // 确定B中的k行的非零元素在B.data中的下限位置  
    if (k < B->mu) {
      t = rpot[k+1];
    } else {
      t = B->tu;
    }

    // 将B中第k行的每一列非零元素与A中非零元素记录到累加器中  
    for (q = rpot[k]; q < t; q ++){  
      j = B->data[q].j;  
      temp[j] += A->data[p].v*B->data[q].v;  
    }

    p++;

    // 将第i行的结果赋值给C矩阵  
    for (j = 1; j <= B->nu; j++) {  
      if (temp[j] != 0) {
        C->data[r] = { i, j, temp[j] };  
        r ++;
      }
    }
  }

  C->tu = r;
  return C;
}
```
