// 2. Write a program in C to demonstrate how two child processes of a program execute for different tasks, like one finding factorization of an integer and another finding the greatest common divisors between two numbers. Give your comment regarding execution of child processes. 

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

// Function to factorize an integer
void factorize(int num) {
    printf("Factorization of %d: ", num);
    for (int i = 1; i <= num; i++) {
        if (num % i == 0) {
            printf("%d ", i);
        }
    }
    printf("\n");
}

// Function to calculate GCD of two integers
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int main() {
    pid_t pid1, pid2;

    pid1 = fork();
    if (pid1 < 0) {
        perror("fork failed");
        exit(1);
    } else if (pid1 == 0) {
        // First child process: factorization
        printf("Child 1 (PID: %d): ", getpid());
        factorize(28);
        exit(0);
    } else {
        pid2 = fork();
        if (pid2 < 0) {
            perror("fork failed");
            exit(1);
        } else if (pid2 == 0) {
            // Second child process: GCD
            int a = 60, b = 48;
            printf("Child 2 (PID: %d): GCD of %d and %d is %d\n", getpid(), a, b, gcd(a, b));
            exit(0);
        } else {
            // Parent process waits for both children
            wait(NULL);
            wait(NULL);
            printf("Parent (PID: %d): Both child processes completed.\n", getpid());
        }
    }

    return 0;
}
