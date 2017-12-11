#include <stdio.h>
 
/* 函数声明 */
void func1(void);
 
static int count=10;        /* 全局变量 - static 是默认的 */
 
int main () {
  while (count--) {
    func1();
  }

  return 0;
}
 
void func1 (void) {        
  static int thingy = 5;
  thingy ++;
  printf(" thingy 为 %d ， count 为 %d\n", thingy, count);
}