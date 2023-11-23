#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char child_msg[100]; // Assuming a maximum length for the input string
    fgets(child_msg, sizeof(child_msg), stdin);

    // Tokenize the input string
    char** vec = malloc(sizeof(char*)); // Allocate memory for the array of strings
    int count = 0;

    char* token = strtok(child_msg, " ");
    while (token != NULL) {
        // Allocate memory for each word and copy the token
        vec[count] = malloc(strlen(token) + 1);
        strcpy(vec[count], token);

        // Resize the array of strings
        vec = realloc(vec, (count + 2) * sizeof(char*));

        // Move to the next token
        token = strtok(NULL, " ");
        count++;
    }

    // vec[count] is set to NULL to indicate the end of the array
    vec[count] = NULL;

    // Extract the command (first word) and print it
    char* cmd = NULL;
    if (count > 0) {
        cmd = vec[0];
        printf("cmd: %s\n", cmd);

        // Free the memory allocated for vec[0]
        free(vec[0]);

        // Shift the remaining elements to fill the gap
        for (int i = 0; i < count; i++) {
            vec[i] = vec[i + 1];
        }

        // Resize the array of strings
        vec = realloc(vec, count * sizeof(char*));
    }

    // Print the rest of the words in vec
    for (int i = 0; vec[i] != NULL; i++) {
        printf("vec[%d]: %s\n", i, vec[i]);
    }

    // Free the allocated memory
    for (int i = 0; i < count; i++) {
        free(vec[i]);
    }
    free(vec);

    return 0;
}

