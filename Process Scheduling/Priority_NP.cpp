#include <bits/stdc++.h>
#include "Process.h"
using namespace std;

void PriorityNP(vector<Process> processes, int n)
{
    int time = 0, k = 0;
    string Exe;

    sort(processes.begin(), processes.end(), SortByArrival);
    vector<Process *> ReadyQueue;

    for (int j = 0; j < n; j++)
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
        sort(ReadyQueue.begin(), ReadyQueue.end(), SortByPriority);

        Process *i = ReadyQueue.front();
        time += i->burst_time;
        i->finish_time = time;
        i->turnaround_time = i->finish_time - i->arrival_time;
        i->waiting_time = i->turnaround_time - i->burst_time;
        Exe += "P" + to_string(i->id) + " ";
        ReadyQueue.erase(ReadyQueue.begin());
    }

    cout << "\nPriority-NP Execution Order: " << Exe << "\n";
    sort(processes.begin(), processes.end(), SortByProcessId);
    cout << "Process\tFinish Time\tTurnaround Time\tWaiting Time\n";
    for (auto &i : processes)
    {
        cout << i.id << "\t" << i.finish_time << "\t\t"
             << i.turnaround_time << "\t\t" << i.waiting_time << endl;
    }
}
