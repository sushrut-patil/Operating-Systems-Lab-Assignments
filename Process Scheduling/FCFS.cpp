#include <bits/stdc++.h>
#include "Process.h"
using namespace std;

void FCFS(vector<Process> processes, int n)
{   
    int time = 0;
    string Exe;

    sort(processes.begin(), processes.end(), SortByArrival);
    
    for (int i = 0; i < n; i++)
    {
        time += processes[i].burst_time;
        processes[i].finish_time = time;
        processes[i].turnaround_time = processes[i].finish_time - processes[i].arrival_time;
        processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
        Exe += "P" + to_string(processes[i].id) + " ";
    }
    cout << "\nFCFS Execution Order: " << Exe << "\n";

    sort(processes.begin(),processes.end(),SortByProcessId);
    cout << "Process\tFinish Time\tTurnaround Time\tWaiting Time\n";
    for (auto &i : processes)
    {
        cout << i.id << "\t" << i.finish_time << "\t\t"
             << i.turnaround_time << "\t\t" << i.waiting_time << endl;
    }
}


