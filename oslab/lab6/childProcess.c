// 1. Write a program in C to demonstrate the creation and termination of the child process. Your program must include a series of system calls to create new child processes and each child process must do the same function or task. Check if the series contains "n" System calls, then your program creates how many child processes and how many times the common task will be executed.


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

// Common task for all child processes
void common_task() {
    printf("Child process (PID: %d) is executing the common task.\n", getpid());
}

int main() {
    int n; // number of fork system calls
    printf("Enter the number of fork system calls (n): ");
    scanf("%d", &n);

    int total_forks = n;
    for (int i = 0; i < total_forks; i++) {
        pid_t pid = fork();
        if (pid < 0) {
            perror("fork failed");
            exit(1);
        } else if (pid == 0) {
            // Child process
            common_task();
            exit(0); // Important to prevent child from creating more children
        }
        // Parent process waits for the child
        wait(NULL);
    }

    printf("Main process (PID: %d) completed.\n", getpid());

    return 0;
}
