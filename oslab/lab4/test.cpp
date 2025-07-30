
// Assignment 1
// 1) Write a program in C or C++ to implement the First Come First Service (FCFS) CPU scheduling 

// #include <iostream>
// #include <vector>
// #include <iomanip>
// #include <algorithm>

// using namespace std;

// struct Process {
//     int pid;
//     int arrivalTime;
//     int burstTime;
//     int startTime;
//     int completionTime;
//     int turnaroundTime;
//     int waitingTime;
// };

// bool compareByArrival(Process a, Process b) {
//     return a.arrivalTime < b.arrivalTime;
// }

// int main() {
//     int n;
//     cout << "Enter number of processes: ";
//     cin >> n;

//     vector<Process> p(n);

//     for (int i = 0; i < n; i++) {
//         p[i].pid = i + 1;
//         cout << "Enter arrival time and burst time for Process " << p[i].pid << ": ";
//         cin >> p[i].arrivalTime >> p[i].burstTime;
//     }

//     // Sort by arrival time
//     sort(p.begin(), p.end(), compareByArrival);

//     int currentTime = 0;
//     float totalWaitingTime = 0, totalTurnaroundTime = 0;
//     vector<string> ganttLabels;
//     vector<int> ganttTimes;

//     for (int i = 0; i < n; i++) {
//         if (currentTime < p[i].arrivalTime) {
//             ganttLabels.push_back("IDLE");
//             ganttTimes.push_back(p[i].arrivalTime);
//             currentTime = p[i].arrivalTime;
//         }

//         p[i].startTime = currentTime;
//         p[i].completionTime = currentTime + p[i].burstTime;
//         p[i].turnaroundTime = p[i].completionTime - p[i].arrivalTime;
//         p[i].waitingTime = p[i].turnaroundTime - p[i].burstTime;

//         totalWaitingTime += p[i].waitingTime;
//         totalTurnaroundTime += p[i].turnaroundTime;

//         ganttLabels.push_back("P" + to_string(p[i].pid));
//         ganttTimes.push_back(p[i].completionTime);

//         currentTime = p[i].completionTime;
//     }

//     // Output
//     cout << "\nProcess\tArrival\tBurst\tStart\tCompletion\tWaiting\tTurnaround\n";
//     for (auto &proc : p) {
//         cout << "P" << proc.pid << "\t" << proc.arrivalTime << "\t" << proc.burstTime << "\t"
//              << proc.startTime << "\t" << proc.completionTime << "\t"
//              << proc.waitingTime << "\t" << proc.turnaroundTime << "\n";
//     }

//     cout << fixed << setprecision(2);
//     cout << "\nAverage Waiting Time = " << totalWaitingTime / n;
//     cout << "\nAverage Turnaround Time = " << totalTurnaroundTime / n << "\n";

//     // Gantt Chart
//     cout << "\nGantt Chart:\n";

//     // Top bar
//     for (auto &label : ganttLabels) {
//         cout << " ";
//         for (int i = 0; i < label.length() + 2; i++) cout << "-";
//     }
//     cout << "\n|";

//     // Process labels
//     for (auto &label : ganttLabels) {
//         cout << " " << label << " |";
//     }

//     // Bottom bar
//     cout << "\n";
//     for (auto &label : ganttLabels) {
//         cout << " ";
//         for (int i = 0; i < label.length() + 2; i++) cout << "-";
//     }

//     // Time line
//     cout << "\n" << setw(2) << setfill(' ') << (p[0].startTime < p[0].arrivalTime ? p[0].arrivalTime : p[0].startTime);
//     for (auto &time : ganttTimes) {
//         cout << setw(5) << time;
//     }
//     cout << "\n";

//     return 0;
// }






// 2) Write a program in C or C++ to implement the Non-Preemptive Shortest Job First (SJF) CPU 
// scheduling algorithm. Find the average Trun-Around Time (TAT) and average Waiting Time 
// (WT). Your program will work for at least 10 processes. 
// #include <stdio.h>

// struct Process {
//     int pid;
//     int burst_time;
//     int arrival_time;
//     int waiting_time;
//     int turnaround_time;
//     int completed;
//     int start_time;
// };

// void sort_by_arrival_time(struct Process p[], int n) {
//     struct Process temp;
//     for(int i=0; i<n-1; i++) {
//         for(int j=0; j<n-i-1; j++) {
//             if(p[j].arrival_time > p[j+1].arrival_time) {
//                 temp = p[j];
//                 p[j] = p[j+1];
//                 p[j+1] = temp;
//             }
//         }
//     }
// }

// int main() {
//     int n = 4;
//     struct Process p[20];

//     printf("Enter burst time and arrival time for %d processes:\n", n);
//     for(int i=0; i<n; i++) {
//         p[i].pid = i+1;
//         printf("Process %d - Burst Time: ", i+1);
//         scanf("%d", &p[i].burst_time);
//         printf("Process %d - Arrival Time: ", i+1);
//         scanf("%d", &p[i].arrival_time);
//         p[i].completed = 0;
//     }

//     sort_by_arrival_time(p, n);

//     int current_time = 0, completed = 0;
//     float total_waiting_time = 0, total_turnaround_time = 0;

//     printf("\nGantt Chart:\n");
//     printf("--------------------------------------------------\n");

//     while(completed < n) {
//         int idx = -1;
//         int min_bt = 1e9;

//         for(int i=0; i<n; i++) {
//             if(p[i].arrival_time <= current_time && p[i].completed == 0) {
//                 if(p[i].burst_time < min_bt) {
//                     min_bt = p[i].burst_time;
//                     idx = i;
//                 }
//             }
//         }

//         if(idx != -1) {
//             p[idx].start_time = current_time;
//             p[idx].waiting_time = current_time - p[idx].arrival_time;
//             p[idx].turnaround_time = p[idx].waiting_time + p[idx].burst_time;

//             printf("| P%d (%d-%d) ", p[idx].pid, current_time, current_time + p[idx].burst_time);

//             current_time += p[idx].burst_time;
//             p[idx].completed = 1;
//             completed++;

//             total_waiting_time += p[idx].waiting_time;
//             total_turnaround_time += p[idx].turnaround_time;
//         } else {
//             current_time++; // CPU idle
//         }
//     }

//     printf("|\n--------------------------------------------------\n");

//     printf("\nPID\tAT\tBT\tWT\tTAT\n");
//     for(int i=0; i<n; i++) {
//         printf("%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].arrival_time, p[i].burst_time, p[i].waiting_time, p[i].turnaround_time);
//     }

//     printf("\nAverage Waiting Time: %.2f", total_waiting_time/n);
//     printf("\nAverage Turnaround Time: %.2f\n", total_turnaround_time/n);

//     return 0;
// }




// ass2

// Write a program in C or C++ to implement the non-primitive priority cpu scheduling algorithm. find the avg turn around time and waiting time.
// #include <iostream>
// #include <vector>
// #include <algorithm>
// using namespace std;

// struct Process {
//     int pid;
//     int arrival_time;
//     int burst_time;
//     int priority;
//     int waiting_time;
//     int turnaround_time;
//     int start_time;
//     bool completed = false;
// };

// int main() {
//     int n = 5;
//     vector<Process> processes(n);

//     cout << "Enter Arrival Time, Burst Time and Priority (Lower number = Higher priority):\n";
//     for(int i = 0; i < n; ++i) {
//         processes[i].pid = i + 1;
//         cout << "Process " << i+1 << ":\n";
//         cout << "Arrival Time: ";
//         cin >> processes[i].arrival_time;
//         cout << "Burst Time: ";
//         cin >> processes[i].burst_time;
//         cout << "Priority: ";
//         cin >> processes[i].priority;
//     }

//     int current_time = 0, completed = 0;
//     float total_wt = 0, total_tat = 0;

//     cout << "\nGantt Chart:\n";
//     cout << "--------------------------------------------------\n";

//     while(completed < n) {
//         int idx = -1;
//         int highest_priority = 1e9;

//         for(int i = 0; i < n; ++i) {
//             if(processes[i].arrival_time <= current_time && !processes[i].completed) {
//                 if(processes[i].priority < highest_priority) {
//                     highest_priority = processes[i].priority;
//                     idx = i;
//                 }
//             }
//         }

