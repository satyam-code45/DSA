#include <iostream>
#include <queue>
#include <vector>
#include <iomanip>
#include <algorithm>

using namespace std;

struct Process {
    int pid;            // Process ID
    int arrival_time;   // Arrival Time
    int burst_time;     // Burst Time
    int remaining_time; // Remaining Burst Time
    int completion_time;// Completion Time
    int waiting_time;   // Waiting Time
    int turnaround_time;// Turnaround Time
    int preemptions;    // Number of Preemptions
    int last_executed;  // Last time the process was executed
};

struct GanttChartEntry {
    int pid;
    int start_time;
    int end_time;
};

void roundRobinScheduling(vector<Process>& processes, int time_quantum) {
    int time = 0;
    queue<int> ready_queue;
    vector<GanttChartEntry> gantt_chart;
    int n = processes.size();
    int completed = 0;

    // Sort processes by arrival time
    sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        return a.arrival_time < b.arrival_time;
    });

    vector<bool> in_queue(n, false);
    int index = 0;

    // Add processes that have arrived at time 0
    while (index < n && processes[index].arrival_time <= time) {
        ready_queue.push(index);
        in_queue[index] = true;
        index++;
    }

    while (completed < n) {
        if (ready_queue.empty()) {
            // If no process is in the ready queue, advance time
            time++;
            while (index < n && processes[index].arrival_time <= time) {
                ready_queue.push(index);
                in_queue[index] = true;
                index++;
            }
            continue;
        }

        int current = ready_queue.front();
        ready_queue.pop();

        // Record start time for Gantt chart
        int start_time = time;
        int exec_time = min(time_quantum, processes[current].remaining_time);
        time += exec_time;
        processes[current].remaining_time -= exec_time;

        // Record end time for Gantt chart
        gantt_chart.push_back({processes[current].pid, start_time, time});

        // If process is not finished, re-add to the ready queue
        if (processes[current].remaining_time > 0) {
            // Increment preemption count
            processes[current].preemptions++;
            // Add newly arrived processes to the ready queue
            while (index < n && processes[index].arrival_time <= time) {
                ready_queue.push(index);
                in_queue[index] = true;
                index++;
            }
            ready_queue.push(current);
        } else {
            // Process has completed
            processes[current].completion_time = time;
            processes[current].turnaround_time = processes[current].completion_time - processes[current].arrival_time;
            processes[current].waiting_time = processes[current].turnaround_time - processes[current].burst_time;
            completed++;
            // Add newly arrived processes to the ready queue
            while (index < n && processes[index].arrival_time <= time) {
                ready_queue.push(index);
                in_queue[index] = true;
                index++;
            }
        }
    }

    // Display Gantt Chart
    cout << "\nGantt Chart:\n";
    for (const auto& entry : gantt_chart) {
        cout << "| P" << entry.pid << " ";
    }
    cout << "|\n";
    cout << gantt_chart.front().start_time;
    for (const auto& entry : gantt_chart) {
        cout << setw(5) << entry.end_time;
    }
    cout << "\n";

    // Display process information
    double total_tat = 0, total_wt = 0;
    cout << "\nProcess\tAT\tBT\tCT\tTAT\tWT\tPreemptions\n";
    for (const auto& p : processes) {
        cout << "P" << p.pid << "\t" << p.arrival_time << "\t" << p.burst_time << "\t"
             << p.completion_time << "\t" << p.turnaround_time << "\t"
             << p.waiting_time << "\t" << p.preemptions << "\n";
        total_tat += p.turnaround_time;
        total_wt += p.waiting_time;
    }

    cout << fixed << setprecision(2);
    cout << "\nAverage Turnaround Time: " << total_tat / n;
    cout << "\nAverage Waiting Time: " << total_wt / n << "\n";
}

int main() {
    int n, time_quantum;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> processes(n);

    for (int i = 0; i < n; ++i) {
        processes[i].pid = i + 1;
        cout << "Enter Arrival Time and Burst Time for Process P" << i + 1 << ": ";
        cin >> processes[i].arrival_time >> processes[i].burst_time;
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].preemptions = 0;
    }

    cout << "Enter Time Quantum: ";
    cin >> time_quantum;

    roundRobinScheduling(processes, time_quantum);

    return 0;
}

// Enter the number of processes: 6
// Enter Arrival Time and Burst Time for Process P1: 0 4
// Enter Arrival Time and Burst Time for Process P2: 1 5
// Enter Arrival Time and Burst Time for Process P3: 2 3
// Enter Arrival Time and Burst Time for Process P4: 3 6
// Enter Arrival Time and Burst Time for Process P5: 4 2
// Enter Arrival Time and Burst Time for Process P6: 5 1
// Enter Time Quantum: 2