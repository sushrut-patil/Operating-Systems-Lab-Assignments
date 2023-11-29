#include <bits/stdc++.h>
#include "FCFS.cpp"
#include "SJF_NP.cpp"
#include "SJF_P.cpp"
#include "Priority_NP.cpp"
#include "Priority_P.cpp"
#include "Round_Robin.cpp"
using namespace std;

int main()
{
    int n,Total_Execution_time = 0,time_slice = 1;

    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> processes(n);
    cout << "Enter arrival time for processes : ";
    for (int i = 0; i < n; i++)
    {
        processes[i].id = i + 1;
        cin >> processes[i].arrival_time;
    }

    cout << "Enter burst time for process : ";
    for (int i = 0; i < n; i++)
    {
        cin >> processes[i].burst_time;
        processes[i].remaining_time = processes[i].burst_time;
        Total_Execution_time += processes[i].burst_time;
    }

    cout << "Enter priority of process : ";
    for (int i = 0; i < n; i++)
    {
        cin >> processes[i].priority;
    }
    
    cout << "Enter Time Slice for Round Robin : ";
    cin >> time_slice;
    
    FCFS(processes, n);
    SJFNP(processes,n);
    SJFP(processes,n,Total_Execution_time);
    PriorityNP(processes,n);
    PriorityP(processes,n,Total_Execution_time);
    RoundRobin(processes,n,Total_Execution_time,time_slice);
    return 0;
}