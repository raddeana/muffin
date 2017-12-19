#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void printInfo(pid_t ret);

int main () 
{
  pid_t ret = fork();
  int status;

  if (ret < 0) {
    perror("create process failed\n");
  } else if (ret == 0) {
    printf("in child process %d\n", getpid());

    pid_t insert = execlp("./insert", "./insert", NULL);
    pid_t hinsert = execlp("./hinsert", "./hinsert", NULL);
    pid_t heap = execlp("./heap", "./heap", NULL);
    pid_t bubble = execlp("./bubble", "./bubble", NULL);
    pid_t merge = execlp("./merge", "./merge", NULL);
    pid_t selection = execlp("./selection", "./selection", NULL);
    pid_t shell = execlp("./shell", "./shell", NULL);
    pid_t quick = execlp("./quick", "./quick", NULL);

    printInfo(insert);
    printInfo(hinsert);
    printInfo(heap);
    printInfo(bubble);
    printInfo(merge);
    printInfo(selection);
    printInfo(shell);
    printInfo(quick);

    return 0;
  }
}

/**
 * 输出线程信息
 */
void printInfo(pid_t ret) 
{
  if(ret >= 0) {
    printf("execute process childprocess sucessfully!\n");
  }
  else if (ret > 0) {
    printf("in parent prcess %d\n\n\n", getpid());
    waitpid(ret, &status, 0);
    printf("\n\nin the parent process\n");
  }
  else {
    printf("execute process childprocess failed!\n");
    printf("after exec\n");
  }
}