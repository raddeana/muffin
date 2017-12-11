#include <stdio.h>

int main(){   
  FILE *fp = NULL;
  fp = fopen("./tmp/test.txt", "r+");
  
  fprintf(fp, "This is testing for fseek...\n");   
  fseek(fp, 10, SEEK_SET);

  if (fputc(65, fp) == EOF) {
    printf("fputc fail");   
  }   
  
  fclose(fp);
}