//         if(idx != -1) {
//             Process &p = processes[idx];
//             p.start_time = current_time;
//             p.waiting_time = current_time - p.arrival_time;
//             p.turnaround_time = p.waiting_time + p.burst_time;
//             current_time += p.burst_time;
//             p.completed = true;
//             completed++;

//             total_wt += p.waiting_time;
//             total_tat += p.turnaround_time;

//             cout << "| P" << p.pid << " (" << p.start_time << "-" << current_time << ") ";
//         } else {
//             current_time++; // CPU Idle
//         }
//     }

//     cout << "|\n--------------------------------------------------\n";
//     cout << "\nPID\tAT\tBT\tPri\tWT\tTAT\n";
//     for(auto &p : processes) {
//         cout << p.pid << "\t" << p.arrival_time << "\t" << p.burst_time << "\t"
//              << p.priority << "\t" << p.waiting_time << "\t" << p.turnaround_time << "\n";
//     }

//     cout << "\nAverage Waiting Time: " << total_wt / n;
//     cout << "\nAverage Turnaround Time: " << total_tat / n << "\n";

//     return 0;
// }





// 2) Write a program in C or C++ to implement the primitive sjf. find the avg tat, wt.
// #include <iostream>
// #include <vector>
// using namespace std;

// struct Process {
//     int pid;
//     int arrival_time;
//     int burst_time;
//     int remaining_time;
//     int completion_time;
//     int waiting_time;
//     int turnaround_time;
// };

// int main() {
//     int n = 3;
//     vector<Process> processes(n);

//     cout << "Enter Arrival Time and Burst Time:\n";
//     for(int i = 0; i < n; ++i) {
//         processes[i].pid = i+1;
//         cout << "Process " << i+1 << ":\n";
//         cout << "Arrival Time: ";
//         cin >> processes[i].arrival_time;
//         cout << "Burst Time: ";
//         cin >> processes[i].burst_time;
//         processes[i].remaining_time = processes[i].burst_time;
//     }

//     int completed = 0, current_time = 0;
//     float total_wt = 0, total_tat = 0;

//     cout << "\nGantt Chart:\n";
//     cout << "--------------------------------------------------\n";

//     while(completed < n) {
//         int idx = -1, min_rt = 1e9;
//         for(int i = 0; i < n; ++i) {
//             if(processes[i].arrival_time <= current_time && processes[i].remaining_time > 0) {
//                 if(processes[i].remaining_time < min_rt) {
//                     min_rt = processes[i].remaining_time;
//                     idx = i;
//                 }
//             }
//         }

//         if(idx != -1) {
//             processes[idx].remaining_time--;
//             cout << "|P" << processes[idx].pid << "(" << current_time << "-" << current_time+1 << ")";

//             if(processes[idx].remaining_time == 0) {
//                 completed++;
//                 processes[idx].completion_time = current_time + 1;
//                 processes[idx].turnaround_time = processes[idx].completion_time - processes[idx].arrival_time;
//                 processes[idx].waiting_time = processes[idx].turnaround_time - processes[idx].burst_time;

//                 total_wt += processes[idx].waiting_time;
//                 total_tat += processes[idx].turnaround_time;
//             }
//         } else {
//             cout << "|Idle(" << current_time << "-" << current_time+1 << ")";
//         }

//         current_time++;
//     }

//     cout << "|\n--------------------------------------------------\n";

//     cout << "\nPID\tAT\tBT\tCT\tWT\tTAT\n";
//     for(auto &p : processes) {
//         cout << p.pid << "\t" << p.arrival_time << "\t" << p.burst_time << "\t"
//              << p.completion_time << "\t" << p.waiting_time << "\t" << p.turnaround_time << "\n";
//     }

//     cout << "\nAverage Waiting Time: " << total_wt / n;
//     cout << "\nAverage Turnaround Time: " << total_tat / n << "\n";

//     return 0;
// }




// as3

// 1) Write a program in C or C++ to implement the primitive priority cpu scheduling algo. find the avg tat, wt.
// #include <bits/stdc++.h>
// using namespace std;

// struct GanttEntry {
//     int pid, start, end;
// };

// int main() {
//     int n;
//     cout << "Enter number of processes (>=10): ";
//     cin >> n;

//     vector<int> at(n), bt(n), rem_bt(n), pr(n);
//     for (int i = 0; i < n; i++) {
//         cout << "P" << i+1 << " Arrival Time, Burst Time, Priority: ";
//         cin >> at[i] >> bt[i] >> pr[i];
//         rem_bt[i] = bt[i];
//     }

//     vector<int> ct(n), tat(n), wt(n), preempt_count(n, 0);
//     vector<GanttEntry> gantt;
//     int completed = 0, time = 0, last_pid = -1;

//     while (completed < n) {
//         // Select highest-priority ready process
//         int idx = -1;
//         for (int i = 0; i < n; i++) {
//             if (rem_bt[i] > 0 && at[i] <= time) {
//                 if (idx == -1
//                     || pr[i] < pr[idx]
//                     || (pr[i] == pr[idx] && at[i] < at[idx])
//                     || (pr[i] == pr[idx] && at[i] == at[idx] && i < idx)) {
//                     idx = i;
//                 }
//             }
//         }

//         if (idx == -1) {
//             // CPU idle
//             time++;
//             continue;
//         }

//         // Preemption detection
//         if (last_pid != -1 && last_pid != idx && rem_bt[last_pid] > 0)
//             preempt_count[last_pid]++;

//         // Record Gantt
//         if (gantt.empty() || gantt.back().pid != idx) {
//             gantt.push_back({idx, time, time+1});
//         } else {
//             gantt.back().end++;
//         }

//         last_pid = idx;
//         // Execute one time unit
//         rem_bt[idx]--;
//         time++;

//         // If process completes
//         if (rem_bt[idx] == 0) {
//             completed++;
//             ct[idx]  = time;
//             tat[idx] = ct[idx] - at[idx];
//             wt[idx]  = tat[idx] - bt[idx];
//         }
//     }

//     // Display Gantt chart
//     cout << "\nGantt Chart:\n|";
//     for (auto &e : gantt) {
//         cout << " P" << e.pid+1 << " |";
//     }
//     cout << "\n0";
//     for (auto &e : gantt) {
//         cout << "\t" << e.end;
//     }
//     cout << "\n";

//     // Output table
//     double sumTAT = 0, sumWT = 0;
//     cout << "\nPID\tAT\tBT\tPR\tCT\tTAT\tWT\tPreemptions\n";
//     for (int i = 0; i < n; i++) {
//         cout << i+1 << "\t"
//              << at[i] << "\t"
//              << bt[i] << "\t"
//              << pr[i] << "\t"
//              << ct[i] << "\t"
//              << tat[i] << "\t"
//              << wt[i] << "\t"
//              << preempt_count[i] << "\n";
//         sumTAT += tat[i];
//         sumWT  += wt[i];
//     }

//     cout << fixed << setprecision(2)
//          << "\nAverage Turn-Around Time = " << (sumTAT / n) << "\n"
//          << "Average Waiting Time    = " << (sumWT  / n) << "\n";

//     return 0;
// }




// "Write a C++ function to implement Round Robin scheduling for a set of processes with a given time quantum."

// #include <iostream>
// #include <queue>
// #include <vector>
// #include <iomanip>
// #include <algorithm>

// using namespace std;

// struct Process {
//     int pid;            // Process ID
//     int arrival_time;   // Arrival Time
//     int burst_time;     // Burst Time
//     int remaining_time; // Remaining Burst Time
//     int completion_time;// Completion Time
//     int waiting_time;   // Waiting Time
//     int turnaround_time;// Turnaround Time
//     int preemptions;    // Number of Preemptions
//     int last_executed;  // Last time the process was executed
// };

// struct GanttChartEntry {
//     int pid;
//     int start_time;
//     int end_time;
// };

// void roundRobinScheduling(vector<Process>& processes, int time_quantum) {
//     int time = 0;
//     queue<int> ready_queue;
//     vector<GanttChartEntry> gantt_chart;
//     int n = processes.size();
//     int completed = 0;

//     // Sort processes by arrival time
//     sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
//         return a.arrival_time < b.arrival_time;
//     });

//     vector<bool> in_queue(n, false);
//     int index = 0;

