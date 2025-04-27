#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int pid;
    pid = fork();
    if (pid < 0) {
        // Помилка створення процесу
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Дочірній процес
        printf("Child process: pid = %d\n", pid);
    } else {
        // Батьківський процес
        printf("Parent process: child pid = %d\n", pid);
    }
    return 0;
}
