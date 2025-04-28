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
        printf("Please run as root.\n");
        return 1;
    }

    const char *normal_user = getenv("SUDO_USER");
    if (!normal_user) {
        printf("SUDO_USER not set. Run with sudo.\n");
        return 1;
    }

    struct passwd *pwd = getpwnam(normal_user);
    if (!pwd) {
        printf("User %s not found.\n", normal_user);
        return 1;
    }

    char src_path[PATH_MAX];
    snprintf(src_path, sizeof(src_path), "/tmp/%s", filename);

    FILE *f = fopen(src_path, "w");
    if (!f) {
        perror("fopen");
        return 1;
    }
    fprintf(f, "%s", content);
    fclose(f);
    printf("Created file: %s\n", src_path);

    char dst_path[PATH_MAX];
    snprintf(dst_path, sizeof(dst_path), "%s/%s", pwd->pw_dir, filename);

    int src_fd = open(src_path, O_RDONLY);
    if (src_fd < 0) {
        perror("open source");
        return 1;
    }

    int dst_fd = open(dst_path, O_WRONLY|O_CREAT|O_TRUNC, 0644);
    if (dst_fd < 0) {
        perror("open destination");
        close(src_fd);
        return 1;
    }

    char buffer[4096];
    ssize_t bytes_read;
    while ((bytes_read = read(src_fd, buffer, sizeof(buffer))) > 0) {
        write(dst_fd, buffer, bytes_read);
    }

    close(src_fd);
    close(dst_fd);
    printf("Copied file to: %s\n", dst_path);

    if (chown(dst_path, pwd->pw_uid, pwd->pw_gid) == -1) {
        perror("Failed to change owner");
        return 1;
    }
    printf("Changed owner to %s\n", normal_user);

    printf("\nNow switch to user '%s' and try to:\n", normal_user);
    printf("1. Edit the file: %s\n", dst_path);
    printf("2. Save changes\n");
    printf("3. Delete the file: rm %s\n", dst_path);
    printf("\nExpected behavior:\n");
    printf("- User CAN edit and save the file (they own it).\n");
    printf("- User CAN delete the file (they have write permission in their home dir).\n");

    return 0;
}