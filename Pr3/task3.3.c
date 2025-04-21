#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_FILE_SIZE 1024

int main() {
    FILE *file;
    int roll;
    long file_size;
    file = fopen("dice_rolls.txt", "a");
    if (file == NULL) {
        perror("Failed to open the file");
        return 1;
    }
    srand(time(NULL));

    for (int i = 0; i < 100; i++) {
        roll = rand() % 6 + 1;

        fseek(file, 0, SEEK_END);
        file_size = ftell(file);

        if (file_size >= MAX_FILE_SIZE) {
            printf("The file has reached the maximum size (%d bytes)\n", MAX_FILE_SIZE);
            break;
        }
        fprintf(file, "Roll %d: %d\n", i + 1, roll);
    }
    fclose(file);
    printf("Dice rolls completed.\n");
    return 0;
}
