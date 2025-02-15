#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

struct Process {
    int id, at, bt, remaining_bt, ct, tat, wt;
};

bool comp(const Process &p1, const Process &p2) {
    return p1.at < p2.at;
}

void executeRR(queue<int> &q, vector<Process> &processes, int &currentTime, int timeQuantum) {
    int size = q.size();
    while (size--) {
        int i = q.front();
        q.pop();
        if (processes[i].remaining_bt > timeQuantum) {
            processes[i].remaining_bt -= timeQuantum;
            currentTime += timeQuantum;
            q.push(i);
        } else {
            currentTime += processes[i].remaining_bt;
            processes[i].ct = currentTime;
            processes[i].remaining_bt = 0;
        }
    }
}

void executeFCFS(queue<int> &q, vector<Process> &processes, int &currentTime) {
    while (!q.empty()) {
        int i = q.front();
        q.pop();
        currentTime += processes[i].remaining_bt;
        processes[i].ct = currentTime;
        processes[i].remaining_bt = 0;
    }
}

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> processes(n);
    for (int i = 0; i < n; i++) {
        cout << "Enter Arrival Time and Burst Time for process " << i + 1 << ": ";
        cin >> processes[i].at >> processes[i].bt;
        processes[i].id = i + 1;
        processes[i].remaining_bt = processes[i].bt;
    }

    sort(processes.begin(), processes.end(), comp);

    queue<int> Q1, Q2, Q3, Q4;
    int currentTime = 0, timeQuantum1 = 4, timeQuantum2 = 8, timeQuantum3 = 16;
    int idx = 0;

    while (idx < n || !Q1.empty() || !Q2.empty() || !Q3.empty() || !Q4.empty()) {
        while (idx < n && processes[idx].at <= currentTime) {
            Q1.push(idx++);
        }
        if (!Q1.empty()) executeRR(Q1, processes, currentTime, timeQuantum1);
        else if (!Q2.empty()) executeRR(Q2, processes, currentTime, timeQuantum2);
        else if (!Q3.empty()) executeRR(Q3, processes, currentTime, timeQuantum3);
        else if (!Q4.empty()) executeFCFS(Q4, processes, currentTime);
        else currentTime = processes[idx].at;
    }

    float totalTAT = 0, totalWT = 0;
    cout << "\nID  AT  BT  CT  TAT  WT\n";
    for (int i = 0; i < n; i++) {
        processes[i].tat = processes[i].ct - processes[i].at;
        processes[i].wt = processes[i].tat - processes[i].bt;
        totalTAT += processes[i].tat;
        totalWT += processes[i].wt;
        cout << processes[i].id << "   " << processes[i].at << "   " << processes[i].bt << "   "
             << processes[i].ct << "   " << processes[i].tat << "   " << processes[i].wt << endl;
    }

    cout << "\nAverage Turnaround Time: " << totalTAT / n;
    cout << "\nAverage Waiting Time: " << totalWT / n << endl;
    return 0;
}
