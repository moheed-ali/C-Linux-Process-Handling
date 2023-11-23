#include <stdio.h> 

#include <stdlib.h> 

#include <sys/types.h> 

#include <unistd.h> 

#include <string.h> 

int main(int argc, char ** argv) 

{ 

  

    // int ret; 

    // char *cmd[] = { "ls", "-l", "-a", NULL}; 

  

  

  

    pid_t child; 

    pid_t parent = getpid(); 

  

    child = fork(); 

  

    if (child == -1 ){ 

      perror("fork"); 

      exit(-1); 

    } 

  

    if (child == 0 ){ 

      printf("I am a child my id %d, my parent id is %d\n", getpid(), getpid()); 

      // excel 

      // execl ("/bin/ls", "ls", "-a", "-l", NULL); // new line 

  

      // excecv 

  

      // char *cmd[] = { "ls", "-l", "-a", NULL}; // for static 

      // execv("/bin/ls", cmd); 

      /* 

      char** vec = (char **) malloc(4 * sizeof(char*)); 

      vec[0] = "ls"; 

      vec[1] = "-a"; 

      vec[2] = "-l"; 

      vec[3] = NULL; 

      execv("/bin/ls", vec); // for dynamic */ 

  

      char *cmd = argv[1]; 

  

      char** vec = (char **) malloc(4 * sizeof(char*)); 

      vec[0] = argv[2]; 

      vec[1] = argv[3]; 

      vec[2] = argv[4]; 

      vec[3] = NULL; 

  

      // printf("%s, \n",argv[1]); 

  

      execv(cmd, vec); // for dynamic "/bin/ls" ls -a -l 

      free(vec); 

  

      perror("excecv"); 

      exit(-2); // new line 

    } 

    else{ 

      printf("I am a parent my id %d, my child id is %d\n", parent, child); 

    } 

  

  

  

    // make two process which run same 

    // program after this instruction 

    // pid_t p = fork(); 

  

    // printf("Hello world!, process_id(pid) = %d \n",getpid()); 

  

  

  

    return 0; 

}

  

  

  
