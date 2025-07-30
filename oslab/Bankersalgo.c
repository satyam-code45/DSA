#include <stdio.h>
#define R 3 // Total number of resource types

struct Bankersalgo
{
    int pid;
    int allocation[R];
    int maxNeed[R];
    int Remaning[R]
};

int main()
{
    int available[R] = {10, 5, 7};
    int np;
    printf("Enter no of Processes: ");
    scanf("%d", &np);
    struct Bankersalgo Process[np];
    //MaxNeed
    for (int i = 0; i < np; i++)
    {
        for (int j = 0; j < R; j++)
        {
            printf("Enter MaxNeed for Process %d for resouce %d: ", i + 1, j+1);
            scanf("%d", Process[i].maxNeed[j]);
        }
    }
    //Allocated & remaning
    for (int i = 0; i < np; i++)
    {
        for (int j = 0; j < R; j++)
        {
            printf("Enter Allocation for Process %d for resouce %d: ", i + 1, j+1);
            scanf("%d", Process[i].allocation[j]);
            Process[i].Remaning[j] = Process[i].maxNeed[j] - Process[i].allocation[j];
        }
    }

    int work[R];
    bool finish[np] = {false};
    for (int i = 0; i < R; i++) {
        work[i] = available[i];
    }

    

    int pdone = np;

    while (pdone)
    {
        
    }
    
}