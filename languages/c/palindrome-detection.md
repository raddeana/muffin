#### 字符串回文检测
```c
#include "stdio.h"
#include "string.h"
  
  
int f (char *s) {
  int i, j;
  j = strlen(s);  
  j--;  
  
  for(i = 0; i < j && s[i] == s[j]; i ++, j --);  
  
  if(i >= j) {
    return 1;
  }
  
  return 0;
}  
  
  
main () {
  char s[80];  
  gets(s);  

  if(f(s) == 1) { 
    printf("YES");
  } else {  
    printf("NO");  
  }
}  
```

#### 把字符串转换成浮点数
```c
#include "stdafx.h"  
#include <iostream>  
  
/**
 * 字符转数字
 * @param {char} 字符
 * @return {int} 数字
 */
int atoi (char sptr) {  
  int atoI = 0;  

  switch (sptr) {
  case '1':
    atoI = 1;
    break;
  case '2':
    atoI = 2;
    break;
  case '3':
    atoI = 3;
    break;
  case '4':
    atoI = 4;
    break;
  case '5': 
    atoI = 5;
    break;
  case '6':
    atoI = 6;
    break;
  case '7':
    atoI = 7;
    break;
  case '8':
    atoI = 8;
    break;
  case '9':
    atoI = 9;
    break;
  case '0':
    atoI = 0;
    break;
  }

  return atoI;
}

/**
 * 字符串转浮点
 * @param {char *} 字符串
 * @return {double} 浮点类型
 */
double myatof (char *str) {  
  double sum = 0;  
  int num = 0, 
      flag = 0;  

  if (*str == '-') {  
    str ++;

    while (*str != '\0') {
      if ((*str != '0') && 
          (*str != '1') && 
          (*str != '2') && 
          (*str != '3') && 
          (*str != '4') && 
          (*str != '5') && 
          (*str != '6') && 
          (*str != '7') && 
          (*str != '8') && 
          (*str != '9') && 
          (*str != '.')) {
        printf("falsh input!\n");
        return 0;
      } else {
        if (*str == '.') {
          flag = 1;
          str++;
        } else {
          if (flag == 0) {
            num = atoi(*str);
            sum = sum * 10 + num;
            str++;
          }

          if (flag == 1){  
            num = atoi(*str);  
            sum = sum + num / 10;  
            str++;
          }  
        }  
      }
    }

    return -sum;  
  } else {
    while (*str != '\0') {
      if ((*str != '0') && (*str != '1') && (*str != '2') && (*str != '3')  
          && (*str != '4') && (*str != '5') && (*str != '6') && (*str != '7')  
          && (*str != '8') && (*str != '9') && (*str != '.')) {  
        printf("falsh input!\n");  
        return 0;  
      } else {  
        if (*str == '.'){  
          flag = 1;
          str ++;
        } else {  
          if (flag == 0) {  
            num = atoi(*str);  
            sum = sum * 10 + num;  
            str++;
          }

          if (flag == 1) {
            num = atoi(*str);  
            sum = sum + num / 10;  
            str++;  
          }  
        }
      }
    }

    return sum;  
  }
}

/**
 * 主函数
 * @return {int}
 */
int _tmain (int argc, _TCHAR* argv[]) {
  char *String1 = "1a2345";
  char *String2 = "123.45";

  double Sum1 = 0,
         Sum2 = 0;

  Sum1 = myatof(String1);
  printf("%f\n", Sum1);

  Sum2 = myatof(String2);
  printf("%f\n", Sum2);

  while (1);
  return 0;
}  

```
