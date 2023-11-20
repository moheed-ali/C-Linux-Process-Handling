#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

int main(){

    pid_t child = 0;
    pid_t parent = getpid();

    child = fork();


    if (child == -1 ){
      perror("fork");
      exit(-1);
    }

    if (child == 0 ){
      printf("I am a Child my id  is %d, my parent id is %d\n", getpid(), getppid());
      perror("fork");
      exit(1);
    }

    else{
      printf("I am a parent my id is %d, my Child id is %d\n", parent, child);
    }

    for(;;);

    return 0;
}
