#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <memory_in_MB>\n", argv[0]);
        return 1;
    }

    long long memory_to_allocate = atoll(argv[1]) * 1024 * 1024; 

    char *memory = malloc(memory_to_allocate);

    if (memory == NULL) {
        perror("malloc failed");
        return 1;
    }

    printf("Allocated %lld bytes (%lld MB). Press Enter to continue and use the memory.\n", memory_to_allocate, memory_to_allocate / (1024 * 1024));
    getchar(); 

    for (long long i = 0; i < memory_to_allocate; i += 4096) { 
        memory[i] = 1;
    }

    printf("Memory touched. Sleeping indefinitely. Use Ctrl+C to terminate.\n");
    while (1) {
        sleep(1);
    }

    free(memory); 
    return 0;
}
