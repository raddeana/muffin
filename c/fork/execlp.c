#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main () {
  pid_t ret = fork();
  int status;

  if (ret < 0) {
    perror("create process failed\n");
  } else if(ret == 0) {
    printf("in child process %d\n",getpid());

    if((ret = execlp("./childprocess", "./childprocess", NULL)) >= 0) {
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

    return 0;
  }
}