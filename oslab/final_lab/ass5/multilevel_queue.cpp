#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Process {
    int id;
    int arrival;
    int burst;
    int remaining;
    int priority;
    int start = -1;
    int finish = 0;
    int waiting = 0;
    int turnaround = 0;
    bool completed = false;
};

bool arrivalSort(const Process &a, const Process &b) {
    return a.arrival < b.arrival;
}

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> processes(n);
    for (int i = 0; i < n; i++) {
        cout << "\nProcess " << i + 1 << ":\n";
        processes[i].id = i + 1;
        cout << "Arrival Time: ";
        cin >> processes[i].arrival;
        cout << "Burst Time: ";
        cin >> processes[i].burst;
        processes[i].remaining = processes[i].burst;
        cout << "Queue (1-5) [1=High, 5=Low]: ";
        cin >> processes[i].priority;
    }

    sort(processes.begin(), processes.end(), arrivalSort);

    vector<queue<Process*>> queues(5);
    int time = 0, completed = 0, preemptions = 0;
    Process* current = nullptr;

    while (completed < n) {
        // Push newly arrived processes into their queues
        for (auto &p : processes) {
            if (p.arrival == time) {
                queues[p.priority - 1].push(&p);
            }
        }

        // Check if a higher-priority process is now available
        for (int i = 0; i < 5; i++) {
            if (!queues[i].empty()) {
                if (current == nullptr || current->priority > i + 1) {
                    if (current != nullptr && current->remaining > 0) {
                        // Preempt current process
                        queues[current->priority - 1].push(current);
                        preemptions++;
                    }
                    current = queues[i].front();
                    queues[i].pop();
                }
                break;
            }
        }

        if (current != nullptr) {
            if (current->start == -1)
                current->start = time;

            current->remaining--;

            if (current->remaining == 0) {
                current->finish = time + 1;
                current->turnaround = current->finish - current->arrival;
                current->waiting = current->turnaround - current->burst;
                current->completed = true;
                completed++;
                current = nullptr;
            }
        }

        time++;
    }

    // Output
    double totalTAT = 0, totalWT = 0;
    cout << "\nID\tArrival\tBurst\tQueue\tTAT\tWT\n";
    for (auto &p : processes) {
        totalTAT += p.turnaround;
        totalWT += p.waiting;
        cout << p.id << "\t" << p.arrival << "\t" << p.burst << "\t"
             << p.priority << "\t" << p.turnaround << "\t" << p.waiting << endl;
    }

    cout << "\nAverage Turnaround Time: " << totalTAT / n;
    cout << "\nAverage Waiting Time: " << totalWT / n;
    cout << "\nPreemptions (due to lower-priority arrival): " << preemptions << endl;

    return 0;
}
