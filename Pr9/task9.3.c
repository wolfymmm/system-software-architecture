#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pwd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <limits.h>

int main() {
    const char *filename = "testfile.txt";
    const char *content = "This file was created by root.\n";

    if (getuid() != 0) {
        fprintf(stderr, "Error: Please run this program as root using sudo.\n");
        return 1;
    }

    const char *normal_user = getenv("SUDO_USER");
    if (!normal_user) {
        fprintf(stderr, "Error: SUDO_USER not set. Please run with: sudo ./program\n");
        return 1;
    }

    struct passwd *pwd = getpwnam(normal_user);
    if (!pwd) {
        fprintf(stderr, "Error: User '%s' not found.\n", normal_user);
        return 1;
    }

    char src_path[PATH_MAX];
    char dst_path[PATH_MAX];
    snprintf(src_path, sizeof(src_path), "/tmp/%s", filename);
    snprintf(dst_path, sizeof(dst_path), "%s/%s", pwd->pw_dir, filename);

    FILE *f = fopen(src_path, "w");
    if (!f) {
        perror("Error creating source file");
        return 1;
    }
    fprintf(f, "%s", content);
    fclose(f);
    printf("Created file: %s\n", src_path);

    int src_fd = open(src_path, O_RDONLY);
    if (src_fd < 0) {
        perror("Error opening source file");
        return 1;
    }

    int dst_fd = open(dst_path, O_WRONLY | O_CREAT | O_TRUNC, 0644); // rw-r--r--
    if (dst_fd < 0) {
        perror("Error creating destination file");
        close(src_fd);
        return 1;
    }

    char buffer[4096];
    ssize_t bytes;
    while ((bytes = read(src_fd, buffer, sizeof(buffer))) > 0) {
        if (write(dst_fd, buffer, bytes) != bytes) {
            perror("Error writing to destination file");
            close(src_fd);
            close(dst_fd);
            return 1;
        }
    }

    close(src_fd);
    close(dst_fd);
    printf("File copied to: %s\n", dst_path);

    if (chown(dst_path, pwd->pw_uid, pwd->pw_gid) != 0) {
        perror("Error changing file ownership");
        return 1;
    }
    printf("File ownership changed to: %s\n", normal_user);

    struct stat st;
    if (stat(dst_path, &st) == 0) {
        printf("File permissions: %o\n", st.st_mode & 0777);
    } else {
        perror("Error checking file permissions");
    }

    printf("\nInstructions:\n");
    printf("1. Switch to user '%s':\n", normal_user);
    printf("   su - %s\n", normal_user);
    printf("2. Edit the file:\n");
    printf("   nano %s\n", dst_path);
    printf("3. Delete the file (if needed):\n");
    printf("   rm %s\n", dst_path);
    return 0;
}