//     // Add processes that have arrived at time 0
//     while (index < n && processes[index].arrival_time <= time) {
//         ready_queue.push(index);
//         in_queue[index] = true;
//         index++;
//     }

//     while (completed < n) {
//         if (ready_queue.empty()) {
//             // If no process is in the ready queue, advance time
//             time++;
//             while (index < n && processes[index].arrival_time <= time) {
//                 ready_queue.push(index);
//                 in_queue[index] = true;
//                 index++;
//             }
//             continue;
//         }

//         int current = ready_queue.front();
//         ready_queue.pop();

//         // Record start time for Gantt chart
//         int start_time = time;
//         int exec_time = min(time_quantum, processes[current].remaining_time);
//         time += exec_time;
//         processes[current].remaining_time -= exec_time;

//         // Record end time for Gantt chart
//         gantt_chart.push_back({processes[current].pid, start_time, time});

//         // If process is not finished, re-add to the ready queue
//         if (processes[current].remaining_time > 0) {
//             // Increment preemption count
//             processes[current].preemptions++;
//             // Add newly arrived processes to the ready queue
//             while (index < n && processes[index].arrival_time <= time) {
//                 ready_queue.push(index);
//                 in_queue[index] = true;
//                 index++;
//             }
//             ready_queue.push(current);
//         } else {
//             // Process has completed
//             processes[current].completion_time = time;
//             processes[current].turnaround_time = processes[current].completion_time - processes[current].arrival_time;
//             processes[current].waiting_time = processes[current].turnaround_time - processes[current].burst_time;
//             completed++;
//             // Add newly arrived processes to the ready queue
//             while (index < n && processes[index].arrival_time <= time) {
//                 ready_queue.push(index);
//                 in_queue[index] = true;
//                 index++;
//             }
//         }
//     }

//     // Display Gantt Chart
//     cout << "\nGantt Chart:\n";
//     for (const auto& entry : gantt_chart) {
//         cout << "| P" << entry.pid << " ";
//     }
//     cout << "|\n";
//     cout << gantt_chart.front().start_time;
//     for (const auto& entry : gantt_chart) {
//         cout << setw(5) << entry.end_time;
//     }
//     cout << "\n";

//     // Display process information
//     double total_tat = 0, total_wt = 0;
//     cout << "\nProcess\tAT\tBT\tCT\tTAT\tWT\tPreemptions\n";
//     for (const auto& p : processes) {
//         cout << "P" << p.pid << "\t" << p.arrival_time << "\t" << p.burst_time << "\t"
//              << p.completion_time << "\t" << p.turnaround_time << "\t"
//              << p.waiting_time << "\t" << p.preemptions << "\n";
//         total_tat += p.turnaround_time;
//         total_wt += p.waiting_time;
//     }

//     cout << fixed << setprecision(2);
//     cout << "\nAverage Turnaround Time: " << total_tat / n;
//     cout << "\nAverage Waiting Time: " << total_wt / n << "\n";
// }

// int main() {
//     int n, time_quantum;
//     cout << "Enter the number of processes: ";
//     cin >> n;

//     vector<Process> processes(n);

//     for (int i = 0; i < n; ++i) {
//         processes[i].pid = i + 1;
//         cout << "Enter Arrival Time and Burst Time for Process P" << i + 1 << ": ";
//         cin >> processes[i].arrival_time >> processes[i].burst_time;
//         processes[i].remaining_time = processes[i].burst_time;
//         processes[i].preemptions = 0;
//     }

//     cout << "Enter Time Quantum: ";
//     cin >> time_quantum;

//     roundRobinScheduling(processes, time_quantum);

//     return 0;
// }

// // Enter the number of processes: 6
// // Enter Arrival Time and Burst Time for Process P1: 0 4
// // Enter Arrival Time and Burst Time for Process P2: 1 5
// // Enter Arrival Time and Burst Time for Process P3: 2 3
// // Enter Arrival Time and Burst Time for Process P4: 3 6
// // Enter Arrival Time and Burst Time for Process P5: 4 2
// // Enter Arrival Time and Burst Time for Process P6: 5 1
// // Enter Time Quantum: 2




// Assignment 4
// 1) Write a program in C or C++ to implement the multilevel feedback queue cpu scheduling algo.find the avg tat,wt.
// #include <iostream>
// #include <queue>
// #include <vector>
// #include <algorithm>
// using namespace std;

// vector<pair<int, int>> gantt_chart;
// int currentTime = 0;
// int idx = 0;
// float totalTAT = 0, totalWT = 0;
// int newProcessCount = 1;

// struct Process
// {
//     int id, at, bt, remaning_bt, ct = 0, tat = 0, wt = 0, preemptions = 0;
// };

// bool comp(const Process &p1, const Process &p2)
// {
//     return p1.at < p2.at;
// }

// bool compid(const Process &p1, const Process &p2)
// {
//     return p1.id < p2.id;
// }

// void rrScheduling(vector<Process> &processes, queue<int> &rq, queue<int> &nq, int timeQuantum, int n)
// {
//     // Round Robin Scheduling logic
//     while (!rq.empty())
//     {
//         int i = rq.front() - 1;
//         rq.pop();
//         if (processes[i].remaning_bt >= timeQuantum)
//         {
//             processes[i].remaning_bt -= timeQuantum;
//             currentTime += timeQuantum;
//             gantt_chart.emplace_back(processes[i].id, currentTime);
//         }
//         else
//         {
//             currentTime += processes[i].remaning_bt;
//             processes[i].remaning_bt = 0;
//             gantt_chart.emplace_back(processes[i].id, currentTime);
//         }
//         // If the current process remaning_bt>0 push it to the nq
//         if (processes[i].remaning_bt > 0)
//         {
//             processes[i].preemptions++;
//             nq.push(processes[i].id);
//         }
//     }
// }

// int main()
// {
//     int n;
//     cout << "Enter number of processes: ";
//     cin >> n;
//     int timeQuantum1, timeQuantum2, timeQuantum3;
//     cout << "Enter the time Quantum: ";
//     cin >> timeQuantum1 >> timeQuantum2 >> timeQuantum3;
//     vector<Process> processes(n);
//     for (int i = 0; i < n; i++)
//     {
//         cout << "Enter Arrival Time and Burst Time for process " << i + 1 << ": ";
//         cin >> processes[i].at >> processes[i].bt;
//         processes[i].id = i + 1;
//         processes[i].remaning_bt = processes[i].bt;
//     }
//     sort(processes.begin(), processes.end(), comp);

//     queue<int> Q1, Q2, Q3, Q4;
//     for (int i = 0; i < n; i++)
//     {
//         Q1.push(processes[i].id);
//     }
    
//     rrScheduling(processes, Q1, Q2, timeQuantum1, n);  
//     rrScheduling(processes, Q2, Q3, timeQuantum2, n);
//     rrScheduling(processes, Q3, Q4, timeQuantum3, n);

//     // once these three rrScheduling runs we will be left with a Q4 containing the process that are still not completed
//     // now we have to just do a fcfs

//     while (!Q4.empty())
//     {
//         int i = Q4.front() - 1;
//         currentTime += processes[i].remaning_bt;
//         processes[i].remaning_bt = 0;
//         gantt_chart.emplace_back(processes[i].id, currentTime);
//         Q4.pop();
//     }

//     // Calculate completion time (CT)
//     int process = 1;
//     for (int i = gantt_chart.size() - 1; i >= 0; i--)
//     {
//         if (processes[gantt_chart[i].first - 1].ct == 0)
//         {
//             processes[gantt_chart[i].first - 1].ct = gantt_chart[i].second;
//             process++;
//         }
//         if (process > n)
//         {
//             break;
//         }
//     }

//     // sorted the processes again to bascially make the output look good
//     sort(processes.begin(), processes.end(), compid);

//     // Calculate turnaround time (TAT) and waiting time (WT)
//     for (int i = 0; i < n; i++)
//     {
//         processes[i].tat = processes[i].ct - processes[i].at;
//         totalTAT += processes[i].tat;
//         processes[i].wt = processes[i].tat - processes[i].bt;
//         totalWT += processes[i].wt;
    
//     }

