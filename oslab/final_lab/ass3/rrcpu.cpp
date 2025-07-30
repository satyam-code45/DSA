#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, quantum;
    cout << "Enter number of processes: ";
    cin >> n;
    vector<int> bt(n), at(n), rt(n), wt(n, 0), tat(n), ct(n);

    for (int i = 0; i < n; i++) {
        cout << "Process " << i+1 << ":\nAT: ";
        cin >> at[i];
        cout << "BT: ";
        cin >> bt[i];
        rt[i] = bt[i];
    }

    cout << "Enter Time Quantum: ";
    cin >> quantum;

    int t = 0, completed = 0;
    cout << "\nGantt Chart:\n--------------------------------------------------\n";

    while (completed < n) {
        bool done = true;
        for (int i = 0; i < n; i++) {
            if (rt[i] > 0 && at[i] <= t) {
                done = false;
                int exec = min(quantum, rt[i]);
                cout << "|P" << i+1 << "(" << t << "-" << t+exec << ")";
                t += exec;
                rt[i] -= exec;

                if (rt[i] == 0) {
                    ct[i] = t;
                    tat[i] = ct[i] - at[i];
                    wt[i] = tat[i] - bt[i];
                    completed++;
                }
            }
        }
        if (done) {
            cout << "|Idle(" << t << "-" << t+1 << ")";
            t++;
        }
    }

    cout << "|\n--------------------------------------------------\n\n";

    float avg_wt = 0, avg_tat = 0;
    cout << "PID\tAT\tBT\tCT\tTAT\tWT\n";
    for (int i = 0; i < n; i++) {
        avg_wt += wt[i];
        avg_tat += tat[i];
        cout << i+1 << "\t" << at[i] << "\t" << bt[i] << "\t" << ct[i]
             << "\t" << tat[i] << "\t" << wt[i] << "\n";
    }

    cout << "\nAverage Waiting Time: " << avg_wt / n;
    cout << "\nAverage Turnaround Time: " << avg_tat / n << "\n";
    return 0;
}
