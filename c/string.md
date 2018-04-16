#### 字符串是零个或多个字符组成的有限序列
#### 一般记S=‘a1a2....an ’其中，S是串名，单引号括起的字符序列是串值；ai（1〈=i〈=n）可以是字母，数字或其它字符；串中所包含的字符个数为该串的长度
#### 长度为零的串称为空串，它不包含任何字符

##### 结构体
```c
#include <stdio.h>
#define STRINGMAX 100
typedef struct
{
    char vec[STRINGMAX];  
    int len;         //储存串的实际数据的长度而不是下标；  
                     /**（顺便提示一句：往往需要在字符串的末尾加一个结束标志'\0'而这个标志在操作中不算做实际数据，除在某些操作中作为循环结束条件，其它都将这个标志看为空的；）**/  
} str;               //定义一个串结构的结构体
```

##### 字符串链接
```c
/**
 * 将两个字符串链接起来
 * @param {str} 字符串1
 * @param {str} 字符串2
 * @return {void}
 */
void Concarstr (str *r1, str *r2) {
    int i;
    printf("\n\t\tr1=%s \t\t  r2=%s", r1->vec, r2->vec);
    
    if(r1 -> len+r2 -> len > STRINGMAX) {
        printf("\n\t\t两个串太长，溢出！\n");  
    } else {
        for(i = 0; i < r2 -> len; i++) {
            r1->vec[r1 -> len+i] = r2 -> vec[i];      // 将r2的字符逐个赋值到r1的尾部；r1 -> len 储存的不是实际数据而是结束标志'\0'
        }
        
        r1 -> vec[r1->len+i] = '\0';                  // 在新串的末尾加一个结束标志'\0',（链接时覆盖掉这个数据）
        r1 -> len=r1->len+r2 -> len;
    }
}
```

##### 获取子字符串
```c
/**
 * 获取子串
 * @param {str} 字符串
 * @param {int} 子串开始位置
 * @param {int} 子串结束位置
 * @return {void}
 */
void Substr (str *r, int i, int j) {  
    int k;
    str a;                                // 因为下面的指针r1需要一个空间；  
    str *r1 = &a;  
  
    if(i+j-1 > r->len) {  
        printf("\n\t\t子串超界!\n");  
    } else {  
        for(k = 0; k < j; k ++) {  
            r1->vec[k] = r->vec[i+k-1];   // 位置-1即为所需下标；  
        }
        
        r1->len=j;
        r1->vec[r1->len] = '0';
        printf("\n\t\t取出字符为：");
        puts(r1->vec);
    }  
}  
```

##### 删除子字符串串
```c
/**
 * 删除子串
 * @param {str} 字符串
 * @param {int} 子串开始位置
 * @param {int} 子串结束位置
 * @return {void}
 */
void Delstr (str *r, int i ,int j)      // 删除子串；  
{  
    int k;
    
    if(i-1+j>=r->len)                   // r->vec[r->len]储存了字符串的结束标志'0'，并不算做实际数据，所以应当把这种情况算作越界；  
    {  
        printf("要删除的子串超界");  
    } else {  
        for(k= i-1-j; k < r->len; k ++, i ++) // i-1为位置i的坐标表示，k为需删除数据后面的数据；  
        {  
            r->vec[i-1] = r->vec[k];  // 用后面的数据覆盖前面需要删除的数据；  
        }  
        r->len = r->len-j;            // 设置字符串r的新长度；  
        r->vec[r->len] = '0';         // 无论原串需删除的数据有没有被后面的数据完全覆盖（可能存在后面的数据不足完全覆盖需删除数据的情况）；  
                                      // 在新串的r->vec[r->len]赋值结束标志'0'，这时无论后面还存不存需删除的数据，都等同于无；  
    }
}
```

##### 插入子字符串
```c
/**
 * 插入子串
 * @param {str} 父字符串
 * @param {str} 子字符串
 * @param {int} 插入位置
 * @return {void}
 */
str Insstr(str *r, str *r1, int i) {  
    int k;
  
    if(i>=r->len || r->len+r1->len>STRINGMAX) {
        printf("\n\t\t不能插入！\n");  
    } else {  
        for(k=r->len-1;k>=i-1;i--)  
        {  
            r->vec[r1->len-1+k] = r->vec[k];          // 利用循环从串r的最后一个实际元素开始，向后移动r1->len个单位；  
        }  
        for(k=0;k<r1->len;k++)  
        {  
            r->vec[i-1+k] = r1->vec[k];               // 从插入位置开始，利用循环将r1的实际元素逐个赋值给r；  
        }  
    }  
}
```

##### 字符串模式匹配
```c
/**
 * 字符串模糊匹配
 * @param {str} 父字符串
 * @param {str} 子字符串
 * @return {int} 子字符串开始位置
 */
int Indexstr (str *r, str *r1) {
    int i, j, k;  
  
    for(i = 0;r -> vec[i];i ++)                            // 主串的结束标志作为循环终止条件；  
    {  
        for(j=i,k=0;r->vec[j]==r1->vec[k];j++,i++)         // 将i值交给j用于保护i值，记录位置；把r->vec[j]==r1->vec[k];作为循环条件，若匹配则继续循环，否则退出内层循环；  
        {  
            if(!r1->vec[k+1])                              // 利用结束标志，判断子串r1的实际数据是否完全与主串r匹配；  
            {  
                return i;                                  // 如果完全与主串匹配，怎返回位置i，结束函数；  
            }  
        }  
    }
    
    return -1;  
}
```
