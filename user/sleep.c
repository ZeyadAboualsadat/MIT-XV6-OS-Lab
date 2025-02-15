#include "user.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: sleep <ticks>\n");
        exit(1);
    }

    int ticks = atoi(argv[1]);
    if (ticks < 0) {
        printf("Error: ticks must be a non-negative integer\n");
        exit(1);
    }

    sleep(ticks);
    exit(0);
}

