#include<iostream>
using namespace std;
typedef struct Process
{
    int id;
    int arrivalTime;
    int burstTime;
    int finishTime;
    int turnaroundTime;
    int waitingTime;
    int priority;
}process;

void sort_by_priority(process proc[],int n)
    {
    //sorts processes by priority from index 1
    process temp;
    for(int i = 0; i < n - 1; i++)
    {
        for(int j = 1; j < n - i - 1; j++)
        {
            if (proc[j].priority > proc[j+1].priority)
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
void sort_by_FT(process proc[],int n)
{
    //sorts processes by Finish Time
    process temp;
    for(int i = 0; i < n - 1; i++)
    {
        for(int j = 0; j < n - i - 1; j++)
        {
            if (proc[j].finishTime > proc[j+1].finishTime)
            {
                temp = proc[j];
                proc[j] = proc[j + 1];
                proc[j + 1] = temp;
            }
        }
    }
}
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
void priority(process proc[],int n)
{
    sort_by_AT(proc,n);
    sort_by_priority(proc,n); //sorts from index 1 so 1st element is the one with least arrival time
    proc[0].finishTime = proc[0].arrivalTime + proc[0].burstTime;
    proc[0].turnaroundTime = proc[0].finishTime - proc[0].arrivalTime;
    proc[0].waitingTime = proc[0].turnaroundTime - proc[0].burstTime;
    for(int i = 1; i < n; i++)
    {
        proc[i].finishTime = proc[i - 1].finishTime + proc[i].burstTime;
        proc[i].turnaroundTime = proc[i].finishTime - proc[i].arrivalTime;
        proc[i].waitingTime = proc[i].turnaroundTime - proc[i].burstTime;
        }
    sort_by_id(proc,n);
    //printing table
    cout << "\n\t\tPR\t\tAT\t\tBT\t\tFT\t\tTT\t\tWT";
    for(int i = 0; i < n; i++)
    {
        cout << endl << "P" << proc[i].id << "\t\t" << proc[i].priority << "\t\t" <<
        proc[i].arrivalTime << "\t\t" << proc[i].burstTime << "\t\t" << proc[i].finishTime << "\t\t"
        << proc[i].turnaroundTime << "\t\t" << proc[i].waitingTime;
    }
}
void gantt_chart(process proc[],int n)
{
    //printing gantt chart
    cout << endl;
    int i,j,k,l;
    char gan1[200],gan2[200];
    sort_by_FT(proc,n);
    k=0;
    for(i=0;i<n;i++)
    {
        l=1;
        if(i==0)
        {
            j = proc[i].finishTime;
            gan2[k] = '0';
        }
        else
            j = (proc[i].finishTime - proc[i - 1].finishTime);
        gan1[k] = '|';
        k++;
        while(l<j)
        {
            gan1[k] = ' ';
            gan2[k] = ' ';
            k++;
            l++;
        }
        gan1[k] = 'P';
        gan2[k] = ' ';
        k++;
        gan1[k] = proc[i].id + 48;
        gan2[k] = ' ';
        k++;
        while(k <= proc[i].finishTime * 2)
        {
            gan1[k] = ' ';
            gan2[k] = ' ';
            k++;
        }
        gan1[k] = '|';
        gan2[k] = (proc[i].finishTime % 10) + 48;
        if((proc[i].finishTime / 10) > 0)
            gan2[k-1] = (proc[i].finishTime / 10) + 48;
    }
    k++;
    gan1[k] = '\0';
    gan2[k] = '\0';
    cout << "\n\n";
    for(i = 0; i < k; i++)
        cout << gan1[i];
    cout << "\n";
    for(i = 0; i < k; i++)
        cout << gan2[i];
}
int main()
{
    int n;
    cout << "PRIORITY - NON PREEMPTIVE" << endl;
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
        cout << "Enter the priority of process P" << (i + 1) << " : ";
        cin >> proc[i].priority;
        cout << endl;
    }
    priority(proc,n);
    gantt_chart(proc,n);
    return 0;
}