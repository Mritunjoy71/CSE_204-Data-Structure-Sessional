#include<stdio.h>

#define MAX_HEAP_SIZE 100000

#define MAXREAL 999999.0

class HeapItem
{
public:
    int data; //actual data that is stored
    float key; //key value of the data, heap is constructed based on key
};

//MinHeap class, minimum item stored at the root of heap tree
class MinHeap
{
public:
    HeapItem * A; //stores heap items, e.g., nodes
    int heapLength;
    int * map;

    MinHeap() //constructor
    {
        A = new HeapItem[MAX_HEAP_SIZE];
        map = new int[MAX_HEAP_SIZE];
        map[1]=0;
        heapLength=0;
    }

    ~MinHeap() //destructor
    {
        if(map) delete [] map;
        if(A) delete [] A;
        map = 0; //set to NULL after deletion
        A = 0; //set to NULL after deletion
    }

    //Fills the heap with an array of integers
    //key values do not maintain heap property
    //May be used in some algorithms such as dijkstra's shortest path
    void initialize(int v[], int n)
    {
        heapLength = n;
        for(int i=0; i<n; i++) //nodes are stored from index 1 instead of 0 in the heap
        {
            A[i+1].data = v[i];
            A[i+1].key = MAXREAL;
            map[v[i]] = i+1; //map tracks which vertex is stored at which heap node
        }
        buHeapify(n);
        //printf(" idx =%d\n",map[v[2]]);
    }

    //this function inserts a new (data,key) pair in the heap
    //call to buheapify is required
    void insertItem(int data, float key)
    {


        heapLength++;
        A[heapLength].data=data;
        map[data]=heapLength;
        A[heapLength].key=key;
        if(heapLength>1)
            buHeapify(heapLength);

    }

    //this function removes (and returns) the node which contains the minimum key value
    HeapItem removeMin()
    {
        if(Empty())
            printf("Heap is empty.\n");
        else
        {
            if(heapLength==1)
            {
                map[A[1].data]=0;
                heapLength=0;
                return A[1];

            }

            HeapItem minheap=A[1];
            map[minheap.data]=0;
            A[1]=A[heapLength];
            map[A[1].data]=1;
            heapLength--;
            if(heapLength>1)
                heapify(1);
            return minheap;


        }


    }


    //The function updates the key value of an existing data
    //stored in the heap
    //Note that updates can result in an increase or decrease of key value
    //Call to heapify or buheapify is required
    void updateKey(int data, float key)
    {
        if(heapLength==0)
        {
            printf("Heap is empty.\n");
            return ;
        }
        int i=map[data];
        if(i==0)
        {
            printf("This data doesn't exist.\n");
            return;
        }
        else
        {
            int temp=A[i].key;
            A[i].key=key;
            if(key<temp && i==1)
                return;
            else if(key<temp)
                buHeapify(i);
            else
                heapify(i);
            return ;
        }




    }


    //This function returns the key value of a data stored in heap
    float getKey(int data)
    {
        int i = map[data];
        return A[i].key;
    }

    //This function heapifies the heap
    //When a key value of ith node is increased (because of update), then calling
    //this function will restore heap property
    void heapify(int i)
    {
        int l,r,smallest;
        while(1)
        {
            l=2*i;      //left child index
            r=2*i+1;    //right child index
            smallest=i;

            if(l>heapLength && r>heapLength)
                break; //nothing to do, we are at bottom
            else if(r>heapLength)
                smallest = l;
            else if(l>heapLength)
                smallest = r;
            else if( A[l].key < A[r].key )
                smallest = l;
            else
                smallest = r;

            if(A[i].key <= A[smallest].key)
                break;	//we are done heapifying
            else
            {
                //swap nodes with smallest child, adjust map array accordingly
                HeapItem t;
                t=A[i];
                A[i]=A[smallest];
                map[A[i].data]=i;
                A[smallest]=t;
                map[A[smallest].data]=smallest;
                i=smallest;
            }

        }
    }

    //This function heapifies the heap form bottom to up
    //When a key value of ith node is decreased (because of update), then calling
    //this function will restore heap property
    //In addition, when a new item is inserted at the end of the heap, then
    //calling this function restores heap property
    void buHeapify(int i)
    {
        int k;
        for(k=i/2; k>=1; k--)
            heapify(k);

    }

    void printHeap()
    {
        printf("Heap length: %d\n", heapLength);
        for(int i=1; i<=heapLength; i++)
        {
            printf("(%d,%.2f) ", A[i].data, A[i].key);
        }
        printf("\n");
    }

    bool Empty()
    {
        if(heapLength==0)return true;
        else return false;
    }
};


int main()
{
    int choice;
    int data;
    float key;
    MinHeap heap;
    bool exit = false;
    //printf("map %d\n",heap.map[1]);
    while(!exit)
    {
        printf("1. Insert 2. RemoveMin 3.Update 4. Print 5. Initialize 6. get key 7.get index  8. Exit.\n");
        scanf("%d",&choice);
        switch(choice)
        {
        case 1:
            scanf("%d%f",&data,&key);
            heap.insertItem(data, key);
            heap.printHeap();
            break;
        case 2:
            if(heap.Empty())
                printf("Heap is empty.\n");
            else
            {
                HeapItem item;
                item = heap.removeMin();
                printf("Removed: (%d,%.2f)\n", item.data, item.key);
                heap.printHeap();
            }
            break;
        case 3:
            scanf("%d%f",&data,&key);
            heap.updateKey(data,key);
            heap.printHeap();
            break;
        case 4:
            heap.printHeap();
            break;
        case 5:
            printf("enter n:");
            int n,i;
            scanf("%d",&n);
            int *v;
            v=new int[n];
            for (i=0; i<n; i++)
                scanf("%d",&v[i]);
            heap.initialize(v,n);
            heap.printHeap();
            break;
        case 6:
            scanf("%d",&data);
            if(heap.map[data]!=0)
            {
                key=heap.getKey(data);
                printf("Key value of data %d is %f.\n",data,key);

            }
            else
                printf("This data doesn't exist.\n");
            break;
        case 7:
            scanf("%d",&data);
            if(heap.map[data]!=0)
                printf("Index of data %d is %d\n",data,heap.map[data]);
            else
                printf("This data doesn't exist.\n");
            break;


        case 8:
            exit = true;
            break;

        }
    }
    return 0;
}
