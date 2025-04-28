#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pwd.h>
#include <sys/types.h>

int main() {
    const char *filename = "testfile.txt";

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

    char src_path[256];
    char dst_path[256];

    snprintf(src_path, sizeof(src_path), "/tmp/%s", filename);
    snprintf(dst_path, sizeof(dst_path), "%s/%s", pwd->pw_dir, filename);

    FILE *f = fopen(src_path, "w");
    if (!f) {
        perror("fopen");
        return 1;
    }
    fprintf(f, "This file was created by root.\n");
    fclose(f);
    printf("Created file: %s\n", src_path);

    char cmd[512];
    snprintf(cmd, sizeof(cmd), "cp %s %s", src_path, dst_path);
    system(cmd);
    printf("Copied file to: %s\n", dst_path);

    // Змінюємо власника файлу на звичайного користувача
    if (chown(dst_path, pwd->pw_uid, pwd->pw_gid) != 0) {
        perror("chown");
        return 1;
    }
    printf("Changed owner to %s\n", normal_user);
    printf("Now, as user '%s', you can try to edit and delete the file: %s\n", normal_user, dst_path);

    return 0;
}
