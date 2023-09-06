/*factorial using pipes*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int factorial(int n) {
    if (n == 0 || n == 1) {
        return 1;
    } else {
        return n * factorial(n - 1);
    }
}

int main() {
    int pipe_fd[2]; // File descriptors for the pipe
    int num;
    
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
        
        // Read the number from the parent process
        read(pipe_fd[0], &num, sizeof(num));
        
        int result = factorial(num);
        
        printf("Child Process - Factorial of %d is %d\n", num, result);
        
        close(pipe_fd[0]); // Close the read end of the pipe in the child process
    } else { // Parent process
        close(pipe_fd[0]); // Close the read end of the pipe
        
        printf("Enter a positive integer: ");
        scanf("%d", &num);
        
        // Send the number to the child process through the pipe
        write(pipe_fd[1], &num, sizeof(num));
        
        close(pipe_fd[1]); // Close the write end of the pipe in the parent process
    }

    return 0;
}