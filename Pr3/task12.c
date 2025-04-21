#include <stdio.h>
#include <stdlib.h>

#define NUM_FILES 1000
#define FILENAME "testfile.txt"

void create_test_files() {
    FILE *file;
    for (int i = 0; i < NUM_FILES; i++) {
        char filename[50];
        snprintf(filename, sizeof(filename), "file_%d.txt", i);

        file = fopen(filename, "w");
        if (file == NULL) {
            perror("Failed to create file");
            exit(1);
        }

        fprintf(file, "This is test file number %d.\n", i);
        fclose(file);
    }
}

int main() {
    FILE *files[NUM_FILES];
    char buffer[100];
    int i;

    create_test_files();

    for (i = 0; i < NUM_FILES; i++) {
        char filename[50];
        snprintf(filename, sizeof(filename), "file_%d.txt", i);

        files[i] = fopen(filename, "r");
        if (files[i] == NULL) {
            perror("Failed to open file");
            break;
        }
    }
    for (int j = 0; j < i; j++) {
        if (files[j] != NULL) {
            fgets(buffer, sizeof(buffer), files[j]);
            printf("Content of file %d: %s", j, buffer);
            fclose(files[j]);
        }
    }

    return 0;
}
