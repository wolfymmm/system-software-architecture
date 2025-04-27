#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define ARRAY_SIZE 25000

int compare_ints(const void *a, const void *b) {
    int int_a = *(const int *)a;
    int int_b = *(const int *)b;
    return (int_a > int_b) - (int_a < int_b);
}


int sorted(const int *array, size_t size) {
    for (size_t i = 1; i < size; ++i) {
        if (array[i - 1] > array[i]) {
            return 0;
        }
    }
    return 1;
}

void generate_sorted_array(int *array, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        array[i] = (int)i;
    }
}


void generate_reverse_sorted_array(int *array, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        array[i] = (int)(size - i);
    }
}


void generate_identical_array(int *array, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        array[i] = 42;
    }
}


void generate_random_array(int *array, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        array[i] = rand();
    }
}


void test_sort(const char *test_name, void (*generator)(int *, size_t)) {
    int *array = malloc(ARRAY_SIZE * sizeof(int));
    if (!array) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    generator(array, ARRAY_SIZE);

    clock_t start = clock();
    qsort(array, ARRAY_SIZE, sizeof(int), compare_ints);
    clock_t end = clock();

    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;

    printf("Test: %-25s | Time: %.6f seconds | %s\n",
           test_name,
           time_spent,
           sorted(array, ARRAY_SIZE) ? "Sorted correctly" : "Sort FAILED!");

    free(array);
}

int main() {
    srand((unsigned int)time(NULL));

    printf("Testing qsort with different input patterns:\n\n");

    test_sort("Sorted array", generate_sorted_array);
    test_sort("Reverse sorted array", generate_reverse_sorted_array);
    test_sort("Identical elements array", generate_identical_array);
    test_sort("Random array", generate_random_array);

    return 0;
}