//     // Print Gantt Chart
//     cout << "\nGantt Chart:\n";
//     cout << "--------------------------------------------------\n";
//     cout << "| Process |";
//     for (auto &entry : gantt_chart)
//     {
//         cout << " P" << entry.first << " |";
//     }
//     cout << "\n| Time    | 0 ";
//     for (auto &entry : gantt_chart)
//     {
//         cout << "\t" << entry.second;
//     }
//     cout << "\n--------------------------------------------------\n";

//     // Print process table with preemptions count
//     cout << "\nProcess Table:\n";
//     cout << "--------------------------------------------------\n";
//     cout << "| Ps | AT | BT | CT | TAT | WT | Preemptions |\n";
//     cout << "--------------------------------------------------\n";
//     for (int i = 0; i < n; i++)
//     {
//         cout << "| " << processes[i].id << " | " << processes[i].at << " | " << processes[i].bt << " | "
//              << processes[i].ct << " | " << processes[i].tat << " | " << processes[i].wt << " | " << processes[i].preemptions << " |\n";
//     }
//     cout << "--------------------------------------------------\n";

//     cout << "\nAverage Turnaround Time: " << totalTAT / n;
//     cout << "\nAverage Waiting Time: " << totalWT / n << endl;
//     return 0;
// }










// Assignment 5
// 1) Write a program in C or C++ to implement the multilevel queue cpu scheduling having 5 queues system interactive editing, batch and student processes from high priority to low.
// find the avg tat,wt. count the no of premption takes place during the arrival of a low priority process.

// #include <iostream>
// #include <vector>
// #include <queue>
// #include <algorithm>

// using namespace std;

// struct Process {
//     int id;
//     int arrival;
//     int burst;
//     int remaining;
//     int priority;
//     int start = -1;
//     int finish = 0;
//     int waiting = 0;
//     int turnaround = 0;
//     bool completed = false;
// };

// bool arrivalSort(const Process &a, const Process &b) {
//     return a.arrival < b.arrival;
// }

// int main() {
//     int n;
//     cout << "Enter number of processes: ";
//     cin >> n;

//     vector<Process> processes(n);
//     for (int i = 0; i < n; i++) {
//         cout << "\nProcess " << i + 1 << ":\n";
//         processes[i].id = i + 1;
//         cout << "Arrival Time: ";
//         cin >> processes[i].arrival;
//         cout << "Burst Time: ";
//         cin >> processes[i].burst;
//         processes[i].remaining = processes[i].burst;
//         cout << "Queue (1-5) [1=High, 5=Low]: ";
//         cin >> processes[i].priority;
//     }

//     sort(processes.begin(), processes.end(), arrivalSort);

//     vector<queue<Process*>> queues(5);
//     int time = 0, completed = 0, preemptions = 0;
//     Process* current = nullptr;

//     while (completed < n) {
//         // Push newly arrived processes into their queues
//         for (auto &p : processes) {
//             if (p.arrival == time) {
//                 queues[p.priority - 1].push(&p);
//             }
//         }

//         // Check if a higher-priority process is now available
//         for (int i = 0; i < 5; i++) {
//             if (!queues[i].empty()) {
//                 if (current == nullptr || current->priority > i + 1) {
//                     if (current != nullptr && current->remaining > 0) {
//                         // Preempt current process
//                         queues[current->priority - 1].push(current);
//                         preemptions++;
//                     }
//                     current = queues[i].front();
//                     queues[i].pop();
//                 }
//                 break;
//             }
//         }

//         if (current != nullptr) {
//             if (current->start == -1)
//                 current->start = time;

//             current->remaining--;

//             if (current->remaining == 0) {
//                 current->finish = time + 1;
//                 current->turnaround = current->finish - current->arrival;
//                 current->waiting = current->turnaround - current->burst;
//                 current->completed = true;
//                 completed++;
//                 current = nullptr;
//             }
//         }

//         time++;
//     }

//     // Output
//     double totalTAT = 0, totalWT = 0;
//     cout << "\nID\tArrival\tBurst\tQueue\tTAT\tWT\n";
//     for (auto &p : processes) {
//         totalTAT += p.turnaround;
//         totalWT += p.waiting;
//         cout << p.id << "\t" << p.arrival << "\t" << p.burst << "\t"
//              << p.priority << "\t" << p.turnaround << "\t" << p.waiting << endl;
//     }

//     cout << "\nAverage Turnaround Time: " << totalTAT / n;
//     cout << "\nAverage Waiting Time: " << totalWT / n;
//     cout << "\nPreemptions (due to lower-priority arrival): " << preemptions << endl;

//     return 0;
// }







// Assignment 6
// 1. Write a program in C to demonstrate the creation and termination of the child process. Your program must include a series of system calls to create new child processes and each child process must do the same function or task. Check if the series contains "n" System calls, then 
// your program creates how many child processes and how many times the common task will be executed.   

// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>
// #include <sys/wait.h>

// // Common task for all child processes
// void common_task() {
//     printf("Child process (PID: %d) is executing the common task.\n", getpid());
// }

// int main() {
//     int n; // number of fork system calls
//     printf("Enter the number of fork system calls (n): ");
//     scanf("%d", &n);

//     int total_forks = n;
//     int i;
//     for (i = 0; i < total_forks; i++) {
//         pid_t pid = fork();
//         if (pid < 0) {
//             perror("fork failed");
//             exit(1);
//         } else if (pid == 0) {
//             // Child process
//             common_task();
//             exit(0); // Important to prevent child from creating more children
//         }
//         // Parent process waits for the child
//         wait(NULL);
//     }

//     printf("Main process (PID: %d) completed.\n", getpid());

//     return 0;
// }





// . Write a program in C to demonstrate how two child processes of a program execute for different tasks, like one finding factorization of an integer and another finding the greatest common divisors between two numbers. Give your comment regarding execution of child processes. 


// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>
// #include <sys/wait.h>

// // Function to factorize an integer
// void factorize(int num) {
//     printf("Factorization of %d: ", num);
//     for (int i = 1; i <= num; i++) {
//         if (num % i == 0) {
//             printf("%d ", i);
//         }
//     }
//     printf("\n");
// }

// // Function to calculate GCD of two integers
// int gcd(int a, int b) {
//     while (b != 0) {
//         int temp = b;
//         b = a % b;
//         a = temp;
//     }
//     return a;
// }

// int main() {
//     pid_t pid1, pid2;

//     pid1 = fork();
//     if (pid1 < 0) {
//         perror("fork failed");
//         exit(1);
//     } else if (pid1 == 0) {
//         // First child process: factorization
//         printf("Child 1 (PID: %d): ", getpid());
//         factorize(28);
//         exit(0);
//     } else {
//         pid2 = fork();
//         if (pid2 < 0) {
//             perror("fork failed");
//             exit(1);
//         } else if (pid2 == 0) {
//             // Second child process: GCD
//             int a = 60, b = 48;
//             printf("Child 2 (PID: %d): GCD of %d and %d is %d\n", getpid(), a, b, gcd(a, b));
//             exit(0);
//         } else {
//             // Parent process waits for both children
//             wait(NULL);
//             wait(NULL);
//             printf("Parent (PID: %d): Both child processes completed.\n", getpid());
//         }
//     }

//     return 0;
// }



// Assignment 7
// 1. Write a program to implement Deadlock Prevention Using Banker’s Algorithm.
// #include <stdio.h>

// #define MAX_PROCESSES 10
// #define MAX_RESOURCES 10

// int main() {
//     int n, m, i, j, k;
//     int alloc[MAX_PROCESSES][MAX_RESOURCES];
//     int max[MAX_PROCESSES][MAX_RESOURCES];
//     int need[MAX_PROCESSES][MAX_RESOURCES];
//     int avail[MAX_RESOURCES];
//     int finish[MAX_PROCESSES];
//     int safe_seq[MAX_PROCESSES];

//     // Input number of processes and resources
//     printf("Enter the number of processes: ");
//     scanf("%d", &n);
//     printf("Enter the number of resource types: ");
//     scanf("%d", &m);

//     // Input Allocation matrix
//     printf("Enter Allocation Matrix (%d x %d):\n", n, m);
//     for (i = 0; i < n; i++)
//         for (j = 0; j < m; j++)
//             scanf("%d", &alloc[i][j]);

