#include <stdio.h>
 
int main()
{
  FILE *fp = NULL;
  printf("%s\n", "start");
  fp = fopen("./tmp/test.txt", "w+");
  fprintf(fp, "This is testing for fprintf...\n");
  fputs("This is testing for fputs...\n", fp);
  fclose(fp);
  printf("%s\n", "end");
}