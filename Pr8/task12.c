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

    // Читаємо частину файлу
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

    // Записуємо дані у файл
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
        // Дочірній процес для читання з файлу
        reader_process();
        exit(0);
    }

    // Затримка перед записом
    sleep(1);

    pid_t writer_pid = fork();
    if (writer_pid == -1) {
        perror("Failed to fork writer process");
        exit(1);
    }

    if (writer_pid == 0) {
        // Дочірній процес для запису в файл
        writer_process();
        exit(0);
    }

    // Чекати завершення обох процесів
    wait(NULL);
    wait(NULL);

    printf("Main process: Both reader and writer have finished.\n");

    return 0;
}
