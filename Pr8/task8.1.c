#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int main() {
    const char *archivo = "output.txt";
    const char *cancion = "This is a test string that is longer than usual buffer sizes!"; // буфер
    ssize_t tamano = strlen(cancion);

    int tralalero = open(archivo, O_WRONLY | O_CREAT | O_NONBLOCK, 0644);
    if (tralalero == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    ssize_t burrito = write(tralalero, cancion, tamano);
    if (burrito == -1) {
        perror("write");
        close(tralalero);
        exit(EXIT_FAILURE);
    }

    printf("Requested to write %zd bytes, actually wrote %zd bytes.\n", tamano, burrito);

    if (burrito < tamano) {
        printf("Warning: Partial write detected!\n");
    } else {
        printf("All bytes written successfully.\n");
    }

    close(tralalero);
    return 0;
}

