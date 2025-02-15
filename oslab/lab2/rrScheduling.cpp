#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

struct rrScheduling
{
    int id;
    int at;
    int bt;
    int ct = 0;
    int tat = 0;
    int wt = 0;
};

bool comp(const rrScheduling &rr1, const rrScheduling &rr2)
{
    return rr1.at < rr2.at;
}

int main()
{
    int n;
    cout << "Enter no of processes: ";
    cin >> n;
    int timeQuantum;
    cout << "Enter Time Quantum: ";
    cin >> timeQuantum;

    rrScheduling rr[n];
    for (int i = 0; i < n; i++)
    {
        cout << "\nEnter the Arrival Time and Burst Time of process " << i + 1 << ": ";
        cin >> rr[i].at >> rr[i].bt;
        rr[i].id = i + 1;
    }

    queue<int> rq;
    rrScheduling rrfinal[n];
    copy(rr, rr + n, rrfinal);

    sort(rr, rr + n, comp);

    vector<pair<int, int>> gantt_chart;
    int currentTime = 0;
    float totalTAT = 0, totalWT = 0;

    rq.push(rr[0].id);
    int count = 1;

    int preemptions[n] = {0}; // Track preemptions for each process

    // Round Robin Scheduling logic
    while (!rq.empty())
    {
        int i = rq.front() - 1;
        rq.pop();

        if (rr[i].bt >= timeQuantum)
        {
            currentTime += timeQuantum;
            gantt_chart.emplace_back(i + 1, currentTime);
            rr[i].bt -= timeQuantum;

            if (rr[i].bt > 0) // Process not finished, so it's preempted
                preemptions[i]++;
        }
        else
        {
            currentTime += rr[i].bt;
            gantt_chart.emplace_back(i + 1, currentTime);
            rr[i].bt = 0;
        }

        // New arrivals
        while (count < n)
        {
            if (rr[count].at <= currentTime)
            {
                rq.push(rr[count].id);
                count++;
            }
            else
            {
                break;
            }
        }
        if (rr[i].bt > 0)
        {
            rq.push(rr[i].id);
        }
    }

    // Calculate completion time (CT)
    int process = 1;
    for (int i = gantt_chart.size() - 1; i >= 0; i--)
    {
        if (rrfinal[gantt_chart[i].first - 1].ct == 0)
        {
            rrfinal[gantt_chart[i].first - 1].ct = gantt_chart[i].second;
            process++;
        }
        if (process > n)
        {
            break;
        }
    }

    // Calculate turnaround time (TAT) and waiting time (WT)
    for (int i = 0; i < n; i++)
    {
        rrfinal[i].tat = rrfinal[i].ct - rrfinal[i].at;
        totalTAT += rrfinal[i].tat;
        rrfinal[i].wt = rrfinal[i].tat - rrfinal[i].bt;
        totalWT += rrfinal[i].wt;
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
        cout << "| " << rrfinal[i].id << " | " << rrfinal[i].at << " | " << rrfinal[i].bt << " | "
             << rrfinal[i].ct << " | " << rrfinal[i].tat << " | " << rrfinal[i].wt << " | " << preemptions[i] << " |\n";
    }
    cout << "--------------------------------------------------\n";

    // Print average waiting time and turnaround time
    cout << "\nAverage Waiting Time: " << totalWT / n;
    cout << "\nAverage Turnaround Time: " << totalTAT / n << endl;
    cout << "--------------------------------------------------\n";

    return 0;
}
