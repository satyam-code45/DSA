#include <iostream>
#include <vector>
#include <limits>
using namespace std;

struct GanttSlot {
    int pid;    // process ID (starting from 1)
    int start;  // start time (inclusive)
    int end;    // end time (exclusive)
};

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    // Process information vectors (numbering is 1-based in output)
    vector<int> arrivalTime(n), burstTime(n), priority(n);
    
    for (int i = 0; i < n; i++) {
        cout << "Process " << i + 1 << ":\n";
        cout << "  Arrival Time: ";
        cin >> arrivalTime[i];
        cout << "  Burst Time: ";
        cin >> burstTime[i];
        cout << "  Priority (smaller number = higher priority): ";
        cin >> priority[i];
    }
    
    // Prepare arrays for scheduling simulation
    vector<int> remainingTime(n), completionTime(n, 0);
    for (int i = 0; i < n; i++) {
        remainingTime[i] = burstTime[i];
    }
    
    // For building the Gantt chart, we use an approach that tracks the current running process.
    vector<GanttSlot> schedule;
    int currentTime = 0;
    int completed = 0;
    
    // Variables for current running process and its segment start time.
    // currentPID holds the index of the currently running process (or -1 if idle).
    int currentPID = -1;
    int currentSegmentStart = 0;
    
    // Run simulation until all processes are complete
    while (completed < n) {
        // Select the process that has arrived and is not finished with the smallest priority value.
        int idx = -1;
        int minPriority = numeric_limits<int>::max();
        for (int i = 0; i < n; i++) {
            if (arrivalTime[i] <= currentTime && remainingTime[i] > 0) {
                if (priority[i] < minPriority) {
                    minPriority = priority[i];
                    idx = i;
                }
            }
        }
        
        // If the selected process (idx) is different from the currentPID, record the previous segment.
        if (idx != currentPID) {
            if (currentPID != -1) { // there was a process running before
                schedule.push_back({currentPID + 1, currentSegmentStart, currentTime});
            }
            currentSegmentStart = currentTime;
            currentPID = idx; // could be -1 if no process is ready (idle)
        }
        
        // If a process is ready, execute it for one time unit.
        if (idx != -1) {
            remainingTime[idx]--;
            if (remainingTime[idx] == 0) {
                completionTime[idx] = currentTime + 1;
                completed++;
            }
        }
        
        // Advance time by 1 unit.
        currentTime++;
    }
    
    // After simulation, if a process was running, record its last segment.
    if (currentPID != -1) {
        schedule.push_back({currentPID + 1, currentSegmentStart, currentTime});
    }
    
    // Compute preemptions for each process from the Gantt chart.
    // A process’s preemption count = (number of segments in which it appears) - 1.
    vector<int> segmentsCount(n, 0);
    for (const auto &slot : schedule) {
        // pid is stored 1-based, so subtract one for index.
        segmentsCount[slot.pid - 1]++;
    }
    
    // Calculate Turn-Around Time (TAT) and Waiting Time (WT)
    double totalTAT = 0, totalWT = 0;
    
    cout << "\nP#\tAT\tBT\tPrio\tCT\tTAT\tWT\t#Preemptions\n";
    for (int i = 0; i < n; i++) {
        int TAT = completionTime[i] - arrivalTime[i];
        int WT  = TAT - burstTime[i];
        totalTAT += TAT;
        totalWT  += WT;
        int preemptions = (segmentsCount[i] > 0) ? segmentsCount[i]  : 1;
        cout << (i + 1) << "\t"
             << arrivalTime[i] << "\t"
             << burstTime[i]   << "\t"
             << priority[i]    << "\t"
             << completionTime[i] << "\t"
             << TAT << "\t"
             << WT  << "\t"
             << preemptions << "\n";
    }
    
    cout << "\nAverage Turn-Around Time = " << (totalTAT / n) << endl;
    cout << "Average Waiting Time     = " << (totalWT / n) << endl;
    
    // Display the Gantt Chart
    cout << "\n===== Gantt Chart (Compressed) =====\n";
    for (size_t i = 0; i < schedule.size(); i++) {
        cout << "[" << schedule[i].start << " - " << schedule[i].end << "] P" << schedule[i].pid;
        if (i < schedule.size() - 1)
            cout << " | ";
    }
    cout << "\n";
    
    return 0;
}

