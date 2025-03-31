#include <stdio.h>
#include <setjmp.h>

jmp_buf stackTop;

void lostWithoutIP() {
    printf("Oh no! Where am I? I don't know where to return...\n");
    longjmp(stackTop, 1);
}

int main() {
    if (setjmp(stackTop) == 0) {
        printf("Sending a function call...\n");
        lostWithoutIP();
    } else {
        printf("Oops! We returned to the wrong place!\n");
    }
    printf("Program exited safely! (But that was weird)\n");
    return 0;
}
