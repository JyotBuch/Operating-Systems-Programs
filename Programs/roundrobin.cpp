#include<iostream>
#include<string>
#define SIZE 20
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
} process;
//queue of process pointers
class Queue
{
    private:
        process* items[SIZE];
        int front, rear;

    public:
        Queue()
        {
        front = -1;
        rear = -1;
        }
        bool isFull()
        {
        if(front == 0 && rear == SIZE - 1)
        return true;
        if(front == rear + 1)
        return true;
        return false;
        }
        bool isEmpty()
        {
        if(front == -1)
        return true;
        else
        return false;
        }
        void enQueue(process* element)
        {
            if(isFull())
                cout << "Queue is full";
            else
            {
                if(front == -1)
                    front = 0;
                rear = (rear + 1) % SIZE;
                items[rear] = element;
            }
        }
        process* deQueue()
        {
            process* element;
            if(isEmpty())
            {
                cout << "Queue is empty" << endl;
            }
            else
            {
                element = items[front];
                if(front == rear)
                    {
                        front = -1;
                        rear = -1;
                    }
                else
                    front = (front + 1) % SIZE;
                return element;
            }
        }
};

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

void RoundRobin(process proc[],int n)
{
    Queue queue;
    int i,finished;
    string gantt = "|";
    process* current;
    sort_by_AT(proc,n);
    //enqueue process with least arrival time
    queue.enQueue(&proc[0]);
    i = 1;
    finished = 0;
    while(finished < n)
    {
        current = queue.deQueue();
        gantt += " P" + to_string(current->id) + " |";
        current->remBurstTime--;
        //current->remBurstTime = current->remBurstTime-2;
        //current process is finished
        if(current->remBurstTime == 0)
        {
            finished++;
            current->finishTime = i;
            current->turnaroundTime = current->finishTime - current->arrivalTime;
            current->waitingTime = current->turnaroundTime - current->burstTime;
        }
        //enqueue process that arrives at current time
        for(int j = 0; j < n; j++)
        {
            if(i == proc[j].arrivalTime)
            queue.enQueue(&proc[j]);
        }
        //enqueue current process if it is not finished
        if(current->remBurstTime != 0)
            queue.enQueue(current);
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
    cout << endl << endl << gantt << endl;
    cout << "0";
    for(int j = 1; j < i; j++)
    {
        if(j < 10)
        cout << " " << j;
        else
        cout << " " << j;
    }
}

int main()
{
    int n;
    cout << "ROUND ROBIN" << endl;
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
    RoundRobin(proc,n);
    return 0;
}