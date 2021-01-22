#include<bits/stdc++.h>
using namespace std;
int *A;
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partitions(int low,int high)
{
    int p=low,r=high;
    int range = r- p + 1;
    int num = rand() % range + p;
    swap(&A[num],&A[r]);

    int x=A[r],i=p;
    for(int j=p; j<=r-1; j++)
    {
        if (A[j]<=x)
        {
            swap(A[i],A[j]);
            i=i+1;
        }
    }
    swap(A[i],A[r]);
    return i;
}

int selection_algorithm(int left,int right,int n)
{
    int kth=n/2;
    for(;;)
    {
        int pivotIndex=partitions(left,right);          //Select the Pivot Between Left and Right
        int len=pivotIndex-left+1;

        if(kth==len)
            return pivotIndex;

        else if(kth<len)
            right=pivotIndex-1;

        else
        {
            kth=kth-len;
            left=pivotIndex+1;
        }
    }
}

int partition_array(int start,int finish)
{

    int n=finish-start+1;
    int median=selection_algorithm(start,finish,n);

    swap(&A[median],&A[finish]);
    int pivot=A[finish];
    int pIndex=start;
    for (int j = start; j <finish; j++)
    {
        if (A[j] <= pivot)
        {
            swap(&A[j],&A[pIndex]);
            pIndex++;
        }
    }
    swap(&A[pIndex], &A[finish]);
    return pIndex;
}

void quicksort(int start,int finish)
{
    if(start<finish)
    {
        int pIndex=partition_array(start,finish);
        quicksort(start,pIndex-1);
        quicksort(pIndex+1,finish);

    }
}

void print_array(int n)
{
    if(n>0)
    {
        printf("The sorted array is:\n");
        for(int i=0; i<n; i++)
            printf("%d  ",A[i]);
        printf("\n");
    }
    else
        printf("Empty array\n");
}

void money_change(int ammount ,int n)
{
    int i;
    printf("Taka    numbers\n");
    for(i=n-1;i>=0;i--)
    {
        int nc=0;
        while(ammount>=A[i])
        {
            ammount=ammount-A[i];
            nc++;

        }
        if(nc!=0)
        {
            printf("%d         %d\n",A[i],nc);
        }

    }
}

int main()
{
    while(1)
    {
        int n,i,start,finish;
        printf("How many type of notes?\n");
        scanf("%d",&n);
        A=new int[n];
        if(n>0)
        {
            printf("Enter value of each note->\n");
            for (i=0; i<n; i++)
            {
                scanf("%d",&A[i]);

            }
        }

        int ammount;
        printf("Enter ammount->\n");
        scanf("%d",&ammount);
        if(n>1)
        {
            start=0;
            finish=n-1;
            quicksort(start,finish);
        }
        print_array(n);

        money_change(ammount,n);



    }

    return 0;
}