//     // Input Max matrix
//     printf("Enter Max Matrix (%d x %d):\n", n, m);
//     for (i = 0; i < n; i++)
//         for (j = 0; j < m; j++)
//             scanf("%d", &max[i][j]);

//     // Input Available vector
//     printf("Enter Available Resources (length %d):\n", m);
//     for (i = 0; i < m; i++)
//         scanf("%d", &avail[i]);

//     // Calculate Need matrix
//     for (i = 0; i < n; i++)
//         for (j = 0; j < m; j++)
//             need[i][j] = max[i][j] - alloc[i][j];

//     // Initialize Finish flags
//     for (i = 0; i < n; i++)
//         finish[i] = 0;

//     // Safety algorithm
//     int count = 0;
//     while (count < n) {
//         int found = 0;
//         for (i = 0; i < n; i++) {
//             if (!finish[i]) {
//                 // Check if need[i] <= avail
//                 for (j = 0; j < m; j++)
//                     if (need[i][j] > avail[j])
//                         break;
//                 if (j == m) {
//                     // Simulate allocation
//                     for (k = 0; k < m; k++)
//                         avail[k] += alloc[i][k];
//                     safe_seq[count++] = i;
//                     finish[i] = 1;
//                     found = 1;
//                 }
//             }
//         }
//         if (!found) {
//             printf("System is NOT in a safe state.\n");
//             return 0;
//         }
//     }

//     // If here, system is safe
//     printf("System is in a safe state.\nSafe sequence is: ");
//     for (i = 0; i < n; i++)
//         printf("P%d ", safe_seq[i]);
//     printf("\n");
//     return 0;
// }
// // Enter the number of processes: 5
// // Enter the number of resource types: 3
// // Enter Allocation Matrix:
// // 0 1 0
// // 2 0 0
// // 3 0 2
// // 2 1 1
// // 0 0 2
// // Enter Max Matrix:
// // 7 5 3
// // 3 2 2
// // 9 0 2
// // 2 2 2
// // 4 3 3
// // Enter Available Resources:
// // 3 3 2
// // System is in a safe state.
// // Safe sequence is: P1 P3 P4 P0 P2 






// 2 .Implement Resource Allocation Without Hold and Wait:
// Write a C/C++ program that ensures a process gets all required resources at once before execution, preventing the Hold and Wait condition.
// #include <stdio.h>
// #include <stdbool.h>

// #define MAX_PROCESSES 10
// #define MAX_RESOURCES 10

// int main() {
//     int n, m; // number of processes and resource types
//     int max[MAX_PROCESSES][MAX_RESOURCES]; // max resource need
//     int alloc[MAX_PROCESSES][MAX_RESOURCES] = {0}; // resources currently allocated
//     int avail[MAX_RESOURCES]; // available resources
//     bool finished[MAX_PROCESSES] = {false};

//     printf("Enter number of processes: ");
//     scanf("%d", &n);
//     printf("Enter number of resource types: ");
//     scanf("%d", &m);

//     printf("Enter Available Resources (space-separated):\n");
//     for (int i = 0; i < m; i++) {
//         scanf("%d", &avail[i]);
//     }

//     printf("Enter Max resource requirement matrix (%d x %d):\n", n, m);
//     for (int i = 0; i < n; i++) {
//         printf("Process P%d: ", i);
//         for (int j = 0; j < m; j++) {
//             scanf("%d", &max[i][j]);
//         }
//     }

//     printf("\n--- Resource Allocation Begins ---\n");

//     int completed = 0;
//     while (completed < n) {
//         bool allocated_this_round = false;

//         for (int i = 0; i < n; i++) {
//             if (!finished[i]) {
//                 bool can_allocate = true;

//                 for (int j = 0; j < m; j++) {
//                     if (max[i][j] > avail[j]) {
//                         can_allocate = false;
//                         break;
//                     }
//                 }

//                 if (can_allocate) {
//                     printf("Process P%d is allocated resources: ", i);
//                     for (int j = 0; j < m; j++) {
//                         avail[j] -= max[i][j];
//                         alloc[i][j] = max[i][j];
//                         printf("%d ", alloc[i][j]);
//                     }
//                     printf("\nProcess P%d is executing...\n", i);

//                     // Simulate execution and resource release
//                     for (int j = 0; j < m; j++) {
//                         avail[j] += alloc[i][j];
//                         alloc[i][j] = 0;
//                     }

//                     printf("Process P%d has finished and released resources.\n\n", i);
//                     finished[i] = true;
//                     completed++;
//                     allocated_this_round = true;
//                 }
//             }
//         }

//         if (!allocated_this_round) {
//             printf("No further allocation possible. System might be in unsafe state.\n");
//             break;
//         }
//     }

//     if (completed == n) {
//         printf("All processes executed without Hold and Wait. System is safe.\n");
//     }

//     return 0;
// }

// // Enter number of processes: 3
// // Enter number of resource types: 2
// // Enter Available Resources:
// // 3 3
// // Enter Max resource requirement matrix:
// // Process P0: 1 2
// // Process P1: 2 1
// // Process P2: 3 3



// 3. Resource Allocation with Priority-based Lock Ordering:
// Implement a program that assigns priority to resources and forces processes to request resources in a strict order, preventing Circular Wait.
// #include <stdio.h>
// #include <stdlib.h>
// #include <pthread.h>

// // Number of distinct resources
// #define NUM_RESOURCES 3

// // Global array of mutexes representing resources R0, R1, R2...
// pthread_mutex_t resource_mutex[NUM_RESOURCES];

// // Structure to pass to each thread
// typedef struct {
//     int thread_id;
//     int needed_resources[NUM_RESOURCES];
//     int count;
// } thread_info_t;

// // Comparator for qsort: ascending order
// int cmp_int(const void *a, const void *b) {
//     return (*(int*)a - *(int*)b);  // Dereference the pointers
// }

// void* thread_func(void* arg) {
//     thread_info_t *info = (thread_info_t*)arg;  // Cast to pointer to struct

//     // Sort resource IDs to enforce ascending lock order
//     qsort(info->needed_resources, info->count, sizeof(int), cmp_int);

//     printf("Thread %d requesting resources:", info->thread_id);
//     for (int i = 0; i < info->count; i++) {
//         printf(" R%d", info->needed_resources[i]);
//     }
//     printf("\n");

//     // Acquire locks in ascending order
//     for (int i = 0; i < info->count; i++) {
//         int r = info->needed_resources[i];
//         pthread_mutex_lock(&resource_mutex[r]);
//         printf("Thread %d acquired R%d\n", info->thread_id, r);
//     }

//     // --- Critical section simulating work ---
//     printf("Thread %d in critical section\n", info->thread_id);

//     // Release locks in reverse order
//     for (int i = info->count - 1; i >= 0; i--) {
//         int r = info->needed_resources[i];
//         pthread_mutex_unlock(&resource_mutex[r]);
//         printf("Thread %d released R%d\n", info->thread_id, r);
//     }

//     return NULL;
// }

// int main() {
//     pthread_t threads[2];
//     thread_info_t infos[2] = {
//         { .thread_id = 1, .needed_resources = {2, 0}, .count = 2 },
//         { .thread_id = 2, .needed_resources = {1, 0}, .count = 2 }
//     };

//     // Initialize all resource mutexes
//     for (int i = 0; i < NUM_RESOURCES; i++) {
//         pthread_mutex_init(&resource_mutex[i], NULL);
//     }

//     // Create threads
//     for (int i = 0; i < 2; i++) {
//         pthread_create(&threads[i], NULL, thread_func, &infos[i]);
//     }

//     // Wait for threads to finish
//     for (int i = 0; i < 2; i++) {
//         pthread_join(threads[i], NULL);
//     }

//     // Destroy mutexes
//     for (int i = 0; i < NUM_RESOURCES; i++) {
//         pthread_mutex_destroy(&resource_mutex[i]);
//     }

//     printf("All threads completed without deadlock.\n");
//     return 0;
// }




// 4.Preemptive Resource Allocation (No Preemption Rule):
// Create a C/C++ program where if a process is holding resources and another higher-priority process requests them, they are forcibly released.

// #include <stdio.h>
// #include <stdbool.h>

// #define MAX_PROCESSES 10
// #define MAX_RESOURCES 10

