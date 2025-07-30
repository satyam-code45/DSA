#include <stdio.h>

struct Process {
    int pid;
    int burst_time;
    int arrival_time;
    int waiting_time;
    int turnaround_time;
    int completed;
    int start_time;
};

void sort_by_arrival_time(struct Process p[], int n) {
    struct Process temp;
    for(int i=0; i<n-1; i++) {
        for(int j=0; j<n-i-1; j++) {
            if(p[j].arrival_time > p[j+1].arrival_time) {
                temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }
}

int main() {
    int n = 4;
    struct Process p[20];

    printf("Enter burst time and arrival time for %d processes:\n", n);
    for(int i=0; i<n; i++) {
        p[i].pid = i+1;
        printf("Process %d - Burst Time: ", i+1);
        scanf("%d", &p[i].burst_time);
        printf("Process %d - Arrival Time: ", i+1);
        scanf("%d", &p[i].arrival_time);
        p[i].completed = 0;
    }

    sort_by_arrival_time(p, n);

    int current_time = 0, completed = 0;
    float total_waiting_time = 0, total_turnaround_time = 0;

    printf("\nGantt Chart:\n");
    printf("--------------------------------------------------\n");

    while(completed < n) {
        int idx = -1;
        int min_bt = 1e9;

        for(int i=0; i<n; i++) {
            if(p[i].arrival_time <= current_time && p[i].completed == 0) {
                if(p[i].burst_time < min_bt) {
                    min_bt = p[i].burst_time;
                    idx = i;
                }
            }
        }

        if(idx != -1) {
            p[idx].start_time = current_time;
            p[idx].waiting_time = current_time - p[idx].arrival_time;
            p[idx].turnaround_time = p[idx].waiting_time + p[idx].burst_time;

            printf("| P%d (%d-%d) ", p[idx].pid, current_time, current_time + p[idx].burst_time);

            current_time += p[idx].burst_time;
            p[idx].completed = 1;
            completed++;

            total_waiting_time += p[idx].waiting_time;
            total_turnaround_time += p[idx].turnaround_time;
        } else {
            current_time++; // CPU idle
        }
    }

    printf("|\n--------------------------------------------------\n");

    printf("\nPID\tAT\tBT\tWT\tTAT\n");
    for(int i=0; i<n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].arrival_time, p[i].burst_time, p[i].waiting_time, p[i].turnaround_time);
    }

    printf("\nAverage Waiting Time: %.2f", total_waiting_time/n);
    printf("\nAverage Turnaround Time: %.2f\n", total_turnaround_time/n);

    return 0;
}
