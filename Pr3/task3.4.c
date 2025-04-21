#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_CPU_TIME 5

void generate_lottery_numbers(int *lottery1, int *lottery2) {
    for (int i = 0; i < 7; i++) {
        lottery1[i] = rand() % 49 + 1;
        for (int j = 0; j < i; j++) {
            if (lottery1[i] == lottery1[j]) {
                i--;
                break;
            }
        }
    }

    for (int i = 0; i < 6; i++) {
        lottery2[i] = rand() % 36 + 1;
        for (int j = 0; j < i; j++) {
            if (lottery2[i] == lottery2[j]) {
                i--;
                break;
            }
        }
    }
}

int main() {
    int lottery1[7], lottery2[6];
    time_t start_time, current_time;
    double elapsed_time;

    srand(time(NULL));

    start_time = time(NULL);

    while (1) {
        generate_lottery_numbers(lottery1, lottery2);

        current_time = time(NULL);
        elapsed_time = difftime(current_time, start_time);

        if (elapsed_time >= MAX_CPU_TIME) {
            printf("CPU time limit reached (%d seconds).\n", MAX_CPU_TIME);
            break;
        }

        printf("Lottery numbers (1-49): ");
        for (int i = 0; i < 7; i++) {
            printf("%d ", lottery1[i]);
        }

        printf("\nLottery numbers (1-36): ");
        for (int i = 0; i < 6; i++) {
            printf("%d ", lottery2[i]);
        }
        printf("\n");

        sleep(1);
    }

    return 0;
}
