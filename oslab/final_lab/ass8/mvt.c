//Q2: C Program to Implement and Simulate MVT (Multiple Variable Partitioning)

#include <stdio.h>

int main() {
    int memSize, remainingMem, processSize, processCount = 0, choice;

    printf("Enter total memory size: ");
    scanf("%d", &memSize);

    remainingMem = memSize;

    do {
        printf("\nEnter size of process %d: ", processCount + 1);
        scanf("%d", &processSize);

        if (processSize <= remainingMem) {
            printf("Process %d is allocated.\n", processCount + 1);
            remainingMem -= processSize;
            processCount++;
        } else {
            printf("Not enough memory to allocate the process!\n");
        }

        printf("Do you want to add more processes? (1: Yes / 0: No): ");
        scanf("%d", &choice);
    } while (choice == 1);

    printf("\nTotal Processes Allocated: %d\n", processCount);
    printf("Remaining Memory: %d\n", remainingMem);

    return 0;
}
