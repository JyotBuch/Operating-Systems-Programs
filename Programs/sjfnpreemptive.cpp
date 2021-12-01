#include<iostream>
#include<queue>
#include <vector>
#include <functional>
#include<string>
using namespace std;

typedef struct Process
{
int id;
int arrivalTime;
int burstTime;
int remBurstTime;
int finishTime;
int turnaroundTime;
int waitingTime;
}process;

//comparer lambda function for priority queue
auto compare = [](process* a, process* b) { return a->remBurstTime >=
b->remBurstTime; };

void sort_by_id(process proc[],int n)
{
    //sorts processes by process id
    process temp;
    for(int i = 0; i < n - 1; i++)
    {
        for(int j = 0; j < n - i - 1; j++)
        {
            if (proc[j].id > proc[j+1].id)
            {
                temp = proc[j];
                proc[j] = proc[j + 1];
                proc[j + 1] = temp;
            }
        }
    }
}
void sort_by_AT(process proc[],int n)
{
//sorts processes by Arrival Time
    process temp;
    for(int i = 0; i < n - 1; i++)
    {
        for(int j = 0; j < n - i - 1; j++)
        {
            if (proc[j].arrivalTime > proc[j+1].arrivalTime)
            {
                temp = proc[j];
                proc[j] = proc[j + 1];
                proc[j + 1] = temp;
            }
    }
    }
}
void SJF(process proc[],int n)
{
    process *current;
    int i,finished,last;
    priority_queue<process*,vector<process*>,decltype(compare)> queue(compare);
    //priority queue of process pointers
    string gantt = "";
    string ganttn = "";
    sort_by_AT(proc,n);
    queue.push(&proc[0]); //enqueue process with least arrival time
    i = 1;
    finished = 0;
    while(finished < n)
    {
        current = queue.top();
        queue.pop();
        current->remBurstTime--;
        if(current->id == last)
        {
            gantt += " ";
            ganttn += " ";
        }
        else
        {
            gantt += "| P" + to_string(current->id) + " ";
            ganttn += to_string(i-1) + " ";
        }
        if(current->remBurstTime == 0)
        {
            finished++;
            current->finishTime = i;
            current->turnaroundTime = current->finishTime - current->arrivalTime;
            current->waitingTime = current->turnaroundTime - current->burstTime;
            if(finished == n)
            {
                gantt += " |";
                ganttn += to_string(i);
            }
        }
        //enqueue process that arrives at current time
        for(int j = 0; j < n; j++)
        {
            if(i == proc[j].arrivalTime)
            queue.push(&proc[j]);
        }
        //enqueue current process if it is not finished
        if(current->remBurstTime != 0)
            queue.push(current);
        last = current->id;
        i++;
    }
    sort_by_id(proc,n);
    //printing table
    cout << "\n\t\tAT\t\tBT\t\tFT\t\tTT\t\tWT";
    for(int i = 0; i < n; i++)
    {
    cout << endl << "P" << proc[i].id << "\t\t" << proc[i].arrivalTime << "\t\t" <<
    proc[i].burstTime << "\t\t" << proc[i].finishTime << "\t\t" << proc[i].turnaroundTime <<
    "\t\t" << proc[i].waitingTime;
    }
    //printing gantt chart
    cout << endl << endl << gantt << endl << ganttn;
}
int main()
{
    int n;
    cout << "SHORTEST JOB FIRST - PREEMPTIVE" << endl;
    cout << "Enter number of processes : ";
    cin >> n;
    process proc[n];
    for(int i = 0; i < n; i++)
    {
        proc[i].id = i + 1;
        cout << "Enter the arrival time of process P" << (i + 1) << " : ";
        cin >> proc[i].arrivalTime;
        cout << "Enter the burst time of process P" << (i + 1) << " : ";
        cin >> proc[i].burstTime;
        proc[i].remBurstTime = proc[i].burstTime;
        cout << endl;
    }
    SJF(proc,n);
    return 0;
}