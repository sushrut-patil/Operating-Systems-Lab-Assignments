#include <bits/stdc++.h>
using namespace std;

void Print(string Type,int &n,int &seektime,vector<int> seeksequence)
{
    cout << Type <<" FCFS Total Seek Time = "<<seektime<<"\n";
    cout << Type <<" Average Seek Time = "<<(float)seektime/n<<"\n";
    cout << Type <<" Seek Sequence : ";
    for (int &i : seeksequence)
    {
        cout << i <<" ";
    }
    cout <<"\n"<<endl;
}
int closestIndex(int &n,int &head,vector<int> &requests)
{
    int c = 0;
    for (int i = 0; i < n; i++)
    {
        if (head < requests[i])
        {
            c = i;
            break;
        } 
    }
    return c;
}
void FCFS(int &n,int head,int &max,vector<int> &requests)
{   
    int seektime = 0;
    vector<int> seeksequence;
    for (int &i : requests)
    {
        seektime += abs(i - head);
        head = i;
        seeksequence.push_back(head);
    }
    Print("FCFS",n,seektime,requests);
}

/*
    Shortest Seek Time First 
*/
void SSTF(int &n,int head,int &max,vector<int> &requests)
{
    int seektime = 0;
    vector<bool> serviced(n,false);
    vector<int> seeksequence;
    for (int i = 0; i < n; i++)
    {
        int minseek = INT_MAX,request_index;
        for (int j = 0; j < n; j++)
        {
            if (!serviced[j] && abs(head - requests[j]) < minseek)
            {
                minseek = abs(head - requests[j]);
                request_index = j;
            }
        }
        head = requests[request_index];
        seeksequence.push_back(head);
        serviced[request_index] = true;
        seektime += minseek;
    }
    Print("SSTF",n,seektime,requests);
}

/*
    SCAN Algorithm
*/
void SCAN(int &n,int head,int &max,vector<int> requests)
{
    sort(requests.begin(),requests.end());
    int seektime = 0,closest_index = 0;
    vector<int> seeksequence;

    /* The code snippet is responsible for finding the index in the 
    `requests` vector that is closest to the current head position. */
    closest_index = closestIndex(n,head,requests);
    /* The code snippet is  responsible for scanning the disk in the forward 
    direction from the current head position to the end of the disk. */
    for (int i = closest_index; i < n; i++)
    {
        seektime += abs(head - requests[i]);
        seeksequence.push_back(requests[i]);
        head = requests[i];
    }
    
    /* The code snippet  is responsible for scanning the disk in the reverse 
    direction from the end of disk to the beginning of the disk. */
    seektime += max - 1 - requests[n - 1];
    head = max - 1;
    for (int i = closest_index - 1; i >= 0;i--)
    {
        seektime += abs(head - requests[i]);
        seeksequence.push_back(requests[i]);
        head = requests[i];
    }
    Print("SCAN",n,seektime,requests);
}

/*
    Circular SCAN
*/
void CSCAN(int &n,int head,int &max,vector<int> requests)
{
    sort(requests.begin(),requests.end());
    int seektime = 0,closest_index = 0;
    vector<int> seeksequence;

    closest_index = closestIndex(n,head,requests);
    for (int i = closest_index; i < n; i++)
    {
        seektime += abs(head - requests[i]);
        seeksequence.push_back(requests[i]);
        head = requests[i];
    }
    seektime += max - 1 - requests[n - 1];
    seektime += max - 1;
    head = 0;

    for (int i = 0; i < closest_index;i++)
    {
        seektime += abs(head - requests[i]);
        seeksequence.push_back(requests[i]);
        head = requests[i];
    }
    Print("C-SCAN",n,seektime,requests);
}
/*
    LOOK disk Scheduling Algorithm
*/
void LOOK(int &n,int head,int &max,vector<int> requests)
{
    sort(requests.begin(),requests.end());
    int seektime = 0,closest_index = 0;
    vector<int> seeksequence;

    closest_index = closestIndex(n,head,requests);
    for (int i = closest_index; i < n; i++)
    {
        seektime += abs(head - requests[i]);
        seeksequence.push_back(requests[i]);
        head = requests[i];
    }
    for (int i = closest_index - 1; i >= 0;i--)
    {
        seektime += abs(head - requests[i]);
        seeksequence.push_back(requests[i]);
        head = requests[i];
    }
    Print("LOOK",n,seektime,requests);
}
/*
    circular LOOK
*/
void CLOOK(int &n,int head,int &max,vector<int> requests)
{
    sort(requests.begin(),requests.end());
    int seektime = 0,closest_index = 0;
    vector<int> seeksequence;

    closest_index = closestIndex(n,head,requests);
    for (int i = closest_index; i < n; i++)
    {
        seektime += abs(head - requests[i]);
        seeksequence.push_back(requests[i]);
        head = requests[i];
    }
    for (int i = 0; i < closest_index;i++)
    {
        seektime += abs(head - requests[i]);
        seeksequence.push_back(requests[i]);
        head = requests[i];
    }
    Print("CLOOK",n,seektime,requests);
}

int main()
{  
    int n,head,max;
    
    cout << "Enter No of requests : ";
    cin >> n;
    vector<int> requests(n);
    cout << "\nEnter request order : ";
    for (int i = 0;i<n;i++)
    {
        cin >> requests[i];
    } 
    cout << "\nEnter intial Head Position : ";
    cin >> head;
    cout << "\nEnter Maximun number of Cylinders : ";
    cin >> max;
    cout <<"\n";

    // n = 7;
    // vector<int> requests {82 ,170 ,43 ,140 ,24 ,16 ,190};
    // max = 200;
    // head = 50;

    FCFS(n,head,max,requests);
    SSTF(n,head,max,requests);
    SCAN(n,head,max,requests);
    CSCAN(n,head,max,requests);
    LOOK(n,head,max,requests);
    CLOOK(n,head,max,requests);

    return 0;
}