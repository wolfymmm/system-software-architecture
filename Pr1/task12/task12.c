#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Function to fill an array with random values
void fill_array(void *arr, size_t size, size_t elem_size, int type) {
    for (size_t i = 0; i < size; i++) {
        if (type == 0) { // int
            *((int*)arr + i) = rand() % 100;
        } else if (type == 1) { // float
            *((float*)arr + i) = (float)rand() / RAND_MAX * 100.0;
        } else if (type == 2) { // char
            *((char*)arr + i) = 'A' + rand() % 26;
        }
    }
}

// Recursive function
int recursive_search(void *arr, void *value, size_t size, size_t elem_size, int type) {
    if (size == 0) return -1;
    if (type == 0 && *((int*)arr) == *((int*)value)) return 0;
    if (type == 1 && *((float*)arr) == *((float*)value)) return 0;
    if (type == 2 && *((char*)arr) == *((char*)value)) return 0;
    int result = recursive_search((char*)arr + elem_size, value, size - 1, elem_size, type);
    return result == -1 ? -1 : result + 1;
}

// Function for binary search
int binary_search(void *arr, void *value, size_t size, size_t elem_size, int type) {
    size_t low = 0, high = size - 1;
    while (low <= high) {
        size_t mid = low + (high - low) / 2; // Calculate the middle index
        void *mid_val = (char*)arr + mid * elem_size; // Get the middle element
        if (type == 0 && *((int*)mid_val) == *((int*)value)) return mid;
        if (type == 1 && *((float*)mid_val) == *((float*)value)) return mid;
        if (type == 2 && *((char*)mid_val) == *((char*)value)) return mid;
        if (type == 0 && *((int*)mid_val) < *((int*)value)) low = mid + 1;
        else if (type == 1 && *((float*)mid_val) < *((float*)value)) low = mid + 1;
        else if (type == 2 && *((char*)mid_val) < *((char*)value)) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}

// Function to print the array
void print_array(void *arr, size_t size, size_t elem_size, int type) {
    for (size_t i = 0; i < size; i++) {
        if (type == 0) printf("%d ", *((int*)arr + i));
        else if (type == 1) printf("%.2f ", *((float*)arr + i));
        else if (type == 2) printf("%c ", *((char*)arr + i));
    }
    printf("\n");
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <array size> <data type (0 - int, 1 - float, 2 - char)>\n", argv[0]);
        return 1;
    }

    size_t size = atoi(argv[1]); // Get the array size from command line
    int type = atoi(argv[2]); // Get the data type from command line

    if (type < 0 || type > 2) {
        printf("Invalid data type. Choose 0 (int), 1 (float), or 2 (char).\n");
        return 1;
    }

    void *arr; // Pointer to the array
    size_t elem_size; // Size of one element in the array

    // Allocate memory based on the data type
    if (type == 0) {
        arr = malloc(size * sizeof(int));
        elem_size = sizeof(int);
    } else if (type == 1) {
        arr = malloc(size * sizeof(float));
        elem_size = sizeof(float);
    } else if (type == 2) {
        arr = malloc(size * sizeof(char));
        elem_size = sizeof(char);
    }

    srand(time(NULL)); // Seed the random number generator
    fill_array(arr, size, elem_size, type);

    printf("Array: ");
    print_array(arr, size, elem_size, type);

    void *value = malloc(elem_size); // Allocate memory for the search value
    printf("Enter the value to search: ");
    if (type == 0) scanf("%d", (int*)value);
    else if (type == 1) scanf("%f", (float*)value);
    else if (type == 2) scanf(" %c", (char*)value);

    int index = recursive_search(arr, value, size, elem_size, type);
    if (index != -1) {
        printf("Value found at index %d (recursive search).\n", index);
    } else {
        printf("Value not found (recursive search).\n");
    }

    // Sort the array for binary search
    if (type == 0) qsort(arr, size, elem_size, (int(*)(const void*, const void*))strcmp);
    else if (type == 1) qsort(arr, size, elem_size, (int(*)(const void*, const void*))strcmp);
    else if (type == 2) qsort(arr, size, elem_size, (int(*)(const void*, const void*))strcmp);

    printf("Sorted array: ");
    print_array(arr, size, elem_size, type);

    index = binary_search(arr, value, size, elem_size, type);
    if (index != -1) {
        printf("Value found at index %d (binary search).\n", index);
    } else {
        printf("Value not found (binary search).\n");
    }

    free(arr);
    free(value);
    return 0;
}
