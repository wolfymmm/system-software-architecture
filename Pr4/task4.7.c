#include <stdio.h>
#include <stdlib.h>

struct sbar {
    int x;
    int y;
};

int main() {
    struct sbar *ptr, *newptr;
    ptr = reallocarray(NULL, 1000, sizeof(struct sbar));
    if (ptr == NULL) {
        perror("Memory allocation failed");
        return 1;
    }

    newptr = reallocarray(ptr, 500, sizeof(struct sbar));
    if (newptr == NULL) {
        perror("Memory allocation failed");
        free(ptr);
        return 1;
    }
    newptr[0].x = 10;
    newptr[0].y = 20;

    printf("First element: x = %d, y = %d\n", newptr[0].x, newptr[0].y);

    free(newptr);

    return 0;
}

