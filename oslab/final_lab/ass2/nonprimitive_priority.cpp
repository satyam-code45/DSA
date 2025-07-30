#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Process {
    int pid;
    int arrival_time;
    int burst_time;
    int priority;
    int waiting_time;
    int turnaround_time;
    int start_time;
    bool completed = false;
};

int main() {
    int n = 5;
    vector<Process> processes(n);

    cout << "Enter Arrival Time, Burst Time and Priority (Lower number = Higher priority):\n";
    for(int i = 0; i < n; ++i) {
        processes[i].pid = i + 1;
        cout << "Process " << i+1 << ":\n";
        cout << "Arrival Time: ";
        cin >> processes[i].arrival_time;
        cout << "Burst Time: ";
        cin >> processes[i].burst_time;
        cout << "Priority: ";
        cin >> processes[i].priority;
    }

    int current_time = 0, completed = 0;
    float total_wt = 0, total_tat = 0;

    cout << "\nGantt Chart:\n";
    cout << "--------------------------------------------------\n";

    while(completed < n) {
        int idx = -1;
        int highest_priority = 1e9;

        for(int i = 0; i < n; ++i) {
            if(processes[i].arrival_time <= current_time && !processes[i].completed) {
                if(processes[i].priority < highest_priority) {
                    highest_priority = processes[i].priority;
                    idx = i;
                }
            }
        }

        if(idx != -1) {
            Process &p = processes[idx];
            p.start_time = current_time;
            p.waiting_time = current_time - p.arrival_time;
            p.turnaround_time = p.waiting_time + p.burst_time;
            current_time += p.burst_time;
            p.completed = true;
            completed++;

            total_wt += p.waiting_time;
            total_tat += p.turnaround_time;

            cout << "| P" << p.pid << " (" << p.start_time << "-" << current_time << ") ";
        } else {
            current_time++; // CPU Idle
        }
    }

    cout << "|\n--------------------------------------------------\n";
    cout << "\nPID\tAT\tBT\tPri\tWT\tTAT\n";
    for(auto &p : processes) {
        cout << p.pid << "\t" << p.arrival_time << "\t" << p.burst_time << "\t"
             << p.priority << "\t" << p.waiting_time << "\t" << p.turnaround_time << "\n";
    }

    cout << "\nAverage Waiting Time: " << total_wt / n;
    cout << "\nAverage Turnaround Time: " << total_tat / n << "\n";

    return 0;
}
