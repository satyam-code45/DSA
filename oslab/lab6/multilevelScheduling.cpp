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
    int id, at, bt, remaning_bt, ct = 0, tat = 0, wt = 0, preemptions = 0, priority;
};

bool comp(const Process &p1, const Process &p2)
{
    return p1.at < p2.at;
}

bool compid(const Process &p1, const Process &p2)
{
    return p1.id < p2.id;
}

void rrScheduling(vector<Process> &processes, queue<int> &rq, int timeQuantum)
{
    if (rq.empty())
        return; // Avoid running if the queue is empty

    // Case when time quantum is 1 (special case optimization)
        int i = rq.front() - 1; // Ensure correct indexing
        if (processes[i].remaning_bt > 0)
        {
            if (processes[i].remaning_bt >= timeQuantum)
            {
                processes[i].remaning_bt -= timeQuantum;
                currentTime += timeQuantum;
            }
            else
            {
                currentTime += processes[i].remaning_bt;
                processes[i].remaning_bt = 0;
                rq.pop(); // Remove completed process
            }

            if (gantt_chart.empty() || gantt_chart.back().first != processes[i].id)
            {
                gantt_chart.emplace_back(processes[i].id, currentTime);

                // Increment preemptions only if this is not the first process being scheduled
                if (gantt_chart.size() > 1)
                {
                    processes[i].preemptions++;
                }
            }
            else
            {
                // Update end time of the last process in the Gantt chart
                gantt_chart.back().second = currentTime;
            }
        return;
    }

    // General case (time quantum > 1)
    while (!rq.empty())
    {
        int i = rq.front() - 1; // Ensure correct indexing
        rq.pop();               // Remove from queue only after processing

        if (processes[i].remaning_bt > 0)
        {
            int executedTime = min(processes[i].remaning_bt, timeQuantum);
            processes[i].remaning_bt -= executedTime;
            currentTime += executedTime;

            if (gantt_chart.empty() || gantt_chart.back().first != processes[i].id)
            {
                gantt_chart.emplace_back(processes[i].id, currentTime);

                // Only increment preemptions if the process was previously scheduled
                if (gantt_chart.size() > 1)
                {
                    processes[i].preemptions++;
                }
            }
            else
            {
                gantt_chart.back().second = currentTime;
            }

            // If the process is not finished, put it back in the queue
            if (processes[i].remaning_bt > 0)
            {
                rq.push(processes[i].id);
            }
        }
    }
}

void fcfs(vector<Process> &processes, queue<int> &rq, int timeQuantum)
{
    if (timeQuantum)
    {
        int i = rq.front() - 1;
        currentTime += timeQuantum;
        processes[i].remaning_bt -= timeQuantum;
        if (gantt_chart.empty() || gantt_chart.back().first != processes[i].id)
        {
            gantt_chart.emplace_back(processes[i].id, currentTime);

            // Increment preemptions only if this is not the first process being scheduled
            if (gantt_chart.size() > 1)
            {
                processes[i].preemptions++;
            }
        }
        else
        {
            // Update end time of the last process in the Gantt chart
            gantt_chart.back().second = currentTime;
        }
        if (processes[i].remaning_bt == 0)
        {
           rq.pop();
        }
        
        return;
    }
    else
    {
        while (!rq.empty())
        {
            int i = rq.front() - 1;
            currentTime += processes[i].remaning_bt;
            processes[i].remaning_bt = 0;
            gantt_chart.emplace_back(processes[i].id, currentTime);
            rq.pop();
        }
    }
}

int main()
{
    int n;
    cout << "Enter number of processes: ";
    cin >> n;
    int timeQuantum[4];
    cout << "Enter the time Quantum: ";
    cin >> timeQuantum[0] >> timeQuantum[1] >> timeQuantum[2] >> timeQuantum[3];
    vector<Process> processes(n);
    for (int i = 0; i < n; i++)
    {
        cout << "Enter Arrival Time, Burst Time and Priority for process " << i + 1 << ": ";
        cin >> processes[i].at >> processes[i].bt >> processes[i].priority;
        processes[i].id = i + 1;
        processes[i].remaning_bt = processes[i].bt;
    }
    sort(processes.begin(), processes.end(), comp);

    bool executing[5];

    queue<int> rq[5];

    int i = 0;
    executing[processes[0].priority - 1] = true;
    currentTime = processes[0].at;
    while (processes[i].at <= currentTime)
    {
        int j = 0;
        for (j = 0; j < 5; j++)
        {
            if (executing[j])
            {
                if (j < 4)
                {
                    rrScheduling(processes, rq[j], 1);
                }
                else
                    fcfs(processes, rq[j], 1);
                executing[j] = false;
                break;
            }
        }
        i++;
        rq[processes[i].priority - 1].push(processes[i].id);
        if (j >= (processes[i].priority - 1))
        {
            executing[processes[i].priority - 1] = true;
        }
        else
            executing[j] = true;
        if (i >= n) break;
    }

    while (i < n)
    {
        i++;
        switch (processes[i].priority)
        {
        case 1:
            rq[0].push(processes[i].id);
            break;

        case 2:
            rq[1].push(processes[i].id);
            break;
        case 3:
            rq[2].push(processes[i].id);
            break;
        case 4:
            rq[3].push(processes[i].id);
            break;
        case 5:
            rq[4].push(processes[i].id);
            break;
        default:
            break;
        }
    }

    for (int j = 0; j < 4; j++)
    {
        rrScheduling(processes, rq[j], timeQuantum[j]);
    }

    fcfs(processes, rq[4], 0);

    // Calculate completion time (CT)
    int process = 1;
    for (int i = gantt_chart.size() - 1; i >= 0; i--)
    {
        if (processes[gantt_chart[i].first - 1].ct == 0)
        {
            processes[gantt_chart[i].first - 1].ct = gantt_chart[i].second;
            process++;
        }
        if (process > n)
        {
            break;
        }
    }

    // sorted the processes again to bascially make the output look good
    sort(processes.begin(), processes.end(), compid);

    // Calculate turnaround time (TAT) and waiting time (WT)
    for (int i = 0; i < n; i++)
    {
        processes[i].tat = processes[i].ct - processes[i].at;
        totalTAT += processes[i].tat;
        processes[i].wt = processes[i].tat - processes[i].bt;
        totalWT += processes[i].wt;
    }

    // Print Gantt Chart
    cout << "\nGantt Chart:\n";
    cout << "--------------------------------------------------\n";
    cout << "| Process |";
    for (auto &entry : gantt_chart)
    {
        cout << " P" << entry.first << " |";
    }
    cout << "\n| Time    | 0 ";
    for (auto &entry : gantt_chart)
    {
        cout << "\t" << entry.second;
    }
    cout << "\n--------------------------------------------------\n";

    // Print process table with preemptions count
    cout << "\nProcess Table:\n";
    cout << "--------------------------------------------------\n";
    cout << "| Ps | AT | BT | CT | TAT | WT | Preemptions |\n";
    cout << "--------------------------------------------------\n";
    for (int i = 0; i < n; i++)
    {
        cout << "| " << processes[i].id << " | " << processes[i].at << " | " << processes[i].bt << " | "
             << processes[i].ct << " | " << processes[i].tat << " | " << processes[i].wt << " | " << processes[i].preemptions << " |\n";
    }
    cout << "--------------------------------------------------\n";

    cout << "\nAverage Turnaround Time: " << totalTAT / n;
    cout << "\nAverage Waiting Time: " << totalWT / n << endl;
    return 0;
}
