/*reverse input using pipes*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void reverseString(char *str) {
    int length = strlen(str);

    for (int i = 0, j = length - 1; i < j; i++, j--) {
        // Swap characters at positions i and j
        char temp = str[i];
        str[i] = str[j];
        str[j] = temp;
    }
}

int main() {
    int pipe_fd[2]; // File descriptors for the pipe
    char input[100];
    
    // Create a pipe
    if (pipe(pipe_fd) == -1) {
        perror("Pipe creation failed");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork(); // Create a child process

    if (pid == -1) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) { // Child process
        close(pipe_fd[1]); // Close the write end of the pipe
        
        // Read the string from the parent process
        read(pipe_fd[0], input, sizeof(input));
        
        printf("Child Process - Received string from parent: %s\n", input);
        
        reverseString(input);

        printf("Child Process - Reversed string: %s\n", input);
        
        close(pipe_fd[0]); // Close the read end of the pipe in the child process
    } else { // Parent process
        close(pipe_fd[0]); // Close the read end of the pipe
        
        printf("Enter a string: ");
        scanf("%s", input);
        
        // Send the string to the child process through the pipe
        write(pipe_fd[1], input, sizeof(input));
        
        close(pipe_fd[1]); // Close the write end of the pipe in the parent process
    }

    return 0;
}