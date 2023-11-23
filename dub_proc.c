#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

#define MSG_SIZE 256

int main() {
    pid_t child = 0;
    pid_t parent = getpid();

    // Create two pipes
    int parentToChildPipe[2];
    int childToParentPipe[2];

    if (pipe(parentToChildPipe) == -1 || pipe(childToParentPipe) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    child = fork();

    if (child == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (child == 0) {
        // Child process
        close(parentToChildPipe[1]); // Close write end of parent-to-child pipe
        close(childToParentPipe[0]); // Close read end of child-to-parent pipe

        // Redirect standard input to read from the parent-to-child pipe
        dup2(parentToChildPipe[0], STDIN_FILENO);
        close(parentToChildPipe[0]);

        // Redirect standard output to write to the child-to-parent pipe
        dup2(childToParentPipe[1], STDOUT_FILENO);
        close(childToParentPipe[1]);

        char child_msg[MSG_SIZE];

        // Read the message from the redirected standard input
        fgets(child_msg, sizeof(child_msg), stdin);
        
        

        // Display the message on the terminal through the redirected standard output
        printf("%s", child_msg);    

	
        // Flush the standard output and exit
        fflush(stdout);
        
        exit(EXIT_SUCCESS);
    } else {
        // Parent process
        close(parentToChildPipe[0]); // Close read end of parent-to-child pipe
        close(childToParentPipe[1]); // Close write end of child-to-parent pipe

        char parent_msg[MSG_SIZE];

        // Get input from the user
        printf("Enter a message for the child: ");
        fgets(parent_msg, sizeof(parent_msg), stdin);

        // Write a message to the parent-to-child pipe
        write(parentToChildPipe[1], parent_msg, strlen(parent_msg) + 1);
        close(parentToChildPipe[1]); // Close write end after writing

        // Read the message from the child-to-parent pipe
        char child_msg[MSG_SIZE];
        read(childToParentPipe[0], child_msg, sizeof(child_msg));
        close(childToParentPipe[0]); // Close read end after reading

        printf("Parent process (ID: %d, Child ID: %d): %s\n", parent, child, child_msg);

        //for (;;) {
            // Parent process can do other tasks here
        //}
    }

    return 0;
}

