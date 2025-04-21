#include <stdio.h>

void recurse() {
    int array[1000];
    printf("Recurse is working...: %p\n", (void*)array);
    recurse();
}

int main() {
    printf("Starting...\n");
    recurse();
    return 0;
}
