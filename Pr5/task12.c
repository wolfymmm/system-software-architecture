#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <setjmp.h>

jmp_buf jumpyJumpyBuffer;

void whoopsSignalHandler(int sig) {
    printf("Got signal: %d\n", sig);
    longjmp(jumpyJumpyBuffer, 1);
}

void memoryAllocatorMagic() {
    int *memoryPointer = (int *)malloc(100 * sizeof(int));
    if (memoryPointer == NULL) {
        perror("Memory allocation failed... Oops");
        exit(1);
    }

    // Імітуємо ситуацію, коли пам'ять буде втрачена через виключення або сигнал
    printf("Memory allocated!\n");
    if (setjmp(jumpyJumpyBuffer) == 0) {
        raise(SIGINT);
    } else {
        // Тут ми повертаємось після отримання сигналу
        free(memoryPointer);
        printf("Memory set free after the signal drama\n");
    }
}

int main() {
    signal(SIGINT, whoopsSignalHandler);
    memoryAllocatorMagic();
    return 0;
}

