#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main() {
    size_t size = (size_t)-1;
    void *ptr;

    while (1) {
        ptr = malloc(size);
        if (ptr == NULL) {
            printf("Unable to allocate memory for size: %zu bytes   :(\n", size);
            break;
        } else {
            printf("Successfully allocated memory for size: %zu bytes\n", size);
            free(ptr);
        }
        size /= 2;
    }

    return 0;
}
