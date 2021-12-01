#include<stdio.h>
int main()
{
    int fn,pn,frames[30],pages[30],temp[10],flag1,flag2,flag3,i,j,k,pos,max,pf=0;
    printf("\nEnter Number of Frames : ");
    scanf("%d",&fn);
    printf("Enter Number of Pages : ");
    scanf("%d",&pn);
    printf("Enter Page Reference String : ");
    for(i=0;i<pn;i++)
    {
        scanf("%d",&pages[i]);
    }
    for(i=0;i<fn;i++)
    {
        frames[i] = -1;
    }
    for(i=0;i<pn;i++)
    {
        flag1 = flag2 = 0;
        for(j=0;j<fn;j++)
        {
            if(frames[j] == pages[i])
            {
                flag1 = flag2 = 1;
                break;
            }
        }
        if(flag1 == 0)
        {
            for(j=0;j<fn;j++)
            {
                if(frames[j] == -1)
                {
                    pf++;
                    frames[j] = pages[i];
                    flag2 = 1;
                    break;
                }
            }
        }
        if(flag2 == 0)
        {
            flag3 =0;
            for(j=0;j<fn;j++)
            {
                temp[j] = -1;
                for(k=i+1;k<pn;k++)
                {
                    if(frames[j] == pages[k])
                    {
                        temp[j] = k;
                        break;
                    }
                }
            }
            for(j=0;j<fn;j++)
            {
                if(temp[j] == -1)
                {
                    pos = j;
                    flag3 = 1;
                    break;
                }
            }
            if(flag3 ==0)
            {
                max = temp[0];
                pos = 0;
                for(j=1;j<fn;j++)
                {
                    if(temp[j] > max)
                    {
                        max = temp[j];
                        pos = j;
                    }
                }
            }
            frames[pos] = pages[i];
            pf++;
        }
        printf("\n");
        for(j=0;j<fn;j++)
        {
            printf("%d\t", frames[j]);
        }
    }
    printf("\n\nTotal Page Faults : %d", pf);
    return 0;
}