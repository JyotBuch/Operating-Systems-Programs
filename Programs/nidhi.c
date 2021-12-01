#include <stdio.h>
#include <stdlib.h>
#define size 10
 main()
{
    int Max_need[size][size], alloc[size][size], rem_Need[size][size], avail[size], completed[size], safe[size];
    int p, r, i, j, process, count=0;

    printf("Enter the no of processes : ");
    scanf("%d", &p);

    for(i = 0; i< p; i++)
        completed[i] = 0;               //  flag whether the process completed or not

    printf("\n\nEnter the no of resources : ");
    scanf("%d", &r);

    printf("\n\nEnter the Max_need [Matrix] for each process : ");
    for(i = 0; i < p; i++)// p is the number of processes
    {
        printf("\nFor process %d : ", i + 1);
        for(j = 0; j < r; j++)// for each process number of resources is r
            scanf("%d", &Max_need[i][j]);
    }

    printf("\n\nEnter the allocation for each process : ");//take the allocated value of resources of each process
    for(i = 0; i < p; i++)
    {
        printf("\nFor process %d : ",i + 1);
        for(j = 0; j < r; j++)
            scanf("%d", &alloc[i][j]);
    }

    printf("\n\nEnter the Current Available Resources with OS : ");
    for(j = 0; j < r; j++)
        scanf("%d", &avail[j]);

    for(i = 0; i < p; i++)
    {// here we calculate the remaining need of each resource for each process
        for(j = 0; j < r; j++)
            rem_Need[i][j] = Max_need[i][j] - alloc[i][j];
    }

        do
        {
            printf("\nMax need matrix:\t\tAllocation matrix:\t\tRemaining need matrix:\n");

            for(i = 0; i < p; i++)
            {
                for( j = 0; j < r; j++)
                {
                    printf("%d ", Max_need[i][j]);
                    printf("\t");
                }


                for( j = 0; j < r; j++)
                {
                    printf("%d ", alloc[i][j]);
                    printf("\t");
                }

                for( j = 0; j < r; j++)
                {
                    printf("%d ", rem_Need[i][j]);
                    printf("\t");
                }
                printf("\n");
            }

            process = -1;           // For Each loop eligible process variable set = -1

            for(i = 0; i < p; i++)
            {
                if(completed[i] == 0)   //if not completed
                {
                    process = i ;       // Process Value updated
                    for(j = 0; j < r; j++)
                    {
                        if(avail[j] <rem_Need[i][j])       // for each Resource of need matrix availability checked
                        {
                            process = -1; //  if one of resource is having higher value then RESET default value
                            break;
                        }
                    }
                }
                if(process != -1)
                    break;
            }

            if(process != -1)
            {
                printf("\nProcess %d runs to completion!", process + 1);
                safe[count] = process + 1;
                count++;                            // increment count of completed process
                for(j = 0; j < r; j++)
                {
                    avail[j]= avail[j]+alloc[process][j];
                    alloc[process][j] = 0;         // allocation turned to zero
                    Max_need[process][j] = 0;
                    rem_Need[process][j] = 0;
                    completed[process] = 1;             // mark completed process
                }
                printf("New Availability of Resource:");
                for(j=0;j<r;j++)
                printf("%d", avail[j]);

            }
        }while(count != p && process != -1);

        if(count == p)
        {
            printf("\nThe system is in a safe state!!\n");
            printf("Safe Sequence : < ");
            for( i = 0; i < p; i++)
                printf("%d ", safe[i]);
            printf(">\n");
        }
        else
            printf("\nThe system is in an unsafe state!!");

}