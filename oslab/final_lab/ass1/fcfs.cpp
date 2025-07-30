#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>

using namespace std;

struct Process {
    int pid;
    int arrivalTime;
    int burstTime;
    int startTime;
    int completionTime;
    int turnaroundTime;
    int waitingTime;
};

bool compareByArrival(Process a, Process b) {
    return a.arrivalTime < b.arrivalTime;
}

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> p(n);

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        cout << "Enter arrival time and burst time for Process " << p[i].pid << ": ";
        cin >> p[i].arrivalTime >> p[i].burstTime;
    }

    // Sort by arrival time
    sort(p.begin(), p.end(), compareByArrival);

    int currentTime = 0;
    float totalWaitingTime = 0, totalTurnaroundTime = 0;
    vector<string> ganttLabels;
    vector<int> ganttTimes;

    for (int i = 0; i < n; i++) {
        if (currentTime < p[i].arrivalTime) {
            ganttLabels.push_back("IDLE");
            ganttTimes.push_back(p[i].arrivalTime);
            currentTime = p[i].arrivalTime;
        }

        p[i].startTime = currentTime;
        p[i].completionTime = currentTime + p[i].burstTime;
        p[i].turnaroundTime = p[i].completionTime - p[i].arrivalTime;
        p[i].waitingTime = p[i].turnaroundTime - p[i].burstTime;

        totalWaitingTime += p[i].waitingTime;
        totalTurnaroundTime += p[i].turnaroundTime;

        ganttLabels.push_back("P" + to_string(p[i].pid));
        ganttTimes.push_back(p[i].completionTime);

        currentTime = p[i].completionTime;
    }

    // Output
    cout << "\nProcess\tArrival\tBurst\tStart\tCompletion\tWaiting\tTurnaround\n";
    for (auto &proc : p) {
        cout << "P" << proc.pid << "\t" << proc.arrivalTime << "\t" << proc.burstTime << "\t"
             << proc.startTime << "\t" << proc.completionTime << "\t"
             << proc.waitingTime << "\t" << proc.turnaroundTime << "\n";
    }

    cout << fixed << setprecision(2);
    cout << "\nAverage Waiting Time = " << totalWaitingTime / n;
    cout << "\nAverage Turnaround Time = " << totalTurnaroundTime / n << "\n";

    // Gantt Chart
    cout << "\nGantt Chart:\n";

    // Top bar
    for (auto &label : ganttLabels) {
        cout << " ";
        for (int i = 0; i < label.length() + 2; i++) cout << "-";
    }
    cout << "\n|";

    // Process labels
    for (auto &label : ganttLabels) {
        cout << " " << label << " |";
    }

    // Bottom bar
    cout << "\n";
    for (auto &label : ganttLabels) {
        cout << " ";
        for (int i = 0; i < label.length() + 2; i++) cout << "-";
    }

    // Time line
    cout << "\n" << setw(2) << setfill(' ') << (p[0].startTime < p[0].arrivalTime ? p[0].arrivalTime : p[0].startTime);
    for (auto &time : ganttTimes) {
        cout << setw(5) << time;
    }
    cout << "\n";

    return 0;
}
