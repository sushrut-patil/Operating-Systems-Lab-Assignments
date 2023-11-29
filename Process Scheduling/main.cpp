#include <bits/stdc++.h>
#include "FCFS.cpp"
#include "SJF_NP.cpp"
#include "Priority_NP.cpp"
using namespace std;

int main()
{
    int n;
    n = 4;
    vector<int> AT{3,1,0,5};
    vector<int> BT{1,3,4,5};
    vector<int> P{3,4,0,3};
    // cout << "Enter the number of processes: ";
    // cin >> n;
    vector<Process> processes(n);

    // cout << "Enter arrival time for processes : ";
    for (int i = 0; i < n; i++)
    {
        processes[i].id = i + 1;
        processes[i].arrival_time = AT[i];
        processes[i].burst_time = BT[i];
        processes[i].priority = P[i];
        // cin >> processes[i].arrival_time;
    }

    // cout << "Enter burst time for process : ";
    // for (int i = 0; i < n; i++)
    // {
    //     cin >> processes[i].burst_time;
    // }

    // cout << "Enter priority of process : ";
    // for (int i = 0; i < n; i++)
    // {
    //     cin >> processes[i].priority;
    // }
    
    
    // FCFS(processes, n);
    // SJFNP(processes,n);
    // PriorityNP(processes,n);

    return 0;
}