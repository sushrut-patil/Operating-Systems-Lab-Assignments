#include <bits/stdc++.h>
#include "Process.h"
using namespace std;

void RoundRobin(vector<Process> processes, int n, int Total_Exetime,int time_slice)
{
    int k = 0;
    string Exe;

    sort(processes.begin(), processes.end(), SortByArrival);
    list<Process *> ReadyQueue;

    for (int time = 0; time < Total_Exetime; time += time_slice)
    {
        while (k < n)
        {
            if (processes[k].arrival_time > time)
            {
                break;
            }
            ReadyQueue.push_front(&processes[k]);
            k++;
        }
        if (ReadyQueue.empty())
        {
            Total_Exetime++;
            continue;
        }
        Process *j = ReadyQueue.front();
        j->remaining_time -= time_slice;

        if (j->remaining_time <= 0)
        {
            time += j->remaining_time;
            j->finish_time = time + time_slice;
            j->turnaround_time = j->finish_time - j->arrival_time;
            j->waiting_time = j->turnaround_time - j->burst_time;
            Exe += "P" + to_string(j->id) + " ";
            ReadyQueue.pop_front();
            
            continue;
        }
        ReadyQueue.push_back(ReadyQueue.front());
        ReadyQueue.pop_front();
    }
    cout << "\nRound Robin Execution Order: " << Exe << "\n";
    sort(processes.begin(), processes.end(), SortByProcessId);
    cout << "Process\tFinish Time\tTurnaround Time\tWaiting Time\n";
    for (auto &i : processes)
    {
        cout << i.id << "\t" << i.finish_time << "\t\t"
             << i.turnaround_time << "\t\t" << i.waiting_time << endl;
    }
}