// int main() {
//     int n, m, i, j, p;

//     // Data structures
//     int priority[MAX_PROCESSES];
//     int max[MAX_PROCESSES][MAX_RESOURCES];
//     int alloc[MAX_PROCESSES][MAX_RESOURCES] = {0};
//     int avail[MAX_RESOURCES];
//     bool waiting[MAX_PROCESSES] = {false};

//     // Input counts
//     printf("Enter number of processes: ");
//     scanf("%d", &n);
//     printf("Enter number of resource types: ");
//     scanf("%d", &m);

//     // Input priorities (0 = highest)
//     printf("Enter priorities for each process (0 = highest):\n");
//     for (i = 0; i < n; i++) {
//         printf("P%d priority: ", i);
//         scanf("%d", &priority[i]);
//     }

//     // Input max requirement matrix
//     printf("Enter Max requirement matrix (%dx%d):\n", n, m);
//     for (i = 0; i < n; i++)
//         for (j = 0; j < m; j++)
//             scanf("%d", &max[i][j]);

//     // Input available resources
//     printf("Enter Available resources (length %d):\n", m);
//     for (j = 0; j < m; j++)
//         scanf("%d", &avail[j]);

//     // Process requests until user quits
//     while (true) {
//         printf("\nEnter process number making a request (or -1 to exit): ");
//         scanf("%d", &p);
//         if (p < 0 || p >= n) break;

//         int req[MAX_RESOURCES];
//         printf("Enter request vector for P%d:\n", p);
//         for (j = 0; j < m; j++)
//             scanf("%d", &req[j]);

//         // Check if request ≤ max – alloc
//         bool legal = true;
//         for (j = 0; j < m; j++) {
//             if (req[j] + alloc[p][j] > max[p][j]) {
//                 legal = false;
//                 break;
//             }
//         }
//         if (!legal) {
//             printf("Error: request exceeds declared maximum.\n");
//             continue;
//         }

//         // Can we allocate directly?
//         bool direct = true;
//         for (j = 0; j < m; j++) {
//             if (req[j] > avail[j]) {
//                 direct = false;
//                 break;
//             }
//         }

//         if (!direct) {
//             // Preempt all lower‑priority processes
//             for (i = 0; i < n; i++) {
//                 if (!waiting[i] && priority[i] > priority[p]) {
//                     printf("Preempting P%d (lower priority %d > %d)\n",
//                            i, priority[i], priority[p]);
//                     for (j = 0; j < m; j++) {
//                         avail[j] += alloc[i][j];
//                         alloc[i][j] = 0;
//                     }
//                     waiting[i] = true;
//                 }
//             }
//         }

//         // Now allocate
//         bool ok = true;
//         for (j = 0; j < m; j++) {
//             if (req[j] > avail[j]) ok = false;
//         }
//         if (!ok) {
//             printf("Still insufficient resources after preemption. P%d must wait.\n", p);
//             waiting[p] = true;
//         } else {
//             for (j = 0; j < m; j++) {
//                 avail[j] -= req[j];
//                 alloc[p][j] += req[j];
//             }
//             waiting[p] = false;
//             printf("Allocated to P%d. Available now: ", p);
//             for (j = 0; j < m; j++) printf("%d ", avail[j]);
//             printf("\n");
//         }
//     }

//     printf("Exiting.\n");
//     return 0;
// }

// // Enter number of processes: 3
// // Enter number of resource types: 2

// // Enter priorities for each process (0 = highest):
// // P0 priority: 1
// // P1 priority: 0
// // P2 priority: 2

// // Enter Max requirement matrix (3x2):
// // P0: 0 2
// // P1: 1 1
// // P2: 2 2

// // Enter Available resources (length 2):
// // 1 1

// // --- Begin requests ---

// // Enter process number making a request (or -1 to exit): 2
// // Enter request vector for P2:
// // 1 0
// // Allocated to P2. Available now: 0 1

// // Enter process number making a request (or -1 to exit): 0
// // Enter request vector for P0:
// // 0 1
// // Allocated to P0. Available now: 0 0

// // Enter process number making a request (or -1 to exit): 1
// // Enter request vector for P1:
// // 1 1
// // Preempting P0 (lower priority 1 > 0)
// // Preempting P2 (lower priority 2 > 0)
// // Allocated to P1. Available now: 0 0

// // Enter process number making a request (or -1 to exit): -1
// // Exiting.




// 5.Mutex Lock Ordering (Preventing Circular Wait):
// Implement a multithreaded program where two threads try to acquire locks in a fixed order to avoid deadlock.
// #include <stdio.h>
// #include <stdlib.h>
// #include <pthread.h>
// #include <stdint.h>  // For intptr_t

// pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
// pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;

// void* thread_func(void* arg) {
//     int id = (int)(intptr_t)arg;  // Safe casting from void* to int
//     // Acquire locks in fixed order
//     pthread_mutex_lock(&mutex1);
//     printf("Thread %d acquired mutex1\n", id);

//     pthread_mutex_lock(&mutex2);
//     printf("Thread %d acquired mutex2\n", id);

//     // Critical section
//     printf("Thread %d in critical section\n", id);

//     // Release locks in reverse order
//     pthread_mutex_unlock(&mutex2);
//     printf("Thread %d released mutex2\n", id);

//     pthread_mutex_unlock(&mutex1);
//     printf("Thread %d released mutex1\n", id);

//     return NULL;
// }

// int main() {
//     pthread_t t1, t2;
//     int id1 = 1, id2 = 2;

//     // Create threads and pass IDs safely
//     pthread_create(&t1, NULL, thread_func, (void*)(intptr_t)id1);
//     pthread_create(&t2, NULL, thread_func, (void*)(intptr_t)id2);

//     // Wait for threads to complete
//     pthread_join(t1, NULL);
//     pthread_join(t2, NULL);

//     return 0;
// }












// Assignment 8
// 1 Implementation and stimulation of MFT(multiple fixed partition algorithm) algorithms.
// //Q1: C Program to Implement and Simulate MFT (Multiple Fixed Partitioning)
// #include <stdio.h>

// #define MAX 10

// int main() {
//     int partitionSize[10], memorySize, blockCount, processCount;
//     int processSize[10], allocation[10];
    
//     printf("Enter the total memory size: ");
//     scanf("%d", &memorySize);

//     printf("Enter the number of partitions: ");
//     scanf("%d", &blockCount);

//     int blockSize = memorySize / blockCount;

//     for (int i = 0; i < blockCount; i++) {
//         partitionSize[i] = blockSize;
//     }

//     printf("Fixed Partition Size = %d\n", blockSize);

//     printf("Enter number of processes: ");
//     scanf("%d", &processCount);

//     printf("Enter size of each process:\n");
//     for (int i = 0; i < processCount; i++) {
//         printf("Process %d: ", i + 1);
//         scanf("%d", &processSize[i]);
//         allocation[i] = -1;
//     }

//     // Allocation
//     for (int i = 0; i < processCount; i++) {
//         for (int j = 0; j < blockCount; j++) {
//             if (partitionSize[j] >= processSize[i]) {
//                 allocation[i] = j;
//                 partitionSize[j] = -1; // Mark partition as used
//                 break;
//             }
//         }
//     }

//     // Output
//     printf("\nProcess No\tProcess Size\tPartition Allocated\n");
//     for (int i = 0; i < processCount; i++) {
//         printf("%d\t\t%d\t\t", i + 1, processSize[i]);
//         if (allocation[i] != -1)
//             printf("%d\n", allocation[i] + 1);
//         else
//             printf("Not Allocated\n");
//     }

//     return 0;
// }




// 2.  Implementation and stimulation of MVT(multiple variable partition algorithm) algorithms.
// //Q2: C Program to Implement and Simulate MVT (Multiple Variable Partitioning)

// #include <stdio.h>

// int main() {
//     int memSize, remainingMem, processSize, processCount = 0, choice;

//     printf("Enter total memory size: ");
//     scanf("%d", &memSize);

//     remainingMem = memSize;

//     do {
//         printf("\nEnter size of process %d: ", processCount + 1);
//         scanf("%d", &processSize);

//         if (processSize <= remainingMem) {
//             printf("Process %d is allocated.\n", processCount + 1);
//             remainingMem -= processSize;
//             processCount++;
//         } else {
//             printf("Not enough memory to allocate the process!\n");
//         }

