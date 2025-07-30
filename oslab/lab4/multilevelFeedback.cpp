// 1) Write a program in C or C++ to implement the multilevel feedback queue cpu scheduling algo.find the avg tat,wt.
#include<bits/stdc++.h>
using namespace std;

vector<pair<int, int>> gantt_chart;
int currentTime = 0;
float totalTAT = 0, totalWT = 0;

struct Process
{
    int id, at, bt, remaning_bt, ct = 0, tat = 0, wt = 0, preemptions = 0;
};

//compare on at
bool comp(const Process &p1, const Process &p2)
{
    return p1.at < p2.at;
}

//compare on id 
bool compid(const Process &p1, const Process &p2)
{
    return p1.id < p2.id;
}

void rrScheduling(vector<Process> &processes, queue<int> &rq, queue<int> &nq, int timeQuantum, int n)
{
    // Round Robin Scheduling logic
    while (!rq.empty())
    {
        int i = rq.front() - 1;
        rq.pop();
        if (processes[i].remaning_bt >= timeQuantum)
        {
            processes[i].remaning_bt -= timeQuantum;
            currentTime += timeQuantum;
            gantt_chart.emplace_back(processes[i].id, currentTime);
        }
        else
        {
            currentTime += processes[i].remaning_bt;
            processes[i].remaning_bt = 0;
            gantt_chart.emplace_back(processes[i].id, currentTime);
        }
        // If the current process remaning_bt>0 push it to the nq
        if (processes[i].remaning_bt > 0)
        {
            processes[i].preemptions++;
            nq.push(processes[i].id);
        }
    }
}

int main()
{
    int n;
    cout << "Enter number of processes: ";
    cin >> n;
    int timeQuantum1, timeQuantum2, timeQuantum3;
    cout << "Enter the time Quantum: ";
    cin >> timeQuantum1 >> timeQuantum2 >> timeQuantum3;
    vector<Process> processes(n);
    for (int i = 0; i < n; i++)
    {
        cout << "Enter Arrival Time and Burst Time for process " << i + 1 << ": ";
        cin >> processes[i].at >> processes[i].bt;
        processes[i].id = i + 1;
        processes[i].remaning_bt = processes[i].bt;
    }
    sort(processes.begin(), processes.end(), comp);

    queue<int> Q1, Q2, Q3, Q4;
    for (int i = 0; i < n; i++)
    {
        Q1.push(processes[i].id);
    }
    
    rrScheduling(processes, Q1, Q2, timeQuantum1, n);  
    rrScheduling(processes, Q2, Q3, timeQuantum2, n);
    rrScheduling(processes, Q3, Q4, timeQuantum3, n);

    // once these three rrScheduling runs we will be left with a Q4 containing the process that are still not completed
    // now we have to just do a fcfs

    while (!Q4.empty())
    {
        int i = Q4.front() - 1;
        currentTime += processes[i].remaning_bt;
        processes[i].remaning_bt = 0;
        gantt_chart.emplace_back(processes[i].id, currentTime);
        Q4.pop();
    }

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
