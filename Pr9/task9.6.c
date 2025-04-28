#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pwd.h>

void check_access(const char *filepath) {
    printf("Checking access for file: %s\n", filepath);

    if (access(filepath, R_OK) == 0)
        printf("  - Read access: YES\n");
    else
        printf("  - Read access: NO\n");

    if (access(filepath, W_OK) == 0)
        printf("  - Write access: YES\n");
    else
        printf("  - Write access: NO\n");

    if (access(filepath, X_OK) == 0)
        printf("  - Execute access: YES\n");
    else
        printf("  - Execute access: NO\n");
    printf("\n");
}

int main() {
    const char *home_dir = getenv("HOME");
    if (!home_dir) {
        struct passwd *pw = getpwuid(getuid());
        if (pw) home_dir = pw->pw_dir;
        else {
            fprintf(stderr, "Cannot get home directory\n");
            return 1;
        }
    }

    printf("Listing files in your home directory (%s):\n", home_dir);
    char cmd[512];

    snprintf(cmd, sizeof(cmd), "ls -l %s", home_dir);
    system(cmd);
    printf("\n");

    printf("Listing files in /usr/bin:\n");
    system("ls -l /usr/bin");
    printf("\n");

    printf("Listing files in /etc:\n");
    system("ls -l /etc");
    printf("\n");
    printf("Demonstrating access checks:\n");

    const char *files_to_check[] = {
        "/usr/bin/ls",        // Виконуваний файл
        "/etc/passwd",        // Файл з правами на читання
        "/etc/shadow",        // Доступний тільки для root
        "/etc/hosts",         // Конфігураційний файл
        NULL
    };

    for (int i = 0; files_to_check[i] != NULL; i++) {
        check_access(files_to_check[i]);
    }

    return 0;
}
