#pragma once

class Process
{
public:
    int id, arrival_time, burst_time;
    int finish_time, turnaround_time, waiting_time;
};

inline bool SortByArrival(const Process &p1, const Process &p2)
{
    if (p1.arrival_time != p2.arrival_time)
        return p1.arrival_time < p2.arrival_time;
    return p1.id < p2.id;
}

inline bool SortByProcessId(const Process &p1, const Process &p2)
{
    return p1.id < p2.id;
}

inline bool SortByShortTime(const Process* p1 , const Process* p2)
{
    return p1->burst_time < p2->burst_time;
}