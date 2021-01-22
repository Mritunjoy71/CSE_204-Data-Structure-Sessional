#include<stdio.h>
#include<stdlib.h>
#define NULL_VALUE -999999
#define INFINITY 999999
#define WHITE 1
#define GRAY 2
#define BLACK 3
#define MAX_HEAP_SIZE 100000
#define MAXREAL 999999.0
#define MAX_TREE_HT 100



///Heap//
class HeapItem
{
public:
    int vertex; //actual data that is stored
    int key;
};

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
            A[i+1].vertex = v[i];
            A[i+1].key = MAXREAL;
            map[v[i]] = i+1; //map tracks which vertex is stored at which heap node
        }
        buHeapify(n);
        //printf(" idx =%d\n",map[v[2]]);
    }

    //this function inserts a new (data,key) pair in the heap
    //call to buheapify is required
    void insertItem(int vertex, int key)
    {


        heapLength++;
        A[heapLength].vertex=vertex;
        map[vertex]=heapLength;
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
                map[A[1].vertex]=0;
                heapLength=0;
                return A[1];

            }

            HeapItem minheap=A[1];
            map[minheap.vertex]=0;
            A[1]=A[heapLength];
            map[A[1].vertex]=1;
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
    void updateKey(int vertex, int key)
    {
        if(heapLength==0)
        {
            printf("Heap is empty.\n");
            return ;
        }
        int i=map[vertex];
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
    float getKey(int vertex)
    {
        int i = map[vertex];
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
                map[A[i].vertex]=i;
                A[smallest]=t;
                map[A[smallest].vertex]=smallest;
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
            printf("(%d,%d) ", A[i].vertex, A[i].key);
        }
        printf("\n");
    }

    bool Empty()
    {
        if(heapLength==0)return true;
        else return false;
    }
};
///end of heap///


class Queue
{
    int queueInitSize ;
    int queueMaxSize;
    int * data;
    int length;
    int front;
    int rear;
public:
    Queue();
    ~Queue();
    void enqueue(int item); //insert item in the queue
    int dequeue(); //returns the item according to FIFO
    bool empty(); //return true if Queue is empty
};

Queue::Queue()
{
    queueInitSize = 2 ;
    queueMaxSize = queueInitSize;
    data = new int[queueMaxSize] ; //allocate initial memory
    length = 0 ;
    front = 0;
    rear = 0;
}


void Queue::enqueue(int item)
{
    if (length == queueMaxSize)
    {
        int * tempData ;
        //allocate new memory space for tempList
        queueMaxSize = 2 * queueMaxSize ;
        tempData = new int[queueMaxSize] ;
        int i, j;
        j = 0;
        for( i = rear; i < length ; i++ )
        {
            tempData[j++] = data[i] ; //copy items from rear
        }
        for( i = 0; i < rear ; i++ )
        {
            tempData[j++] = data[i] ; //copy items before rear
        }
        rear = 0 ;
        front = length ;
        delete[] data ; //free the memory allocated before
        data = tempData ; //make list to point to new memory
    }

    data[front] = item ; //store new item
    front = (front + 1) % queueMaxSize ;
    length++ ;
}


bool Queue::empty()
{
    if(length == 0) return true ;
    else return false ;
}


int Queue::dequeue()
{
    if(length == 0) return NULL_VALUE ;
    int item = data[rear] ;
    rear = (rear + 1) % queueMaxSize ;
    length-- ;
    return item ;
}


Queue::~Queue()
{
    if(data) delete[] data; //deallocate memory
    data = 0; //set to NULL
}

//****************Queue class ends here************************

//****************Dynamic ArrayList class based************************
class ArrayList
{
    int * list;
    int length ;
    int listMaxSize ;
    int listInitSize ;
public:
    ArrayList() ;
    ~ArrayList() ;
    int searchItem(int item) ;
    void insertItem(int item) ;
    void removeItem(int item) ;
    void removeItemAt(int item);
    int getItem(int position) ;
    int getLength();
    bool empty();
    void printList();
} ;


ArrayList::ArrayList()
{
    listInitSize = 2 ;
    listMaxSize = listInitSize ;
    list = new int[listMaxSize] ;
    length = 0 ;
}

void ArrayList::insertItem(int newitem)
{
    int * tempList ;
    if (length == listMaxSize)
    {
        //allocate new memory space for tempList
        listMaxSize = 2 * listMaxSize ;
        tempList = new int[listMaxSize] ;
        int i;
        for( i = 0; i < length ; i++ )
        {
            tempList[i] = list[i] ; //copy all items from list to tempList
        }
        delete[] list ; //free the memory allocated before
        list = tempList ; //make list to point to new memory
    };

    list[length] = newitem ; //store new item
    length++ ;
}

int ArrayList::searchItem(int item)
{
    int i = 0;
    for (i = 0; i < length; i++)
    {
        if( list[i] == item ) return i;
    }
    return NULL_VALUE;
}

