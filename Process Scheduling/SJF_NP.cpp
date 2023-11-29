#include <bits/stdc++.h>
#include "Process.h"
using namespace std;

void SJFNP(vector<Process> processes, int n)
{
    int time = 0, k = 0,processexe = 0;
    string Exe;

    sort(processes.begin(), processes.end(), SortByArrival);
    vector<Process *> ReadyQueue;

    while(processexe < n)
    {
        /* The code snippet is a while loop that iterates through the remaining processes and adds them
        to the ReadyQueue if their arrival time is less than or equal to the current time. */
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
            time++;
            continue;
        }
        sort(ReadyQueue.begin(), ReadyQueue.end(), SortByShortTime);

        Process *i = ReadyQueue.front();
        time += i->burst_time;
        i->finish_time = time;
        i->turnaround_time = i->finish_time - i->arrival_time;
        i->waiting_time = i->turnaround_time - i->burst_time;
        Exe += "P" + to_string(i->id) + " ";
        processexe++;
        ReadyQueue.erase(ReadyQueue.begin());
    }

    cout << "\nSJF-NP Execution Order: " << Exe << "\n";
    sort(processes.begin(), processes.end(), SortByProcessId);
    cout << "Process\tFinish Time\tTurnaround Time\tWaiting Time\n";
    for (auto &i : processes)
    {
        cout << i.id << "\t" << i.finish_time << "\t\t"
             << i.turnaround_time << "\t\t" << i.waiting_time << endl;
    }
}
