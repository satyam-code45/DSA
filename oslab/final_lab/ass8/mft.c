//Q1: C Program to Implement and Simulate MFT (Multiple Fixed Partitioning)
#include <stdio.h>

#define MAX 10

int main() {
    int partitionSize[10], memorySize, blockCount, processCount;
    int processSize[10], allocation[10];
    
    printf("Enter the total memory size: ");
    scanf("%d", &memorySize);

    printf("Enter the number of partitions: ");
    scanf("%d", &blockCount);

    int blockSize = memorySize / blockCount;

    for (int i = 0; i < blockCount; i++) {
        partitionSize[i] = blockSize;
    }

    printf("Fixed Partition Size = %d\n", blockSize);

    printf("Enter number of processes: ");
    scanf("%d", &processCount);

    printf("Enter size of each process:\n");
    for (int i = 0; i < processCount; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d", &processSize[i]);
        allocation[i] = -1;
    }

    // Allocation
    for (int i = 0; i < processCount; i++) {
        for (int j = 0; j < blockCount; j++) {
            if (partitionSize[j] >= processSize[i]) {
                allocation[i] = j;
                partitionSize[j] = -1; // Mark partition as used
                break;
            }
        }
    }

    // Output
    printf("\nProcess No\tProcess Size\tPartition Allocated\n");
    for (int i = 0; i < processCount; i++) {
        printf("%d\t\t%d\t\t", i + 1, processSize[i]);
        if (allocation[i] != -1)
            printf("%d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }

    return 0;
}
