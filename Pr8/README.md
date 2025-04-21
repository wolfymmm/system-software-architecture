# Практична робота №8:  Системні виклики в UNIX/POSIX (файлові операції, fork(), qsort(), write(), read(), lseek() тощо

## Зміст
1. [Умова завдання](#умова-завдання)
2. [Код програми](#код-програми)
3. [Опис](#опис)
4. [Результат](#результат)

---
## Умова завдання
Напишіть програму, яка симулює часткове зчитування з файлу з паралельним записом з іншого процесу.
## Код програми:

```
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

#define FILENAME "test_file.txt"
#define BUFFER_SIZE 100
#define WRITE_DATA "This is data written by the writer process.\n"

void reader_process() {
    char buffer[BUFFER_SIZE];
    int fd = open(FILENAME, O_RDONLY);
    if (fd == -1) {
        perror("Failed to open file for reading");
        exit(1);
    }

    printf("Reader process: Reading the file...\n");

    ssize_t bytes_read;
    while ((bytes_read = read(fd, buffer, sizeof(buffer) - 1)) > 0) {
        buffer[bytes_read] = '\0';  // Додаємо нульовий символ для коректного виведення
        printf("Reader process read: %s", buffer);
        sleep(1);  // Затримка для симуляції повільного зчитування
    }

    if (bytes_read == -1) {
        perror("Failed to read the file");
        close(fd);
        exit(1);
    }

    close(fd);
}

void writer_process() {
    int fd = open(FILENAME, O_WRONLY | O_APPEND | O_CREAT, 0644);
    if (fd == -1) {
        perror("Failed to open file for writing");
        exit(1);
    }

    printf("Writer process: Writing to the file...\n");

    ssize_t bytes_written = write(fd, WRITE_DATA, strlen(WRITE_DATA));
    if (bytes_written == -1) {
        perror("Failed to write to the file");
        close(fd);
        exit(1);
    }

    close(fd);
}

int main() {
    // Створення файлу для тесту
    int fd = open(FILENAME, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("Failed to create the test file");
        exit(1);
    }
    close(fd);

    pid_t reader_pid = fork();
    if (reader_pid == -1) {
        perror("Failed to fork reader process");
        exit(1);
    }

    if (reader_pid == 0) {
        reader_process();
        exit(0);
    }
    sleep(1);

    pid_t writer_pid = fork();
    if (writer_pid == -1) {
        perror("Failed to fork writer process");
        exit(1);
    }

    if (writer_pid == 0) {
        writer_process();
        exit(0);
    }
    wait(NULL);
    wait(NULL);
    printf("Main process: Both reader and writer have finished.\n");

    return 0;
}
```

## Опис
Програма моделює ситуацію, коли один процес частково зчитує вміст файлу, а інший — паралельно записує в нього нові дані. 

На початку головна функція створює файл `test_file.txt`, очищаючи його. 

Потім за допомогою `fork()` створюється перший дочірній процес — читач, який відкриває файл для читання і повільно, з затримкою, зчитує вміст блоками. 

Через секунду після старту читача створюється другий процес — записувач, який відкриває той самий файл у режимі дописування і записує рядок тексту. Завдяки затримці читача, запис відбувається "на ходу", і частина вмісту може бути зчитана ще до дописування, що дозволяє спостерігати реальний приклад паралельного доступу до файлу. 

## Результат:
![task 12](task12.png)

