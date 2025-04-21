#include <stdio.h>
#include <stdlib.h>

int main() {
    void *ptr = NULL;
    int n = 10;

    ptr = malloc(n);
    if (!ptr) {
        printf("Memory allocation failed\n");
        return 1;
    }

    while (1) {
        if (ptr) {
            printf("Using memory at address: %p\n", ptr);
        }

        free(ptr);
        ptr = NULL;

        break;
    }
    return 0;
}