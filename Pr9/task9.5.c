#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <pwd.h>
#include <errno.h>

int main() {
    char filename[] = "/tmp/catfish";

    int fd = mkstemp(filename);
    if (fd < 0) {
        perror("mkstemp");
        return 1;
    }
    printf("File created: %s\n", filename);
    close(fd);

    uid_t uid = getuid();
    gid_t gid = getgid();

    printf("Running as UID=%d GID=%d\n", uid, gid);

    // Якщо ми root, змінюємо власника і права доступу
    if (uid == 0) {
        const char *normal_user = getenv("SUDO_USER");
        if (!normal_user) {
            fprintf(stderr, "SUDO_USER env not set. Run with sudo.\n");
            unlink(filename);
            return 1;
        }

        struct passwd *pwd = getpwnam(normal_user);
        if (!pwd) {
            fprintf(stderr, "User %s not found\n", normal_user);
            unlink(filename);
            return 1;
        }

        // Змінюємо власника на звичайного користувача
        if (chown(filename, pwd->pw_uid, pwd->pw_gid) != 0) {
            perror("chown");
            unlink(filename);
            return 1;
        }

        if (chmod(filename, S_IRUSR | S_IWUSR | S_IRGRP) != 0) {
            perror("chmod");
            unlink(filename);
            return 1;
        }

        printf("Changed owner to %s and permissions to \n", normal_user);
    }

    // Перевіряємо права доступу до файлу
    printf("Check access for %s:\n", filename);

    if (access(filename, R_OK) == 0)
        printf("- Can read the file\n");
    else
        printf("- Cannot read the file\n");

    if (access(filename, W_OK) == 0)
        printf("- Can write to the file\n");
    else
        printf("- Cannot write to the file\n");
    unlink(filename);
    return 0;
}
