#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>
#include <unistd.h>

int main() {
    struct passwd *pw;
    uid_t uid_threshold = 1000;
    uid_t current_uid = getuid();
    int found = 0;

    setpwent();
    while ((pw = getpwent()) != NULL) {
        if (pw->pw_uid >= uid_threshold && pw->pw_uid != current_uid) {
            printf("Found an user: %s (UID: %d)\n", pw->pw_name, pw->pw_uid);
            found = 1;
        }
    }
    endpwent();

    if (!found) {
        printf("No other users found.\n");
    }
    return 0;
}
