#include <iostream>
#include <vector>
using namespace std;

struct Process {
    int pid;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int completion_time;
    int waiting_time;
    int turnaround_time;
};

int main() {
    int n = 3;
    vector<Process> processes(n);

    cout << "Enter Arrival Time and Burst Time:\n";
    for(int i = 0; i < n; ++i) {
        processes[i].pid = i+1;
        cout << "Process " << i+1 << ":\n";
        cout << "Arrival Time: ";
        cin >> processes[i].arrival_time;
        cout << "Burst Time: ";
        cin >> processes[i].burst_time;
        processes[i].remaining_time = processes[i].burst_time;
    }

    int completed = 0, current_time = 0;
    float total_wt = 0, total_tat = 0;

    cout << "\nGantt Chart:\n";
    cout << "--------------------------------------------------\n";

    while(completed < n) {
        int idx = -1, min_rt = 1e9;
        for(int i = 0; i < n; ++i) {
            if(processes[i].arrival_time <= current_time && processes[i].remaining_time > 0) {
                if(processes[i].remaining_time < min_rt) {
                    min_rt = processes[i].remaining_time;
                    idx = i;
                }
            }
        }

        if(idx != -1) {
            processes[idx].remaining_time--;
            cout << "|P" << processes[idx].pid << "(" << current_time << "-" << current_time+1 << ")";

            if(processes[idx].remaining_time == 0) {
                completed++;
                processes[idx].completion_time = current_time + 1;
                processes[idx].turnaround_time = processes[idx].completion_time - processes[idx].arrival_time;
                processes[idx].waiting_time = processes[idx].turnaround_time - processes[idx].burst_time;

                total_wt += processes[idx].waiting_time;
                total_tat += processes[idx].turnaround_time;
            }
        } else {
            cout << "|Idle(" << current_time << "-" << current_time+1 << ")";
        }

        current_time++;
    }

    cout << "|\n--------------------------------------------------\n";

    cout << "\nPID\tAT\tBT\tCT\tWT\tTAT\n";
    for(auto &p : processes) {
        cout << p.pid << "\t" << p.arrival_time << "\t" << p.burst_time << "\t"
             << p.completion_time << "\t" << p.waiting_time << "\t" << p.turnaround_time << "\n";
    }

    cout << "\nAverage Waiting Time: " << total_wt / n;
    cout << "\nAverage Turnaround Time: " << total_tat / n << "\n";

    return 0;
}
