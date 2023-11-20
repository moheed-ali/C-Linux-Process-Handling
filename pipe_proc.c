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

        char child_msg[MSG_SIZE] = "Hello from the child!";

        // Read the message from the parent through the parent-to-child pipe
        char parent_msg[MSG_SIZE];
        read(parentToChildPipe[0], parent_msg, sizeof(parent_msg));

        // Write a message to the parent through the child-to-parent pipe
        write(childToParentPipe[1], child_msg, strlen(child_msg) + 1);

        close(parentToChildPipe[0]); // Close read end after reading
        close(childToParentPipe[1]); // Close write end after writing

        printf("Child process (ID: %d, Parent ID: %d) received message from parent: %s\n", getpid(), getppid(), parent_msg);
        printf("Child process (ID: %d, Parent ID: %d) sent message: %s\n", getpid(), getppid(), child_msg);
        exit(EXIT_SUCCESS);
    } else {
        // Parent process
        close(parentToChildPipe[0]); // Close read end of parent-to-child pipe
        close(childToParentPipe[1]); // Close write end of child-to-parent pipe

        char parent_msg[MSG_SIZE] = "Hello from the parent!";

        // Write a message to the child through the parent-to-child pipe
        write(parentToChildPipe[1], parent_msg, strlen(parent_msg) + 1);

        // Read the message from the child through the child-to-parent pipe
        char child_msg[MSG_SIZE];
        read(childToParentPipe[0], child_msg, sizeof(child_msg));

        close(parentToChildPipe[1]); // Close write end after writing
        close(childToParentPipe[0]); // Close read end after reading

        printf("Parent process (ID: %d, Child ID: %d) sent message: %s\n", parent, child, parent_msg);
        printf("Parent process (ID: %d, Child ID: %d) received message from child: %s\n", parent, child, child_msg);

        for (;;) {
            // Parent process can do other tasks here
        }
    }

    return 0;
}

