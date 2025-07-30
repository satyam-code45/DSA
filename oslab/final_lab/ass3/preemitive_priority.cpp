#include <iostream>
#include <vector>
using namespace std;

struct Process {
    int pid, at, bt, rt, prio;
    int ct = 0, tat = 0, wt = 0;
};

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> p(n);
    cout << "Enter Arrival Time, Burst Time, and Priority (Lower number = Higher Priority):\n";
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        cout << "P" << i + 1 << " AT: ";
        cin >> p[i].at;
        cout << "P" << i + 1 << " BT: ";
        cin >> p[i].bt;
        cout << "P" << i + 1 << " Priority: ";
        cin >> p[i].prio;
        p[i].rt = p[i].bt;
    }

    int completed = 0, time = 0;
    float total_wt = 0, total_tat = 0;
    cout << "\nGantt Chart:\n--------------------------------------------------\n";

    while (completed < n) {
        int idx = -1;
        int min_priority = 1e9;

        for (int i = 0; i < n; i++) {
            if (p[i].at <= time && p[i].rt > 0 && p[i].prio < min_priority) {
                min_priority = p[i].prio;
                idx = i;
            }
        }

        if (idx != -1) {
            cout << "|P" << p[idx].pid << "(" << time << "-" << time + 1 << ")";
            p[idx].rt--;
            if (p[idx].rt == 0) {
                p[idx].ct = time + 1;
                p[idx].tat = p[idx].ct - p[idx].at;
                p[idx].wt = p[idx].tat - p[idx].bt;
                total_tat += p[idx].tat;
                total_wt += p[idx].wt;
                completed++;
            }
        } else {
            cout << "|Idle(" << time << "-" << time + 1 << ")";
        }

        time++;
    }

    cout << "|\n--------------------------------------------------\n\n";
    cout << "PID\tAT\tBT\tPrio\tCT\tTAT\tWT\n";
    for (const auto &proc : p) {
        cout << proc.pid << "\t" << proc.at << "\t" << proc.bt << "\t" << proc.prio << "\t"
             << proc.ct << "\t" << proc.tat << "\t" << proc.wt << "\n";
    }

    cout << "\nAverage Waiting Time: " << total_wt / n;
    cout << "\nAverage Turnaround Time: " << total_tat / n << "\n";

    return 0;
}
