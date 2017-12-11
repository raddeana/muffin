/**
 * 输入输出
 * @author mulberry
 */

#include <stdio.h>

int main () {
    int c;
    c = getchar(); 
    
    while (c != EOF) {
      putchar(c);
      c = getchar();
    }
}