//         printf("Do you want to add more processes? (1: Yes / 0: No): ");
//         scanf("%d", &choice);
//     } while (choice == 1);

//     printf("\nTotal Processes Allocated: %d\n", processCount);
//     printf("Remaining Memory: %d\n", remainingMem);

//     return 0;
// }





// 3.  Stimulation of contiguous memory allocation techniques .
// C code for worst-fit, best-fit and first-fit allocaition
// // Assignment 8 - Q3: C Program for First Fit, Best Fit, and Worst Fit Allocation

// #include <stdio.h>
// #include <string.h>

// #define MAX 25

// void firstFit(int blockSize[], int blocks, int processSize[], int processes);
// void bestFit(int blockSize[], int blocks, int processSize[], int processes);
// void worstFit(int blockSize[], int blocks, int processSize[], int processes);

// int main() {
//     int blockSize[MAX], processSize[MAX];
//     int blocks, processes, choice;

//     printf("Enter number of memory blocks: ");
//     scanf("%d", &blocks);

//     printf("Enter size of each block:\n");
//     for (int i = 0; i < blocks; i++) {
//         printf("Block %d: ", i + 1);
//         scanf("%d", &blockSize[i]);
//     }

//     printf("Enter number of processes: ");
//     scanf("%d", &processes);

//     printf("Enter size of each process:\n");
//     for (int i = 0; i < processes; i++) {
//         printf("Process %d: ", i + 1);
//         scanf("%d", &processSize[i]);
//     }

//     do {
//         int tempBlock[MAX];
//         memcpy(tempBlock, blockSize, blocks * sizeof(int)); // Reset block sizes

//         printf("\nChoose Allocation Strategy:\n");
//         printf("1. First Fit\n2. Best Fit\n3. Worst Fit\n4. Exit\n");
//         printf("Enter your choice: ");
//         scanf("%d", &choice);

//         switch (choice) {
//             case 1:
//                 firstFit(tempBlock, blocks, processSize, processes);
//                 break;
//             case 2:
//                 bestFit(tempBlock, blocks, processSize, processes);
//                 break;
//             case 3:
//                 worstFit(tempBlock, blocks, processSize, processes);
//                 break;
//             case 4:
//                 printf("Exiting...\n");
//                 break;
//             default:
//                 printf("Invalid choice!\n");
//         }
//     } while (choice != 4);

//     return 0;
// }

// // First Fit
// void firstFit(int blockSize[], int blocks, int processSize[], int processes) {
//     int allocation[MAX];
//     memset(allocation, -1, sizeof(allocation));

//     for (int i = 0; i < processes; i++) {
//         for (int j = 0; j < blocks; j++) {
//             if (blockSize[j] >= processSize[i]) {
//                 allocation[i] = j;
//                 blockSize[j] -= processSize[i];
//                 break;
//             }
//         }
//     }

//     printf("\nFirst Fit Allocation:\n");
//     printf("Process No.\tProcess Size\tBlock Allocated\n");
//     for (int i = 0; i < processes; i++) {
//         printf("%d\t\t%d\t\t", i + 1, processSize[i]);
//         if (allocation[i] != -1)
//             printf("%d\n", allocation[i] + 1);
//         else
//             printf("Not Allocated\n");
//     }
// }

// // Best Fit
// void bestFit(int blockSize[], int blocks, int processSize[], int processes) {
//     int allocation[MAX];
//     memset(allocation, -1, sizeof(allocation));

//     for (int i = 0; i < processes; i++) {
//         int bestIdx = -1;
//         for (int j = 0; j < blocks; j++) {
//             if (blockSize[j] >= processSize[i]) {
//                 if (bestIdx == -1 || blockSize[j] < blockSize[bestIdx])
//                     bestIdx = j;
//             }
//         }
//         if (bestIdx != -1) {
//             allocation[i] = bestIdx;
//             blockSize[bestIdx] -= processSize[i];
//         }
//     }

//     printf("\nBest Fit Allocation:\n");
//     printf("Process No.\tProcess Size\tBlock Allocated\n");
//     for (int i = 0; i < processes; i++) {
//         printf("%d\t\t%d\t\t", i + 1, processSize[i]);
//         if (allocation[i] != -1)
//             printf("%d\n", allocation[i] + 1);
//         else
//             printf("Not Allocated\n");
//     }
// }

// // Worst Fit
// void worstFit(int blockSize[], int blocks, int processSize[], int processes) {
//     int allocation[MAX];
//     memset(allocation, -1, sizeof(allocation));

//     for (int i = 0; i < processes; i++) {
//         int worstIdx = -1;
//         for (int j = 0; j < blocks; j++) {
//             if (blockSize[j] >= processSize[i]) {
//                 if (worstIdx == -1 || blockSize[j] > blockSize[worstIdx])
//                     worstIdx = j;
//             }
//         }
//         if (worstIdx != -1) {
//             allocation[i] = worstIdx;
//             blockSize[worstIdx] -= processSize[i];
//         }
//     }

//     printf("\nWorst Fit Allocation:\n");
//     printf("Process No.\tProcess Size\tBlock Allocated\n");
//     for (int i = 0; i < processes; i++) {
//         printf("%d\t\t%d\t\t", i + 1, processSize[i]);
//         if (allocation[i] != -1)
//             printf("%d\n", allocation[i] + 1);
//         else
//             printf("Not Allocated\n");
//     }
// }










// Assignment 9
// 1. wap to implement the fifo page replacement algo
// // Q1: FIFO Page Replacement in C
// #include <stdio.h>
// int main() {
//     // Declare variables
//     int pages[50], frames[10]; 
//     // pages[] stores page reference string; frames[] stores memory frames
//     int n, f, i, j, k, flag, pageFaults = 0;

//     // Input number of pages in the reference string
//     printf("Enter number of pages: ");
//     scanf("%d", &n);

//     // Input the page reference string
//     printf("Enter the page reference string:\n");
//     for (i = 0; i < n; i++)
//         scanf("%d", &pages[i]);

//     // Input number of available frames
//     printf("Enter number of frames: ");
//     scanf("%d", &f);

//     // Initialize all frames to -1 (indicating empty)
//     for (i = 0; i < f; i++)
//         frames[i] = -1;

//     int pos = 0; // Tracks the position to insert the next page (FIFO queue)

//     printf("\nPage\tFrames\n");

//     // Loop over each page in the reference string
//     for (i = 0; i < n; i++) {
//         flag = 0; // Used to check if the current page is already in a frame

//         // Check if the current page is already in one of the frames
//         for (j = 0; j < f; j++) {
//             if (frames[j] == pages[i]) {
//                 flag = 1; // Page is already in memory, no page fault
//                 break;
//             }
//         }

//         // If page is not in any frame => page fault
//         if (!flag) {
//             frames[pos] = pages[i];           // Replace the page at the current position (FIFO)
//             pos = (pos + 1) % f;              // Move to the next position in a circular manner
//             pageFaults++;                     // Increase the page fault count

//             // Print the current state of the frames
//             printf("%d\t", pages[i]);
//             for (k = 0; k < f; k++) {
//                 if (frames[k] != -1)
//                     printf("%d ", frames[k]); // Print page number in frame
//                 else
//                     printf("- ");             // Frame is still empty
//             }
//             printf("\n");
//         }
//         // If page is found in frame, we do nothing (no replacement)
//     }

//     // Print the total number of page faults
//     printf("\nTotal Page Faults = %d\n", pageFaults);
//     return 0;
// }








// 2. wap in c to implement optimal page replacement algo.
// //Q2: Optimal Page Replacement in C
// #include <stdio.h>

// int findOptimal(int pages[], int frames[], int n, int index, int f) {
//     int farthest = index, result = -1;
//     for (int i = 0; i < f; i++) {
//         int j;
//         for (j = index; j < n; j++) {
//             if (frames[i] == pages[j]) {
//                 if (j > farthest) {
//                     farthest = j;
//                     result = i;
//                 }
//                 break;
//             }
//         }
//         if (j == n)
//             return i; // If a frame is never used again, replace it
//     }

//     return (result == -1) ? 0 : result;
// }

// int main() {
//     int n, f, i, j, pageFaults = 0;
//     int pages[100], frames[10];

