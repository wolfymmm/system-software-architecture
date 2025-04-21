#include <stdio.h>
#include <stdlib.h>

int main() {
    // realloc з NULL
    int *ptr = realloc(NULL, 5 * sizeof(int));
    if (ptr) {
        printf("Memory allocated with realloc(NULL, size)\n");
        free(ptr);
    } else {
        printf("Memory allocation failed with realloc(NULL, size)\n");
    }

    // realloc з розміром 0
    int *ptr2 = malloc(5 * sizeof(int));
    if (ptr2) {
        printf("Memory allocated for ptr2\n");

        ptr2 = realloc(ptr2, 0);
        if (ptr2 == NULL) {
            printf("Memory freed with realloc(ptr, 0)\n");
        }
    }

    return 0;
}
