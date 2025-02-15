#include <iostream>
#include <algorithm>
#include <vector>
#include <climits>
using namespace std;

struct Process {
    int id, at, bt, priority, ct, tat, wt, remaining_bt, preemptions = 0;
};

// Comparator function for sorting based on arrival time
bool arrivalSort(Process a, Process b) {
    return a.at < b.at;
}

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;
    Process p[n];

    // Input process details
    for (int i = 0; i < n; i++) {
        cout << "Enter Arrival Time, Burst Time, and Priority for process " << i + 1 << ": ";
        cin >> p[i].at >> p[i].bt >> p[i].priority;
        p[i].id = i + 1;
        p[i].remaining_bt = p[i].bt; // Initialize remaining burst time
    }

    // Sorting processes by arrival time initially
    sort(p, p + n, arrivalSort);

    int currentTime = p[0].at, completedCount = 0;
    float totalTAT = 0, totalWT = 0;
    vector<pair<int, int>> ganttChart;

    // Scheduling logic (Preemptive Priority Scheduling)
    int lastExecutedProcess = -1;
    while (completedCount < n) {
        int highestPriorityIndex = -1;
        int highestPriority = INT_MAX;

        // Select process with highest priority among available ones
        for (int i = 0; i < n; i++) {
            if (p[i].remaining_bt > 0 && p[i].at <= currentTime) {
                if (p[i].priority < highestPriority) {
                    highestPriority = p[i].priority;
                    highestPriorityIndex = i;
                } else if (p[i].priority == highestPriority) {
                    if (p[i].at < p[highestPriorityIndex].at) {
                        highestPriorityIndex = i;
                    }
                }
            }
        }

        if (highestPriorityIndex == -1) {
            currentTime++; // CPU is idle
        } else {
            int i = highestPriorityIndex;

            // Log Gantt Chart execution only if process changes
            if (lastExecutedProcess != p[i].id) {
                ganttChart.push_back({currentTime, p[i].id});

                // If a process was previously executing and now it's being preempted, increment its preemption count
                if (lastExecutedProcess != -1) {
                    for (int j = 0; j < n; j++) {
                        if (p[j].id == lastExecutedProcess) {
                            p[j].preemptions++;
                            break;
                        }
                    }
                }

                lastExecutedProcess = p[i].id;
            }

            // Process executes for 1 unit of time
            p[i].remaining_bt--;
            currentTime++;

            // If process is completed
            if (p[i].remaining_bt == 0) {
                p[i].ct = currentTime;  // Completion time
                p[i].tat = p[i].ct - p[i].at;  // Turnaround time
                p[i].wt = p[i].tat - p[i].bt;  // Waiting time
                
                totalTAT += p[i].tat;
                totalWT += p[i].wt;
                
                completedCount++;
            }
        }
    }

    // Output Gantt Chart
    cout << "\nGantt Chart:\n";
    cout << "--------------------------------------------------\n";
    cout << "| Time |";
    for (auto &entry : ganttChart) {
        cout << " P" << entry.second << "\t|";
    }
    cout << "\n--------------------------------------------------\n";

    // Displaying the timeline of execution
    cout << "|\t0\t";
    for (auto &entry : ganttChart) {
        cout << entry.first << "\t";
    }
    cout << currentTime << "\n--------------------------------------------------\n";

    // Output process details (now ordered by original input order)
    cout << "\nProcess\tAT\tBT\tPriority\tCT\tTAT\tWT\tPreemptions\n";
    for (int i = 0; i < n; i++) {
        cout << p[i].id << "\t" << p[i].at << "\t" << p[i].bt << "\t"
             << p[i].priority << "\t\t" << p[i].ct << "\t" << p[i].tat << "\t"
             << p[i].wt << "\t" << p[i].preemptions << endl;
    }

    // Output average turnaround and waiting times
    cout << "\nAverage Turnaround Time: " << totalTAT / n;
    cout << "\nAverage Waiting Time: " << totalWT / n << endl;

    return 0;
}
