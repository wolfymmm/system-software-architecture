#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *fp;
    char line[256];
    // Виконуємо команду через sudo
    fp = popen("sudo cat /etc/shadow", "r");
    if (fp == NULL) {
        perror("Failed to run command");
        return 1;
    }
    // /etc/shadow
    while (fgets(line, sizeof(line), fp) != NULL) {
        printf("%s", line);
    }
    pclose(fp);
    return 0;
}
