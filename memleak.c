#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    printf("Starting infinite memory leak...\n");
    fflush(stdout);
    int i = 0;

    while (1) {
        void *leak = malloc(100 * 1024 * 1024);

        if (leak == NULL) {
            fprintf(stderr, "Memory allocation failed. Out of memory!\n");
            break;
        }

        for (int i = 0; i < (100 * 1024 * 1024) / sizeof(int); i++) {
            ((int *)leak)[i] = i;
        }

        i+=100;

        printf("Allocated %dMB. Leaking memory...\n",i);
        fflush(stdout);
        sleep(1);
    }

    return 0;
}
