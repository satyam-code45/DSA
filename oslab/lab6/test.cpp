#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

vector<pair<int, int>> gantt_chart;
int currentTime = 0;
float totalTAT = 0, totalWT = 0;

struct Process
{
    int id, at, bt, rem_bt, ct = 0, tat = 0, wt = 0, preemptions = 0, priority;
};

bool comp(const Process &p1, const Process &p2) { return p1.at < p2.at; }
bool compid(const Process &p1, const Process &p2) { return p1.id < p2.id; }

int main()
{
    int n;
    cout << "Enter number of processes (at least 25): ";
    cin >> n;
    int timeQuantum[4];
    cout << "Enter time quanta for queues 1-4: ";
    cin >> timeQuantum[0] >> timeQuantum[1] >> timeQuantum[2] >> timeQuantum[3];

    vector<Process> processes(n);
    for (int i = 0; i < n; i++)
    {
        cout << "Enter AT, BT, Priority (1-5) for P" << i + 1 << ": ";
        cin >> processes[i].at >> processes[i].bt >> processes[i].priority;
        processes[i].id = i + 1;
        processes[i].rem_bt = processes[i].bt;
    }
    sort(processes.begin(), processes.end(), comp);

    queue<int> rq[5]; // 5 queues (0:system, 1:interactive, ..., 4:student)
    int next_process = 0;
    int current_q = -1, current_pid = -1, remaining_quantum = 0;

    while (true)
    {
        // Add arrived processes to their queues
        while (next_process < n && processes[next_process].at <= currentTime)
        {
            int q = processes[next_process].priority - 1;
            if (q < 0 || q >= 5)
                q = 4; // fallback to lowest priority
            rq[q].push(processes[next_process].id);
            next_process++;
        }

        // Check for preemption by higher priority queues
        if (current_q != -1)
        {
            bool preempt = false;
            for (int q = 0; q < current_q; q++)
            {
                if (!rq[q].empty())
                {
                    preempt = true;
                    break;
                }
            }
            if (preempt)
            {
                Process &p = processes[current_pid - 1];
                p.preemptions++;
                rq[current_q].push(current_pid);
                current_q = -1;
                current_pid = -1;
                remaining_quantum = 0;
            }
        }

        // Select highest priority non-empty queue
        int selected_q = -1;
        for (int q = 0; q < 5; q++)
        {
            if (!rq[q].empty())
            {
                selected_q = q;
                break;
            }
        }

        if (selected_q == -1)
        {
            if (next_process < n)
            {
                currentTime = processes[next_process].at;
                continue;
            }
            else
                break; // All done
        }

        // Get process from selected queue
        int pid = rq[selected_q].front();
        Process &p = processes[pid - 1];

        // If switching process, handle preemption
        if (selected_q != current_q && current_q != -1)
        {
            Process &curr_p = processes[current_pid - 1];
            curr_p.preemptions++;
            rq[current_q].push(current_pid);
            current_q = -1;
            current_pid = -1;
            remaining_quantum = 0;
        }

        // Determine execution time
        int exec_time;
        if (selected_q < 4) // RR queues
        {
            if (remaining_quantum == 0)
                remaining_quantum = timeQuantum[selected_q];
            exec_time = min(remaining_quantum, p.rem_bt);

            // Check for next arrival during execution
            if (next_process < n)
            {
                int next_at = processes[next_process].at;
                int max_exec = next_at - currentTime;
                if (max_exec > 0)
                    exec_time = min(exec_time, max_exec);
            }
        }
        else // FCFS queue
        {
            exec_time = p.rem_bt;
            // Check for next arrival or higher priority
            if (next_process < n)
            {
                int next_at = processes[next_process].at;
                int max_exec = next_at - currentTime;
                if (max_exec > 0)
                    exec_time = min(exec_time, max_exec);
            }
        }

        // Execute the process
        currentTime += exec_time;
        p.rem_bt -= exec_time;
        if (selected_q < 4)
            remaining_quantum -= exec_time;

        // Update Gantt chart
        if (!gantt_chart.empty() && gantt_chart.back().first == pid)
            gantt_chart.back().second = currentTime;
        else
            gantt_chart.emplace_back(pid, currentTime);

        // Check if process finished
        if (p.rem_bt == 0)
        {
            rq[selected_q].pop();
            p.ct = currentTime;
            current_q = -1;
            current_pid = -1;
            remaining_quantum = 0;
        }
        else if (selected_q < 4 && remaining_quantum == 0)
        {
            rq[selected_q].pop();
            rq[selected_q].push(pid);
            current_q = -1;
            current_pid = -1;
        }
        else
        {
            current_q = selected_q;
            current_pid = pid;
        }
    }

    // Calculate TAT, WT
    sort(processes.begin(), processes.end(), compid);
    for (auto &p : processes)
    {
        p.tat = p.ct - p.at;
        p.wt = p.tat - p.bt;
        totalTAT += p.tat;
        totalWT += p.wt;
    }

    // Print results
    cout << "\nGantt Chart:\n";
    cout << "--------------------------------------------------\n";
    cout << "| Process |";
    for (auto &entry : gantt_chart)
        cout << " P" << entry.first << " |";
    cout << "\n| Time    | 0 ";
    for (auto &entry : gantt_chart)
        cout << "\t" << entry.second;
    cout << "\n--------------------------------------------------\n";

    cout << "\nProcess Table:\n";
    cout << "--------------------------------------------------\n";
    cout << "| Ps | AT | BT | CT | TAT | WT | Preemptions |\n";
    cout << "--------------------------------------------------\n";
    for (auto &p : processes)
        printf("| %2d | %2d | %2d | %3d | %3d | %2d | %11d |\n",
               p.id, p.at, p.bt, p.ct, p.tat, p.wt, p.preemptions);
    cout << "--------------------------------------------------\n";

    cout << "\nAverage Turnaround Time: " << totalTAT / n;
    cout << "\nAverage Waiting Time: " << totalWT / n << endl;

    return 0;
}