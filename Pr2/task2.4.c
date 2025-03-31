#include <stdio.h>

void func() {
    int local_arr1[1000];
    static int local_arr2[1000] = {1};
}

int main() {
    printf("Hello, World!\n");
    func();
    return 0;
}