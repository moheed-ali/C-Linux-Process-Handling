




#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

#define MSG_SIZE 256

int main() {
    pid_t child = 0;
    pid_t parent = getpid();

    // Create a pipe
    int pipe_fd[2];
    if (pipe(pipe_fd) == -1) {
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
        close(pipe_fd[0]); // Close unused read end

        char child_msg[MSG_SIZE] = "Hello from the child!";

        // Write the message to the pipe
        write(pipe_fd[1], child_msg, strlen(child_msg) + 1);

        // Read the message from the parent through the pipe
        char parent_msg[MSG_SIZE];
        read(pipe_fd[1], parent_msg, sizeof(parent_msg));

        close(pipe_fd[1]); // Close write end after reading

        printf("Child process (ID: %d, Parent ID: %d) sent message: %s\n", getpid(), getppid(), child_msg);
        printf("Child process (ID: %d, Parent ID: %d) received message from parent: %s\n", getpid(), getppid(), parent_msg);
        exit(EXIT_SUCCESS);
    } else {
        // Parent process
        close(pipe_fd[1]); // Close unused write end

        char parent_msg[MSG_SIZE] = "Hello from the parent!";

        // Write the message to the pipe
        write(pipe_fd[0], parent_msg, strlen(parent_msg) + 1);

        // Read the message from the child through the pipe
        char child_msg[MSG_SIZE];
        read(pipe_fd[0], child_msg, sizeof(child_msg));

        close(pipe_fd[0]); // Close read end after reading

        printf("Parent process (ID: %d, Child ID: %d) sent message: %s\n", parent, child, parent_msg);
        printf("Parent process (ID: %d, Child ID: %d) received message from child: %s\n", parent, child, child_msg);

        for (;;) {
            // Parent process can do other tasks here
        }
    }

    return 0;
}