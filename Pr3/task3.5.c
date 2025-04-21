#include <stdio.h>
#include <stdlib.h>

#define MAX_FILE_SIZE 1048576

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Program need two arguments\n");
        return 1;
    }

    FILE *source_file, *dest_file;
    char buffer[1024];
    size_t bytes_read, bytes_written;
    long file_size = 0;

    source_file = fopen(argv[1], "rb");
    if (source_file == NULL) {
        printf("Cannot open file %s for reading\n", argv[1]);
        return 1;
    }

    dest_file = fopen(argv[2], "wb");
    if (dest_file == NULL) {
        printf("Cannot open file %s for writing\n", argv[2]);
        fclose(source_file);
        return 1;
    }

    while ((bytes_read = fread(buffer, 1, sizeof(buffer), source_file)) > 0) {
        file_size += bytes_read;
        if (file_size > MAX_FILE_SIZE) {
            printf("File size limit exceeded\n");
            fclose(source_file);
            fclose(dest_file);
            return 1;
        }

        bytes_written = fwrite(buffer, 1, bytes_read, dest_file);
        if (bytes_written != bytes_read) {
            printf("Error writing to file %s\n", argv[2]);
            fclose(source_file);
            fclose(dest_file);
            return 1;
        }
    }

    fclose(source_file);
    fclose(dest_file);
    printf("File copied successfully\n");

    return 0;
}

