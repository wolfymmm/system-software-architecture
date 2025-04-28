#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *fp;
    char line[256];
    fp = popen("sudo cat /etc/shadow", "r");
    if (fp == NULL) {
        perror("Failed to run command");
        return 1;
    }
    while (fgets(line, sizeof(line), fp) != NULL) {
        printf("%s", line);
    }
    pclose(fp);
    return 0;
}