//     printf("Enter number of pages: ");
//     scanf("%d", &n);
//     printf("Enter the page reference string:\n");
//     for (i = 0; i < n; i++)
//         scanf("%d", &pages[i]);

//     printf("Enter number of frames: ");
//     scanf("%d", &f);

//     for (i = 0; i < f; i++)
//         frames[i] = -1;

//     printf("\nPage\tFrames\n");

//     for (i = 0; i < n; i++) {
//         int flag = 0;

//         // Check if page is already present
//         for (j = 0; j < f; j++) {
//             if (frames[j] == pages[i]) {
//                 flag = 1;
//                 break;
//             }
//         }

//         // Page fault
//         if (!flag) {
//             int replaced = -1;

//             // Check for empty frame
//             for (j = 0; j < f; j++) {
//                 if (frames[j] == -1) {
//                     frames[j] = pages[i];
//                     replaced = j;
//                     break;
//                 }
//             }

//             if (replaced == -1) {
//                 int index = findOptimal(pages, frames, n, i + 1, f);
//                 frames[index] = pages[i];
//             }

//             pageFaults++;

//             // Print frame content
//             printf("%d\t", pages[i]);
//             for (j = 0; j < f; j++) {
//                 if (frames[j] != -1)
//                     printf("%d ", frames[j]);
//                 else
//                     printf("- ");
//             }
//             printf("\n");
//         }
//     }

//     printf("\nTotal Page Faults = %d\n", pageFaults);
//     return 0;
// }




// 3. wap to implement lru page replacement algo.
// // Q3: LRU Page Replacement in C
// #include <stdio.h>

// // Function to find the Least Recently Used (LRU) frame based on time[]
// int findLRU(int time[], int n) {
//     int min = time[0], pos = 0;
//     for (int i = 1; i < n; i++) {
//         if (time[i] < min) {
//             min = time[i];  // find the smallest time value
//             pos = i;        // position of the least recently used page
//         }
//     }
//     return pos;  // return position to replace
// }

// int main() {
//     int n, f, i, j, pageFaults = 0;
//     int time[10], counter = 0;     // time[] stores last used time for each frame
//     int pages[100], frames[10];    // pages[] is the reference string, frames[] is memory

//     // Input: Number of pages
//     printf("Enter number of pages: ");
//     scanf("%d", &n);

//     // Input: Page reference string
//     printf("Enter the page reference string:\n");
//     for (i = 0; i < n; i++)
//         scanf("%d", &pages[i]);

//     // Input: Number of frames
//     printf("Enter number of frames: ");
//     scanf("%d", &f);

//     // Initialize all frames and their times to -1 and 0
//     for (i = 0; i < f; i++) {
//         frames[i] = -1;  // frame is initially empty
//         time[i] = 0;     // last used time
//     }

//     printf("\nPage\tFrames\n");

//     // Iterate over each page in the reference string
//     for (i = 0; i < n; i++) {
//         int flag = 0;  // flag to check if page hit

//         // Check if page is already present (page hit)
//         for (j = 0; j < f; j++) {
//             if (frames[j] == pages[i]) {
//                 flag = 1;             // page hit
//                 time[j] = ++counter;  // update time of this frame
//                 break;
//             }
//         }

//         // Page fault occurs
//         if (!flag) {
//             int pos = -1;

//             // Look for an empty frame
//             for (j = 0; j < f; j++) {
//                 if (frames[j] == -1) {
//                     pos = j;  // use empty frame
//                     break;
//                 }
//             }

//             // If no empty frame, find least recently used one
//             if (pos == -1)
//                 pos = findLRU(time, f);

//             // Replace page in frame and update its last used time
//             frames[pos] = pages[i];
//             time[pos] = ++counter;
//             pageFaults++;

//             // Display frame status
//             printf("%d\t", pages[i]);
//             for (j = 0; j < f; j++) {
//                 if (frames[j] != -1)
//                     printf("%d ", frames[j]);  // display valid page
//                 else
//                     printf("- ");              // display empty frame
//             }
//             printf("\n");
//         }
//     }

//     // Final result
//     printf("\nTotal Page Faults = %d\n", pageFaults);
//     return 0;
// }










// 4. wap to stimulate paging technique of memory management 
// //Q4: Simulate Paging Technique in C
// #include <stdio.h>

// int main() {
//     int memSize, frameSize, numPages, i;
//     int pageTable[100];

//     printf("Enter memory size (in bytes): ");
//     scanf("%d", &memSize);

//     printf("Enter frame size (in bytes): ");
//     scanf("%d", &frameSize);

//     numPages = memSize / frameSize;

//     printf("Number of frames available: %d\n", numPages);

//     // Create page table
//     for (i = 0; i < numPages; i++) {
//         printf("Enter frame number where page %d is stored: ", i);
//         scanf("%d", &pageTable[i]);
//     }

//     int logicalAddr;
//     printf("\nEnter a logical address (page number and offset):\n");
//     int pageNum, offset;
//     scanf("%d %d", &pageNum, &offset);

//     if (pageNum >= numPages || offset >= frameSize) {
//         printf("Invalid page number or offset!\n");
//     } else {
//         int frameNum = pageTable[pageNum];
//         int physicalAddr = frameNum * frameSize + offset;
//         printf("Physical Address: %d\n", physicalAddr);
//     }

//     return 0;
// }




// 5. wap to implement lfu page replacement algorithm.
// // Q5: LFU Page Replacement Algorithm in C
// #include <stdio.h>

// #define MAX 100  // Maximum number of pages

// // Define a structure to hold page number and its frequency
// typedef struct {
//     int page;  // page number
//     int freq;  // how many times the page was used
// } PageFrame;

// // Function to find the index of the Least Frequently Used (LFU) page
// int findLFU(PageFrame frames[], int frameCount) {
//     int minFreq = frames[0].freq;
//     int pos = 0;

//     // Loop to find the page with minimum frequency
//     for (int i = 1; i < frameCount; i++) {
//         if (frames[i].freq < minFreq) {
//             minFreq = frames[i].freq;
//             pos = i;
//         }
//     }
//     return pos;  // Return position of LFU page
// }

// int main() {
//     int pages[MAX], n, frameCount;

//     // Input number of pages
//     printf("Enter number of pages: ");
//     scanf("%d", &n);

//     // Input page reference string
//     printf("Enter page reference string: ");
//     for (int i = 0; i < n; i++) {
//         scanf("%d", &pages[i]);
//     }

//     // Input number of frames available
//     printf("Enter number of frames: ");
//     scanf("%d", &frameCount);

//     PageFrame frames[frameCount];  // Array of page frames
//     int pageFaults = 0;            // Counter for page faults
//     int filled = 0;                // Number of frames currently filled

//     // Initialize all frames as empty
//     for (int i = 0; i < frameCount; i++) {
//         frames[i].page = -1;  // -1 indicates empty frame
//         frames[i].freq = 0;
//     }

//     // Process each page in the reference string
//     for (int i = 0; i < n; i++) {
//         int page = pages[i];
//         int found = 0;

//         // Check if page is already in a frame (Page Hit)
//         for (int j = 0; j < frameCount; j++) {
//             if (frames[j].page == page) {
//                 frames[j].freq++;  // Increase frequency count
//                 found = 1;
//                 break;
//             }
//         }

//         // Page not found -> Page Fault
//         if (!found) {
//             if (filled < frameCount) {
//                 // If there's empty space in memory, insert page
//                 frames[filled].page = page;
//                 frames[filled].freq = 1;
//                 filled++;
//             } else {
//                 // If all frames are full, replace LFU page
//                 int replacePos = findLFU(frames, frameCount);
//                 frames[replacePos].page = page;
//                 frames[replacePos].freq = 1;
//             }
//             pageFaults++;  // Increase page fault count
//         }

//         // Print current status of frames
//         printf("Frame: ");
//         for (int j = 0; j < frameCount; j++) {
//             if (frames[j].page != -1)
//                 printf("%d ", frames[j].page);  // Print loaded pages
//             else
//                 printf("- ");  // Print empty slots
//         }
//         printf("\n");
//     }

//     // Print total page faults
//     printf("\nTotal Page Faults: %d\n", pageFaults);
//     return 0;
// }