void ArrayList::removeItemAt(int position) //do not preserve order of items
{
    if ( position < 0 || position >= length ) return ; //nothing to remove
    list[position] = list[length-1] ;
    length-- ;
}


void ArrayList::removeItem(int item)
{
    int position;
    position = searchItem(item) ;
    if ( position == NULL_VALUE ) return ; //nothing to remove
    removeItemAt(position) ;
}


int ArrayList::getItem(int position)
{
    if(position < 0 || position >= length) return NULL_VALUE ;
    return list[position] ;
}

int ArrayList::getLength()
{
    return length ;
}

bool ArrayList::empty()
{
    if(length==0)return true;
    else return false;
}

void ArrayList::printList()
{
    int i;
    for(i=0; i<length; i++)
        printf("%d ", list[i]);
    printf("Current size: %d, current length: %d\n", listMaxSize, length);
}

ArrayList::~ArrayList()
{
    if(list) delete [] list;
    list = 0 ;
}

//******************ArrayList class ends here*************************

//******************Graph class starts here**************************
class Graph
{
    bool directed ;
    int *color;
    int  *dist;
    int *parent;
    int  *start;
    int *finish;
    int time;

public:
    int **weight;
    ArrayList  * adjList ;
    int nVertices;
    int nEdges;
    Graph(bool dir = false);
    ~Graph();
    void setnVertices(int n);
    void addEdge(int u, int v,int w);
    void removeEdge(int u, int v);
    bool isEdge(int u, int v);
    int getDegree(int u);
    bool hasCommonAdjacent(int u, int v);
    int getDist(int u, int v);
    void printGraph();
    void bfs(int source); //will run bfs in the graph
    void dfs( ); //will run dfs in the graph
    void visit_dfs(int source);
};


Graph::Graph(bool dir)
{
    weight=0;
    nVertices = 0 ;
    nEdges = 0 ;
    adjList = 0 ;
    directed = dir ; //set direction of the graph
    color=0;
    dist=0;
    parent=0;
    start=0;
    finish=0;


}

void Graph::setnVertices(int n)
{
    this->nVertices = n ;
    if(adjList!=0) delete[] adjList ; //delete previous list
    adjList = new ArrayList[nVertices] ;
    color=new int[n];
    dist=new int[n];
    parent=new int[n];
    start=new int[n];
    finish=new int[n];
    weight = new int*[n];
    for(int i=0; i<n; i++)
    {
        weight[i] = new int[n];
        for(int j=0; j<n; j++)
            weight[i][j] =NULL_VALUE; //initialize the matrix cells to 0
    }

}

void Graph::addEdge(int u, int v,int w)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices) return; //vertex out of range
    this->nEdges++ ;
    weight[u][v]=w;
    weight[v][u]=w;
    adjList[u].insertItem(v) ;
    if(!directed)
        adjList[v].insertItem(u) ;
    printf("%d %d\n",weight[u][v],weight[v][u]);

}

void Graph::removeEdge(int u, int v)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices) return; //vertex out of range
    if(!directed)
    {
        adjList[u].removeItem(v);
        adjList[v].removeItem(u);
    }
    else
        adjList[u].removeItem(v);


}

bool Graph::isEdge(int u, int v)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices) return false; //vertex out of range
    if(adjList[u].searchItem(v)!=NULL_VALUE)
        return true;
    else
        return false;



}

int Graph::getDegree(int u)
{
    if(u<0 || u>=nVertices ) return NULL_VALUE; //vertex out of range
    return adjList[u].getLength();

}

bool Graph::hasCommonAdjacent(int u, int v)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices);
    {
        printf("Wrong input\n");
        return false;
    }
    int len=adjList[u].getLength();
    for (int i =0; i<len; i++)
    {
        if(adjList[v].searchItem(adjList[u].getItem(i))!=NULL_VALUE)
        {
            return true;
            break;
        }
    }
    return false;


}

void Graph::bfs(int source)
{

    for(int i=0; i<nVertices; i++)
    {
        color[i] = WHITE ;
        parent[i] = -1 ;
        dist[i] = INFINITY ;
    }
    Queue q ;
    color[source] = GRAY;
    dist[source] = 0 ;
    q.enqueue(source) ;
    while( !q.empty() )
    {
        int u;
        u=q.dequeue();
        int v;
        for(int j=0; j<adjList[u].getLength(); j++)
        {
            v=adjList[u].getItem(j);
            if(color[v]==WHITE)
            {
                color[v]=GRAY;
                dist[v]=dist[u]+1;
                parent[v]=u;
                q.enqueue(v);
            }

        }
        color[u]=BLACK;
    }
}

void Graph::dfs()
{
    int i;
    for (i=0; i<nVertices; i++)
    {
        color[i]=WHITE;
        parent[i]=-1;

    }
    time=0;
    for(i=0; i<nVertices; i++)
    {
        if(color[i]==WHITE)
            visit_dfs(i);
    }


}

