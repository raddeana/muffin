#include <stdio.h>
 
// 变量声明
extern int a, b;
extern int c;
extern float f;

void show ();
 
int main () {
  /* 变量定义 */
  int a, b;
  int c;
  float f = 10;
 
  /* 初始化 */
  a = 10;
  b = 20;
  
  c = a + b;
  printf("value of c : %d \n", c); 
  printf("value of f : %f \n", f);  

  return 0;
}


