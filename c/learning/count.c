#include <stdio.h>

int main () {
  int c, nl;
  nl = 0;

  printf("EOF is %d\n", EOF);

  while ((c = getchar()) != EOF) {
    if (c == '\n') {
      ++nl;
    }
  }

  printf("%d\n", nl);
}