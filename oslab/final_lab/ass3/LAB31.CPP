#include <bits/stdc++.h>
using namespace std;

struct GanttEntry {
    int pid, start, end;
};

int main() {
    int n;
    cout << "Enter number of processes (>=10): ";
    cin >> n;

    vector<int> at(n), bt(n), rem_bt(n), pr(n);
    for (int i = 0; i < n; i++) {
        cout << "P" << i+1 << " Arrival Time, Burst Time, Priority: ";
        cin >> at[i] >> bt[i] >> pr[i];
        rem_bt[i] = bt[i];
    }

    vector<int> ct(n), tat(n), wt(n), preempt_count(n, 0);
    vector<GanttEntry> gantt;
    int completed = 0, time = 0, last_pid = -1;

    while (completed < n) {
        // Select highest-priority ready process
        int idx = -1;
        for (int i = 0; i < n; i++) {
            if (rem_bt[i] > 0 && at[i] <= time) {
                if (idx == -1
                    || pr[i] < pr[idx]
                    || (pr[i] == pr[idx] && at[i] < at[idx])
                    || (pr[i] == pr[idx] && at[i] == at[idx] && i < idx)) {
                    idx = i;
                }
            }
        }

        if (idx == -1) {
            // CPU idle
            time++;
            continue;
        }

        // Preemption detection
        if (last_pid != -1 && last_pid != idx && rem_bt[last_pid] > 0)
            preempt_count[last_pid]++;

        // Record Gantt
        if (gantt.empty() || gantt.back().pid != idx) {
            gantt.push_back({idx, time, time+1});
        } else {
            gantt.back().end++;
        }

        last_pid = idx;
        // Execute one time unit
        rem_bt[idx]--;
        time++;

        // If process completes
        if (rem_bt[idx] == 0) {
            completed++;
            ct[idx]  = time;
            tat[idx] = ct[idx] - at[idx];
            wt[idx]  = tat[idx] - bt[idx];
        }
    }

    // Display Gantt chart
    cout << "\nGantt Chart:\n|";
    for (auto &e : gantt) {
        cout << " P" << e.pid+1 << " |";
    }
    cout << "\n0";
    for (auto &e : gantt) {
        cout << "\t" << e.end;
    }
    cout << "\n";

    // Output table
    double sumTAT = 0, sumWT = 0;
    cout << "\nPID\tAT\tBT\tPR\tCT\tTAT\tWT\tPreemptions\n";
    for (int i = 0; i < n; i++) {
        cout << i+1 << "\t"
             << at[i] << "\t"
             << bt[i] << "\t"
             << pr[i] << "\t"
             << ct[i] << "\t"
             << tat[i] << "\t"
             << wt[i] << "\t"
             << preempt_count[i] << "\n";
        sumTAT += tat[i];
        sumWT  += wt[i];
    }

    cout << fixed << setprecision(2)
         << "\nAverage Turn-Around Time = " << (sumTAT / n) << "\n"
         << "Average Waiting Time    = " << (sumWT  / n) << "\n";

    return 0;
}
