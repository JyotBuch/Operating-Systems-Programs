//Consider Page Reference String : 12,15,12,18,6,8,11,12,19,12,6,8,12,15,19,8

#include<stdio.h>

struct frame
{
    /* data */
    int pno;
    int counter;
}frames[5];

int ref_str[] = {12,15,12,18,6,8,11,12,19,12,6,8,12,15,19,8};
int np = 15, n, i, j, currtime;

int page_found(int pno)
{
    int i;
    for(i=0;i<n;i++)
    {
        if(frames[i].pno==pno)
            return i;//index of page found returned
        return -1;
    }
}

int get_lru()
{
    int min=0;
    for(i=0;i<n;i++)
    {
        if(frames[i].counter<frames[min].counter)//get the least repeating page
            min=i;
    }
    return min;
}

int main()
{
    int i, j, pno, p, page_fault=0,flag;
    printf("Enter number of frames : ");
    scanf("%d", &n);
    for(i=0;i<n;i++)
    {
        frames[i].pno = -1;
        frames[i].counter = -1;
    }
    printf("\n Page No.\tFrames\t\t\t\tPage Fault");
    printf("\n--------------------------------------------------------------");

    currtime=1;
    
    for(p=0;p<np;p++)
    {
        flag=0;
        pno=ref_str[p];
        j=page_found(pno);
        if(j==-1)
        {
            page_fault+=1;
            j=get_lru();
            frames[j].pno=pno;

            flag=1;
        }

        frames[j].counter=currtime;
        currtime+=1;
        printf("\n%5d\t", pno);

        for(i=0;i<n;i++)
        {
            printf("\t%2d:%2d", frames[i].pno, frames[i].counter);
        }

        if(flag==1)
        {
            printf("\t\tYES");
        }
        else
            printf("\t\tNO");

        printf("\n--------------------------------------------------------------");
    }

    printf("\nNo. of page fault : %d", page_fault);
}