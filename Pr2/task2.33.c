#include <stdio.h>
#include <stdlib.h>

int global_var = 42;       // Data segment
int uninitialized_var;     // BSS segment
static int static_var = 99; // Static variable (Data segment)

void expand_stack() {
    int local_array[10000];
    printf("After expanding stack, top is near %p\n", (void*)&local_array);
}

int main() {
    int local_var;
    int *heap_var;

    // Allocating memory on the heap
    heap_var = (int *)malloc(sizeof(int) * 1000);
    if (!heap_var) {
        perror("Memory allocation failed");
        return 1;
    }
    printf("Stack top is near: %p\n", (void*)&local_var);
    printf("Heap starts from: %p\n", (void*)heap_var);
    printf("Data segment (initialized global_var): %p\n", (void*)&global_var);
    printf("BSS segment (uninitialized_var): %p\n", (void*)&uninitialized_var);
    printf("Data segment (static_var): %p\n", (void*)&static_var);
    printf("Code segment (main function): %p\n", (void*)&main);

    expand_stack();
    free(heap_var);
    return 0;
}
