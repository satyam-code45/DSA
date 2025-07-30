#include <stdio.h>
#include <stdbool.h>

#define P 5 // Total number of processes
#define R 3 // Total number of resource types

int main()
{
    int i, j, k;
    int safeSequence[P];      // To store safe sequence
    bool finish[P] = {false}; // To mark finished processes
    int count = 0;            // Count of processes that have finished

    // Example Available vector: number of available resources for each type.
    int available[R] = {10, 5, 7};

    // Example Max matrix: Maximum demand of each process.
    int max[P][R] = {
        {7, 5, 3},
        {3, 2, 2},
        {9, 0, 2},
        {4, 2, 2},
        {5, 3, 3}};

    // Example Allocation matrix: Resources currently allocated to each process.
    int allocation[P][R] = {
        {0, 1, 0},
        {2, 0, 0},
        {3, 0, 2},
        {2, 1, 1},
        {0, 0, 2}};

    int need[P][R]; // Need matrix: to be computed as max - allocation.

    // Calculate Need matrix for each process.
    printf("Remaning Need \n");
    for (i = 0; i < P; i++)
    {
        for (j = 0; j < R; j++)
        {
            need[i][j] = max[i][j] - allocation[i][j];
            printf("%d  ", need[i][j]);
        }
        printf("\n");
    }

    // Safety Algorithm:
    // Create a work vector and initialize it as available.
    int work[R];
    for (i = 0; i < R; i++)
    {
        work[i] = available[i];
    }

    // Find a safe sequence.
    while (count < P)
    {
        bool found = false;
        for (i = 0; i < P; i++)
        {
            if (!finish[i])
            {
                bool possible = true;
                // Check if process i can be satisfied with current work vector.
                for (j = 0; j < R; j++)
                {
                    if (need[i][j] > work[j])
                    {
                        possible = false;
                        break;
                    }
                }
                // If process i can finish, update the work vector.
                if (possible)
                {
                    for (j = 0; j < R; j++)
                    {
                        work[j] += allocation[i][j];
                    }
                    safeSequence[count] = i;
                    count++;
                    finish[i] = true;
                    found = true;
                }
            }
        }
        // If no process could be found in this iteration, system is not safe.
        if (!found)
        {
            break;
        }
    }

    // Check if all processes could finish.
    if (count == P)
    {
        printf("System is in a safe state.\nSafe sequence is: ");
        for (i = 0; i < P; i++)
        {
            printf("P%d ", safeSequence[i]);
        }
        printf("\n");
    }
    else
    {
        printf("System is not in a safe state.\n");
    }

    return 0;
}