#include <stdio.h>
#include <stdlib.h>

int main() {
    size_t size = 1024 * 1024 * 1024; // Запит на 1 ГБ пам'яті
    void *ptr = malloc(size);

    if (ptr == NULL) {
        printf("Memory allocation failed\n");
    } else {
        printf("Memory allocated successfully\n");

        free(ptr);
        printf("Memory freed successfully\n");
    }

    return 0;
}
