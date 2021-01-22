#include<bits/stdc++.h>
#define MAX_HEAP_SIZE 100000
#define MAXREAL 999999.0
#define MAX_TREE_HT 100
using namespace std;
class HeapItem
{
public:
    char letter; //actual data that is stored
    int f;
    HeapItem *left,*right;
};

class MinHeap
{
public:
    HeapItem * A; //stores heap items, e.g., nodes
    int heapLength;

    MinHeap() //constructor
    {
        A = new HeapItem[MAX_HEAP_SIZE];
        heapLength=0;
    }

    ~MinHeap() //destructor
    {

        if(A) delete [] A;
        A = 0; //set to NULL after deletion
    }

    void insertItem(HeapItem ob)
    {
        heapLength++;
        A[heapLength]=ob;
        if(heapLength>1)
            buHeapify(heapLength);
    }

    HeapItem* removeMin()
    {
        if(Empty())
            printf("Heap is empty.\n");
        else
        {
            HeapItem *temp;
            temp=new HeapItem();
            if(heapLength==1)
            {
                temp->letter=A[1].letter;
                temp->f=A[1].f;
                temp->left=A[1].left;
                temp->right=A[1].right;
                heapLength=0;
                return temp;

            }
            else
            {
                temp->letter=A[1].letter;
                temp->f=A[1].f;
                temp->left=A[1].left;
                temp->right=A[1].right;
                A[1]=A[heapLength];
                heapLength--;
                if(heapLength>1)
                    heapify(1);
                return temp;
            }

        }
    }

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
            else if( A[l].f < A[r].f )
                smallest = l;
            else
                smallest = r;

            if(A[i].f <= A[smallest].f)
                break;	//we are done heapifying
            else
            {
                //swap nodes with smallest child, adjust map array accordingly
                HeapItem t;
                t=A[i];
                A[i]=A[smallest];
                A[smallest]=t;
                i=smallest;
            }
        }
    }


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
            printf("(%c,%d) ", A[i].letter, A[i].f);
        }
        printf("\n");
    }

    bool Empty()
    {
        if(heapLength==0)return true;
        else return false;
    }
};
void printArrc(char arr[], int n)
{
    int i;
    for(i = 0; i < n; ++i)
        printf("%c  ", arr[i]);
    printf("\n");
}
void printArri(int arr[], int n)
{
    int i;
    for (i = 0; i < n; ++i)
        printf("%d  ", arr[i]);
    printf("\n");
}


void printCodes(HeapItem *root, int a[], int p)
{

    if (root->left)
    {
        a[p] = 0;
        printCodes(root->left, a, p + 1);
    }


    if (root->right)
    {
        a[p] = 1;
        printCodes(root->right, a, p + 1);
    }


    if (root->left==0 && root->right==0)
    {
        printf("%c : ", root->letter);
        printArri(a,p);
    }
}

int main()
{
    while(1){

    int n;
    MinHeap heap;
    printf("How many characters?\n");
    scanf("%d",&n);
    int freq[n]= {};
    char C[n]="";

    printf("Enter character and frequency->\n");
    for(int i=0; i<n; i++)
    {
        scanf("%s",&C[i]);
        scanf("%d",&freq[i]);
        HeapItem temp;
        temp.letter=C[i];
        temp.f=freq[i];
        temp.left=NULL;
        temp.right=NULL;
        heap.insertItem(temp);
    }
    //printArrc(C,n);
    //printArri(freq,n);
    //heap.printHeap();
    //for(int j=0;j<n;j++)
    //printf("%d\n",heap.removeMin()->f);
    for(int k=0; k<n-1; k++)
    {
        HeapItem parent;
        parent.left=new HeapItem();
        parent.right=new HeapItem();
        parent.left=heap.removeMin();
        parent.right=heap.removeMin();
        //printf("%d",heap.heapLength);
        //printf("%d %d\n",parent.left->f,parent.right->f);
        //heap.printHeap();
        parent.letter='I';
        parent.f=parent.left->f+ parent.right->f;
        heap.insertItem(parent);
        //heap.printHeap();
    }

    HeapItem *root;
    root=new HeapItem();
    root=heap.removeMin();
    //printf("%d",root->f);
    int a[MAX_TREE_HT], d = 0;
    printf("Output of compression code:\n");
    printCodes(root, a, d);
    //printf("%d",root->f);
    }


    return 0;
}
