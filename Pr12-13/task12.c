#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

#define SUBSCRIBER_COUNT 3

pid_t subscribers[SUBSCRIBER_COUNT];

void subscriber_handler(int signo, siginfo_t *info, void *context) {
    printf("Subscriber (PID: %d) received signal %d from publisher (PID: %d)\n",
           getpid(), signo, info->si_pid);
}

void create_subscriber(int index, int signal_number) {
    pid_t pid = fork();
    if (pid == 0) {
        struct sigaction sa;
        sa.sa_flags = SA_SIGINFO;
        sa.sa_sigaction = subscriber_handler;
        sigemptyset(&sa.sa_mask);
        sigaction(signal_number, &sa, NULL);

        printf("Subscriber %d (PID: %d) waiting for signal %d\n",
               index, getpid(), signal_number);

        while (1) {
            pause();
        }
        exit(0);
    } else if (pid > 0) {
        subscribers[index] = pid;
    } else {
        perror("fork");
        exit(1);
    }
}

int main() {
    printf("Publisher PID: %d\n", getpid());

    for (int i = 0; i < SUBSCRIBER_COUNT; i++) {
        int signal_number = SIGRTMIN + i;
        create_subscriber(i, signal_number);
        sleep(1);
    }

    sleep(2);

    for (int i = 0; i < SUBSCRIBER_COUNT; i++) {
        int signal_number = SIGRTMIN + i;
        kill(subscribers[i], signal_number);
        printf("Publisher sent signal %d to subscriber %d (PID: %d)\n",
               signal_number, i, subscribers[i]);
    }
    sleep(3);
    for (int i = 0; i < SUBSCRIBER_COUNT; i++) {
        kill(subscribers[i], SIGKILL);
        waitpid(subscribers[i], NULL, 0);
    }

    return 0;
}
