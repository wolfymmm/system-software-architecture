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

    // Перевірка, що програма запущена від root
    if (getuid() != 0) {
        printf("Please run as root.\n");
        return 1;
    }

    // Отримуємо ім'я звичайного користувача з sudo
    const char *normal_user = getenv("SUDO_USER");
    if (!normal_user) {
        printf("SUDO_USER not set. Run with sudo.\n");
        return 1;
    }

    // Отримуємо інформацію про звичайного користувача
    struct passwd *pwd = getpwnam(normal_user);
    if (!pwd) {
        printf("User %s not found.\n", normal_user);
        return 1;
    }

    // Створюємо файл у /tmp
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

    // Копіюємо файл у домашній каталог користувача
    char dst_path[PATH_MAX];
    snprintf(dst_path, sizeof(dst_path), "%s/%s", pwd->pw_dir, filename);

    // Копіювання файлу
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

    struct stat stat_buf;
    fstat(src_fd, &stat_buf);
    sendfile(dst_fd, src_fd, NULL, stat_buf.st_size);

    close(src_fd);
    close(dst_fd);
    printf("Copied file to: %s\n", dst_path);

    // Змінюємо власника файлу на звичайного користувача
    if (chown(dst_path, pwd->pw_uid, pwd->pw_gid) != 0) {
        perror("chown");
        return 1;
    }
    printf("Changed owner to %s\n", normal_user);

    printf("\nNow switch to user '%s' and try to:\n", normal_user);
    printf("1. Edit the file: %s\n", dst_path);
    printf("2. Save changes\n");
    printf("3. Delete the file: rm %s\n", dst_path);
    printf("\nWhat will happen?\n");

    return 0;
}