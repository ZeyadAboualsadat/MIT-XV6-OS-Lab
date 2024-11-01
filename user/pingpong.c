#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main() {
    int p[2]; // Array to hold the two ends of the pipe
    char byte = 'a'; // Byte to send

    // Create a pipe
    if (pipe(p) < 0) {
        fprintf(2, "pipe error\n");
        exit(1);
    }

    int pid = fork(); // Create a child process

    if (pid < 0) {
        fprintf(2, "fork error\n");
        exit(1);
    }

    if (pid == 0) { // Child process
        // Close the write end of the pipe
        close(p[1]);
        
        // Read the byte from the pipe
        read(p[0], &byte, 1);
        printf("%d: received ping\n", getpid());

        // Close the read end of the pipe
        close(p[0]);

        // Exit the child process
        exit(0);
    } else { // Parent process
        // Close the read end of the pipe
        close(p[0]);

        // Write the byte to the pipe
        write(p[1], &byte, 1);
        printf("%d: received pong\n", getpid());

        // Close the write end of the pipe
        close(p[1]);

        // Wait for the child process to finish
        wait(0);
    }
    return 0;
}

