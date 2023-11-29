#include <bits/stdc++.h>
#include "Process.h"
using namespace std;

void SJFP(vector<Process> processes, int n,int Total_Exetime)
{
    int k = 0,processexe = 0;
    string Exe;

    sort(processes.begin(), processes.end(), SortByArrival); 
    vector<Process *> ReadyQueue;

    for (int time = 0;time < Total_Exetime ; time++)
    {   
        while (k < n)
        {
            if (processes[k].arrival_time > time)
            {
                break;
            }
            ReadyQueue.push_back(&processes[k]);
            k++;
        }
        if (ReadyQueue.empty())
        {
            Total_Exetime++;
            continue;
        }
        sort(ReadyQueue.begin(), ReadyQueue.end(), SortByRemTime);
        Process *j = ReadyQueue.front();
        j->remaining_time--;

        if (j->remaining_time == 0)
        {
            j->finish_time = time+1;
            j->turnaround_time = j->finish_time - j->arrival_time;
            j->waiting_time = j->turnaround_time - j->burst_time;
            Exe += "P" + to_string(j->id) + " ";
            processexe++;
            ReadyQueue.erase(ReadyQueue.begin());
        }
    }
    cout << "\nSJF-P Execution Order: " << Exe << "\n";
    sort(processes.begin(), processes.end(), SortByProcessId);
    cout << "Process\tFinish Time\tTurnaround Time\tWaiting Time\n";
    for (auto &i : processes)
    {
        cout << i.id << "\t" << i.finish_time << "\t\t"
             << i.turnaround_time << "\t\t" << i.waiting_time << endl;
    }
}
