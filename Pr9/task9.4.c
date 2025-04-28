#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("'whoami':\n");
    int ret = system("whoami");
    if (ret == -1) {
        perror("system(whoami)");
        return 1;
    }
    printf("\n'id':\n");
    ret = system("id");
    if (ret == -1) {
        perror("system(id)");
        return 1;
    }
    return 0;
}
