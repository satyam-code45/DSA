#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

class Process {
public:
    int id;
    int arrivalTime;
    int burstTime;
    int completionTime = 0;
    int turnaroundTime = 0;
    int waitingTime = 0;
};

bool compareArrivalTime(const Process &p1, const Process &p2) {
    return p1.arrivalTime < p2.arrivalTime;
}

int main() {
    int numProcesses;
    cout << "Enter the number of processes: ";
    cin >> numProcesses;
    
    Process processes[numProcesses];
    Process scheduledProcesses[numProcesses];

    for (int i = 0; i < numProcesses; i++) {
        cout << "Enter Arrival Time and Burst Time of process P" << i + 1 << ": ";
        cin >> processes[i].arrivalTime >> processes[i].burstTime;
        processes[i].id = i + 1;
    }
    
    copy(processes, processes + numProcesses, scheduledProcesses);
    sort(processes, processes + numProcesses, compareArrivalTime);

    vector<pair<int, int>> ganttChart;
    int currentTime = 0;
    int totalTurnaroundTime = 0;
    int totalWaitingTime = 0;
    
    for (int i = 0; i < numProcesses; i++) {
        if (currentTime < processes[i].arrivalTime) {
            currentTime = processes[i].arrivalTime;
        }
        currentTime += processes[i].burstTime;
        ganttChart.emplace_back(processes[i].id, currentTime);

        int index = processes[i].id - 1;
        scheduledProcesses[index].completionTime = currentTime;
        scheduledProcesses[index].turnaroundTime = scheduledProcesses[index].completionTime - scheduledProcesses[index].arrivalTime;
        scheduledProcesses[index].waitingTime = scheduledProcesses[index].turnaroundTime - scheduledProcesses[index].burstTime;

        totalTurnaroundTime += scheduledProcesses[index].turnaroundTime;
        totalWaitingTime += scheduledProcesses[index].waitingTime;
    }
    
    // Printing output
    cout << "\nGantt Chart:" << endl;
    cout << "-------------------------------------------------\n";
    cout << "| Process |";
    for (auto &entry : ganttChart) {
        cout << " P" << entry.first << " |";
    }
    cout << "\n| Time    |";
    for (auto &entry : ganttChart) {
        cout << " " << entry.second << " |";
    }
    cout << "\n-------------------------------------------------\n";

    cout << "\n| PID | AT | BT | CT | TAT | WT |" << endl;
    for (int i = 0; i < numProcesses; i++) {
        cout << "| " << scheduledProcesses[i].id
             << "   | " << scheduledProcesses[i].arrivalTime
             << "  | " << scheduledProcesses[i].burstTime
             << "  | " << scheduledProcesses[i].completionTime
             << "  | " << scheduledProcesses[i].turnaroundTime
             << "  | " << scheduledProcesses[i].waitingTime << " |" << endl;
    }
    cout << "-------------------------------------------------\n";
    
    cout << "Average Turnaround Time: " << (float)totalTurnaroundTime / numProcesses << endl;
    cout << "Average Waiting Time: " << (float)totalWaitingTime / numProcesses << endl;
    
    return 0;
}