void Graph::visit_dfs(int u)
{
    time=time+1;
    start[u]=time;
    color[u]=GRAY;
    int v;
    for(int j=0; j<adjList[u].getLength(); j++)
    {
        v=adjList[u].getItem(j);
        if(color[v]==WHITE)
        {
            parent[v]=u;
            visit_dfs(v);
        }

    }
    color[u]=BLACK;
    time=time+1;
    finish[u]=time;
}

int Graph::getDist(int u, int v)
{
    bfs(u);
    return dist[v];
}

void Graph::printGraph()
{
    //dfs();
    printf("\nNumber of vertices: %d, Number of edges: %d\n", nVertices, nEdges);
    for(int i=0; i<nVertices; i++)
    {
        printf("%d:", i);
        for(int j=0; j<adjList[i].getLength(); j++)
        {
            printf(" %d (%d)", adjList[i].getItem(j),weight[i][j]);
        }
        printf("\n");
        //printf("\t");
        //printf(":(%d/%d)\n",start[i],finish[i]);

    }
}

Graph::~Graph()
{
    if(adjList) delete[] adjList;
    adjList=0;
    if(color) delete[] color;
    color=0;
    if(dist) delete[] dist;
    dist=0;
    if(parent) delete[] parent;
    parent=0;
    if(start) delete[] start;
    start=0;
    if(finish) delete[] finish;
    finish=0;
    if(*weight) delete []*weight;
    weight=0;

}

//**********************Graph class ends here******************************
void PrimMST(Graph g,int **weight,int r)
{
    int parent[g.nVertices+1];
    MinHeap heap;
    int index[g.nVertices+1];
    int Map[g.nVertices+1];
    for (int i=0; i<=g.nVertices; i++)
    {
        int vertex,key;
        vertex=i;
        key=INFINITY;
        heap.insertItem(vertex,key);
        parent[i]=NULL_VALUE;
        index[i]=1;
        Map[i]=INFINITY;

    }
    heap.updateKey(r,0);
    Map[r]=0;
    parent[r]=NULL_VALUE;
    while(!heap.Empty())
    {
        int u,v;
        HeapItem temp;
        temp=heap.removeMin();
        u=temp.vertex;
        index[u]=0;
        for(v=1;v<=g.adjList[u].getLength();v++)
        {
            if(index[u]==1 && weight[u][v]<Map[v])
            {
                parent[v]=u;
                heap.updateKey(v,weight[u][v]);
                Map[v]=weight[u][v];

            }
        }


    }
     //Print edges of MST using parent array
    for (int i = 2; i <g.nVertices; ++i)
        printf("%d - %d\n", parent[i], i);


}

//******main function to test your code*************************
int main(void)
{


    /*
    int i,n,m;
    Graph g;
    int **weight;
    //printf("Enter number of vertices: ");
    scanf("%d", &n);
    g.setnVertices(n);
    scanf("%d",&m);
    g.nEdges=m;
    weight = new int*[n+1];
    for(int i=0; i<=n; i++)
    {
        weight[i] = new int[n+1];
        for(int j=0; j<=n; j++)
            weight[i][j] = INFINITY; //initialize the matrix cells to 0
    }
    int u,v,w;
    for(i=1; i<=m; i++)
    {
        scanf("%d %d %d",&u,&v,&w);
        g.addEdge(u,v);
        weight[u][v]=w;
        weight[v][u]=w;


    }
    PrimMST(g,weight,1);

     */

    int n;
    Graph g;
    printf("Enter number of vertices: ");
    scanf("%d", &n);
    g.setnVertices(n);
    while(1)
    {
        printf("1. Add edge.");
        printf("2. Remove edge.  3. isEdge  4. get degree\n5. Print Graph   6.common edge  7. get distance  8. Exit.\n");

        int ch;
        scanf("%d",&ch);
        if(ch==1)
        {
            int u, v,w;
            scanf("%d%d%d ", &u, &v,&w);
            g.addEdge(u, v,w);
        }
        else if(ch==2)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            g.removeEdge(u, v);

        }
        else if(ch==3)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            if(g.isEdge(u, v))
                printf("There exists an edge.\n");
            else
                printf("There doesn't exist an edge.\n");



        }
        else if(ch==4)
        {
            int u;
            scanf("%d",&u);
            if(g.getDegree(u)==NULL_VALUE)
                printf("This vertex doesn't exist\n");
            else
                printf("Degree of vertex %d is %d\n",u,g.getDegree(u));
        }

        else if(ch==5)
        {
            g.printGraph();
        }

        else if(ch==6)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            if(g.hasCommonAdjacent(u, v))
                printf("There exists common  edge.\n");
            else
                printf("There doesn't exist common edge.\n");
        }
        else if(ch==7)
        {
            int u, v;
            scanf("%d %d", &u, &v);
            int dis;
            dis=g.getDist(u,v);
            if(dis!=INFINITY)
                printf("The distance from %d to %d is : %d\n",u,v,dis);
            else
                printf("The distance from %d to %d is : INFINITY\n",u,v);

        }


        else if(ch==8)
        {
            break;
        }
    }
    //*/

    return 0;

}
