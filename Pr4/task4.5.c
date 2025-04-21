#include <stdio.h>
#include <stdlib.h>

int main() {
    int *ptr = malloc(5 * sizeof(int));
    if (!ptr) {
        printf("Memory allocation failed\n");
        return 1;
    }
    for (int i = 0; i < 5; i++) {
        ptr[i] = i + 1;
    }
    ptr = realloc(ptr, 100000000000 * sizeof(int));

    if (!ptr) {
        printf("Reallocation failed\n");
    } else {
        printf("Reallocation successful\n");
        free(ptr);
    }

    return 0;
}
