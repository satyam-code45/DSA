#include <iostream>
#include <vector>
using namespace std;

class Process {
public:
    int pid, at, bt, rt, ct, wt, tat;
    Process(int id, int a, int b) : pid(id), at(a), bt(b), rt(b) {}
};

class RoundRobinScheduler {
private:
    vector<Process> processes;
    int quantum;

public:
    RoundRobinScheduler(int q) : quantum(q) {}

    void addProcess(int at, int bt) {
        processes.emplace_back(processes.size() + 1, at, bt);
    }

    void schedule() {
        int t = 0, completed = 0, n = processes.size();
        cout << "\nGantt Chart:\n--------------------------------------------------\n";

        while (completed < n) {
            bool done = true;
            for (auto &p : processes) {
                if (p.rt > 0 && p.at <= t) {
                    done = false;
                    int exec = min(p.rt, quantum);
                    cout << "|P" << p.pid << "(" << t << "-" << t + exec << ")";
                    t += exec;
                    p.rt -= exec;
                    if (p.rt == 0) {
                        p.ct = t;
                        p.tat = p.ct - p.at;
                        p.wt = p.tat - p.bt;
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
    }

    void displayResults() {
        float avg_wt = 0, avg_tat = 0;
        cout << "PID\tAT\tBT\tCT\tTAT\tWT\n";
        for (auto &p : processes) {
            avg_wt += p.wt;
            avg_tat += p.tat;
            cout << p.pid << "\t" << p.at << "\t" << p.bt << "\t" << p.ct
                 << "\t" << p.tat << "\t" << p.wt << "\n";
        }
        cout << "\nAverage Waiting Time: " << avg_wt / processes.size();
        cout << "\nAverage Turnaround Time: " << avg_tat / processes.size() << "\n";
    }
};
int main() {
    RoundRobinScheduler scheduler(3); // quantum = 3
    scheduler.addProcess(0, 5);
    scheduler.addProcess(1, 3);
    scheduler.addProcess(2, 8);
    scheduler.addProcess(3, 6);
    scheduler.schedule();
    scheduler.displayResults();
    return 0;
}
