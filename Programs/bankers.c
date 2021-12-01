#include<stdio.h>
#include<stdlib.h>

#define size 10

int main()
{
    //declaring variables required
    //rem_Need is to be calculated
    //availability needs to be updated after process completion
    int max_Need[size][size], alloc[size][size],
            rem_Need[size][size], avail[size], completed[size], safe[size];

    int p, r, i, j, count=0, process;

    //Enter number of processes
    printf("Number of Processes : ");
    scanf("%d", &p);

    //Enter number of resources required
    printf("Number of Resources Required : ");
    scanf("%d", &r);

    for(i=0;i<p;i++)
    {
        completed[i]=0;
    }

    //Enter the maximum requirement of each resource for every process
    printf("Enter the Maximum Requirement of each resource for each process");
    for(i=0;i<p;i++)
    {
        printf("\nFor Process %d : ", i+1);
        for(j=0;j<r;j++)
        {
            scanf("%d", &max_Need[i][j]);
        }
    }

    //Enter the current allocation of each resource for every process
    printf("Enter the Allocation Matrix of each resource for each process");
    for(i=0;i<p;i++)
    {
        printf("\nFor Process %d : ", i+1);
        for(j=0;j<r;j++)
        {
            scanf("%d", &alloc[i][j]);
        }
    }

    //Enter the current available resources after the processes are already assigned with some resources
    printf("Enter the available resources : ");
    for(j=0;j<r;j++)
    {
        scanf("%d", &avail[j]);
    }

    //Calculate remaining need for each process(Maximum need - Current allocatio)
    for(i=0;i<p;i++)
    {
        for(j=0;j<r;j++)
        {
            rem_Need[i][j] = max_Need[i][j] - alloc[i][j];
        }
    }

    do
    {
        //Print Everything
        printf("\nMaximum Need\t\tAllocation Matrix\t\tRemaining Need\n");
        for(i=0;i<p;i++)
        {
            for(j=0;j<r;j++)
            {
                printf(" %d ", max_Need[i][j]);
                printf("\t");
            }

            for(j=0;j<r;j++)
            {
                printf(" %d ", alloc[i][j]);
                printf("\t");
            }

            for(j=0;j<r;j++)
            {
                printf(" %d ", rem_Need[i][j]);
                printf("\t");
            }

            printf("\n");
        }

        //Compare available resources with remaining need for each process
        process = -1; //No process executed
        for(i=0;i<p;i++)
        {
            if(completed[i]==0)//If process 'x' is not completed
            {
                process = i;
                for (j = 0; j < r; j++)
                {
                    //If available is less than remaining, then break out of the if loop
                    if(avail[j]< rem_Need[i][j])
                    {//If condition not true break will not be executed
                        process=-1;
                        break;
                    }
                }
            }

            if(process!=-1)
            {
                break;
            }
        }

        if(process!=-1)
        {
            printf("Process %d has been completed \n", process+1);
            safe[count]=process+1;
            count++;
            for(j=0; j<r; j++)
            {
                avail[j]= avail[j]+alloc[process][j];
                alloc[process][j]=0;
                max_Need[process][j]=0;
                rem_Need[process][j]=0;
                completed[process]=1;
            }

            printf("New Availability of Resource : ");
            for(j=0;j<r;j++)
            {
                printf(" %d", avail[j]);
            }
        }
    }while(count!=p && process!=-1);

    if(count == p)
    {
        printf("\nSystem is in Safe State\n");
        printf("\nSafe State Sequence <");

        for(i=0;i<p;i++);
        {
            printf(" %d", safe[i]);
        }

        printf(">\n");
    }

    else
        printf("Program is in Unsafe State");

     return 0;
}



// #include <stdio.h>
// #include <stdlib.h>
// int main()
// {
//     int Max[10][10], need[10][10], allocation[10][10], available[10], completed[10], safeSequence[10];
//     int p, r, i, j, process, count;
//     count = 0;

//     printf("Enter the no of processes : ");
//     scanf("%d", &p);

//     for(i = 0; i< p; i++)
//         completed[i] = 0;               //  flag whether the process completed or not

//     printf("\n\nEnter the no of resources : ");
//     scanf("%d", &r);

//     printf("\n\nEnter the Max Matrix for each process : ");
//     for(i = 0; i < p; i++)
//     {
//         printf("\nFor process %d : ", i + 1);
//         for(j = 0; j < r; j++)
//             scanf("%d", &Max[i][j]);
//     }

//     printf("\n\nEnter the allocation for each process : ");
//     for(i = 0; i < p; i++)
//     {
//         printf("\nFor process %d : ",i + 1);
//         for(j = 0; j < r; j++)
//             scanf("%d", &allocation[i][j]);
//     }

//     printf("\n\nEnter the Current Available Resources with OS : ");
//     for(i = 0; i < r; i++)
//         scanf("%d", &available[i]);

//     for(i = 0; i < p; i++)
//         for(j = 0; j < r; j++)
//             need[i][j] = Max[i][j] - allocation[i][j];

//         do
//         {
//             printf("\nMax matrix:\tAllocation matrix:\n");

//             for(i = 0; i < p; i++)
//             {
//                 for( j = 0; j < r; j++)
//                     printf("%d ", Max[i][j]);

//                 printf("\t\t");

//                 for( j = 0; j < r; j++)
//                     printf("%d ", allocation[i][j]);

//                 printf("\n");
//             }

//             process = -1;           // For Each loop eligible process variable set = -1

//             for(i = 0; i < p; i++)
//             {
//                 if(completed[i] == 0)   //if not completed
//                 {
//                     process = i ;       // Process Value updated
//                     for(j = 0; j < r; j++)
//                     {
//                         if(available[j] <= need[i][j])       // for each Resource of need matrix availability checked
//                         {
//                             process = -1; //  if one of resource is having higher value then RESET default value
//                             break;
//                         }
//                     }
//                 }
//                 if(process != -1)
//                     break;
//             }

//             if(process != -1)
//             {
//                 printf("\nProcess %d runs to completion!", process + 1);
//                 safeSequence[count] = process + 1;
//                 count++;                            // increment count of completed process
//                 for(j = 0; j < r; j++)
//                 {
//                     available[j] += allocation[process][j];
//                     allocation[process][j] = 0;         // allocation turned to zero
//                     Max[process][j] = 0;
//                     completed[process] = 1;             // mark completed process
//                 }
//             }
//         }
//         while(count != p && process != -1);

//         if(count == p)
//         {
//             printf("\nThe system is in a safe state!!\n");
//             printf("Safe Sequence : < ");
//             for( i = 0; i < p; i++)
//                 printf("%d ", safeSequence[i]);
//             printf(">\n");
//         }
//         else
//             printf("\nThe system is in an unsafe state!!");

// }