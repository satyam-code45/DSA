#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

struct Process {
    int id, at, bt, priority, ct, tat, wt;
};

// Comparator function for sorting based on priority (higher priority first)
bool prioritySort(Process a, Process b) {
    if (a.priority == b.priority)
        return a.at < b.at;  // If priority is same, sort by arrival time
    return a.priority < b.priority;
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
    }

    // Sorting by priority (higher first) and arrival time
    sort(p, p + n, prioritySort);

    int currentTime = 0;
    float totalTAT = 0, totalWT = 0;
    vector<pair<int, int>> ganttChart;

    // Scheduling logic
    for (int i = 0; i < n; i++) {
        if (currentTime < p[i].at)
            currentTime = p[i].at;  // CPU idle, move to next arrival time

        p[i].ct = currentTime + p[i].bt;  // Completion time
        p[i].tat = p[i].ct - p[i].at;  // Turnaround time
        p[i].wt = p[i].tat - p[i].bt;  // Waiting time

        totalTAT += p[i].tat;
        totalWT += p[i].wt;

        ganttChart.push_back({currentTime, p[i].id});  // Store the start time and process id
        currentTime = p[i].ct;  // Update current time
    }

    // Output Gantt Chart: Timeline and process execution
    cout << "\nGantt Chart:\n";
    cout << "--------------------------------------------------\n";
    cout << "| Time |";
    for (auto &entry : ganttChart) {
        cout << " P" << entry.second << "\t|";
    }
    cout << "\n--------------------------------------------------\n";

    int lastTime = 0;
    // Displaying the time line of execution for each process
    cout << "|\t0\t";
    for (int i = 0; i < n; i++) {
        cout << p[i].ct << "\t";
    }
    cout << "\n--------------------------------------------------\n";

    // Output process details
    cout << "\nProcess\tAT\tBT\tPriority\tCT\tTAT\tWT\n";
    for (int i = 0; i < n; i++) {
        cout << p[i].id << "\t" << p[i].at << "\t" << p[i].bt << "\t"
             << p[i].priority << "\t\t" << p[i].ct << "\t" << p[i].tat << "\t"
             << p[i].wt << endl;
    }

    // Output average turnaround and waiting times
    cout << "\nAverage Turnaround Time: " << totalTAT / n;
    cout << "\nAverage Waiting Time: " << totalWT / n << endl;

    return 0;
}
