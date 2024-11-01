#include "/root/xv6-labs-2024/kernel/types.h"
#include "/root/xv6-labs-2024/kernel/stat.h"  // Correct path to stat.h
#include "user.h"

#define MAX 37
#define FIRST_PRIME 2

int generate_natural();  // -> out_fd
int prime_filter(int in_fd, int prime);  // -> out_fd

int main(int argc, char *argv[]) {
    int prime; 
    int in = generate_natural();
    int pid;  // For storing the child process ID

    while (read(in, &prime, sizeof(int))) {
        printf("prime %d\n", prime);  // Output to standard output
        in = prime_filter(in, prime);
    }

    // Wait for the child processes to finish to prevent zombie processes
    while ((pid = wait(0)) > 0) {  // Pass 0 to ignore the exit status
        // Optionally, you could handle the exit status here
    }

    exit(0);  // Provide an exit status
}

int generate_natural() {
    int out_pipe[2];
    pipe(out_pipe);

    if (!fork()) {
        for (int i = FIRST_PRIME; i < MAX; i++) {
            write(out_pipe[1], &i, sizeof(int));
        }
        close(out_pipe[1]);
        exit(0);  // Provide an exit status
    }

    close(out_pipe[1]);
    return out_pipe[0];
}

// Prime filtering function
int prime_filter(int in_fd, int prime) {
    int num;
    int out_pipe[2];
    pipe(out_pipe);

    if (!fork()) {
        while (read(in_fd, &num, sizeof(int))) {
            if (num % prime) {
                write(out_pipe[1], &num, sizeof(int));
            }
        }
        close(in_fd);
        close(out_pipe[1]);
        exit(0);  // Provide an exit status
    }

    close(in_fd);
    close(out_pipe[1]);
    return out_pipe[0];
}
