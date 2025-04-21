#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int n = 10;

    // Використання calloc
    int *arr1 = (int *)calloc(n, sizeof(int));
    if (!arr1) {
        printf("calloc failed\n");
        return 1;
    }

    // Використання malloc + memset
    int *arr2 = (int *)malloc(n * sizeof(int));
    if (!arr2) {
        printf("malloc failed\n");
        free(arr1);
        return 1;
    }
    memset(arr2, 0, n * sizeof(int));

    int equal = 1;
    for (int i = 0; i < n; i++) {
        if (arr1[i] != arr2[i]) {
            equal = 0;
            break;
        }
    }

    if (equal) {
        printf("calloc and malloc+memset produce the same result\n");
    } else {
        printf("Results differ\n");
    }

    free(arr1);
    free(arr2);

    return 0;
}
