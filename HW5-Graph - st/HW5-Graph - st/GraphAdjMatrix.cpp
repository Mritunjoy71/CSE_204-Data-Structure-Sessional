#include<stdio.h>
#include<stdlib.h>
#define NULL_VALUE -999999
#define INFINITY 999999
#define WHITE 1
#define GRAY 2
#define BLACK 3


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


//******************Graph class starts here**************************
class Graph
{
    int nVertices, nEdges ;
    bool directed ;
    int ** matrix ; //adjacency matrix to store the graph
    int *color;
    int *parent;
    int *dist;
    int *start;
    int *finish;
    int time;

public:
    Graph(bool dir = true);
    ~Graph();
    void setnVertices(int n);
    void addEdge(int u, int v);
    void removeEdge(int u, int v);
    bool isEdge(int u, int v);
    int getDegree(int u);
    bool hasCommonAdjacent(int u, int v);
    int getDist(int u, int v);
    void printGraph();
    void bfs(int source); //will run bfs in the graph
    void dfs();
    void visit_dfs(int u);
};


Graph::Graph(bool dir)
{
    nVertices = 0 ;
    nEdges = 0 ;
    matrix = 0 ;
    directed = dir ; //set direction of the graph
    color=0;
    parent=0;
    dist=0;
    start=0;
    finish=0;

}

void Graph::setnVertices(int n)
{
    this->nVertices = n ;

    //allocate space for the matrix
    matrix = new int*[nVertices];
    for(int i=0; i<nVertices; i++)
    {
        matrix[i] = new int[nVertices];
        for(int j=0; j<nVertices; j++)
            matrix[i][j] = 0; //initialize the matrix cells to 0
    }
    color=new int[n];
    parent=new int [n];
    dist=new int[n];
    start=new int[n];
    finish=new int[n];

}

void Graph::addEdge(int u, int v)
{

    matrix[u][v] = 1;
    if(!directed) matrix[v][u] = 1;

}

void Graph::removeEdge(int u, int v)
{

    matrix[u][v]=0;
    if(!directed) matrix[v][u] = 0;


}

bool Graph::isEdge(int u, int v)
{

    if(matrix[u][v]==1)
        return true;
    else
        return false;
}

int Graph::getDegree(int u)
{
    int nd=0;
    if(!directed)
    {
        for(int i=0; i<nVertices; i++)
        {
            if(matrix[u][i]==1)
                nd++;
        }
    }
    else
    {

        for(int i=0; i<nVertices; i++)
        {
            if(matrix[u][i]==1)
                nd++;
            if(matrix[i][u]==1)
                nd++;

        }

    }
    return nd;
}

bool Graph::hasCommonAdjacent(int u, int v)
{
    for (int i=0; i<nVertices; i++)
    {
        if(matrix[u][i]==1)
            if(matrix[v][i]==1)
            {
                return true;
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
        for(int j=0; j<nVertices; j++)
        {
            if(matrix[u][j]==1)
            {
                if(color[j]==WHITE)
                {
                    color[j]=GRAY;
                    dist[j]=dist[u]+1;
                    parent[j]=u;
                    q.enqueue(j);
                }
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
    for(int j=0; j<nVertices; j++)
    {
        if(matrix[u][j]==1)
        {
            if(color[j]==WHITE)
            {

                parent[j]=u;
                visit_dfs(j);
            }
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
    dfs();
    printf("\nNumber of vertices: %d, Number of edges: %d\n", nVertices, nEdges);
    for(int i=0; i<nVertices; i++)
    {
        printf("%d:", i);
        for(int j=0; j<nVertices; j++)
        {
            if(matrix[i][j]==1)
                printf(" %d", j);
        }
        printf("\t");
        printf(":(%d/%d)\n",start[i],finish[i]);
    }
}

Graph::~Graph()
{
    if(matrix) delete[] matrix;
    matrix=0;
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

}

//**********************Graph class ends here******************************


//******main function to test your code*************************
int main(void)
{
    int i,n,m;
    Graph g;
   // printf("Enter number of vertices: ");
    scanf("%d", &n);
    g.setnVertices(n);
    scanf("%d",&m);
    for(i=0;i<m;i++)


    /*
    while(1)
    {
        printf("1. Add edge.");
        printf("2. remove edge   3. Is edge   4. get degree\n5. Print Graph 6. common edge  7. get distance  8. Exit.\n");

        int ch;
        scanf("%d",&ch);
        if(ch==1)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            if(u<0 || u>=n || v<0 || v>=n)
                printf("wrong input\n");
            else

                g.addEdge(u, v);
        }
        else if(ch==2)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            if(u<0 || u>=n || v<0 || v>=n)
                printf("wrong input\n");
            else
                g.removeEdge(u, v);

        }
        else if(ch==3)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            if(u<0 || u>=n || v<0 || v>=n)
                printf("wrong input\n");
            else
            {
                if(g.isEdge(u, v))
                    printf("There exists an edge.\n");
                else
                    printf("There doesn't exist an edge.\n");
            }



        }
        else if(ch==4)
        {
            int u;
            scanf("%d",&u);
            if(u<0 || u>=n )
                printf("wrong input\n");
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
            if(u<0 || u>=n|| v<0 || v>=n)
                printf("wrong input\n");
            else
            {
                if(g.hasCommonAdjacent(u, v))
                    printf("There exists common  edge.\n");
                else
                    printf("There doesn't exist common edge.\n");
            }
        }
        else if(ch==7)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            if(u<0 || u>=n || v<0 || v>=n)
                printf("wrong input\n");
            else
            {
                if(g.getDist(u,v)==INFINITY)
                    printf("Distance between %d to %d is:INFINITY\n",u,v);
                else
                    printf("Distance between %d to %d is:%d\n",u,v,g.getDist(u,v));
            }
        }
        else if(ch==8)
        {
            break;
        }
    }      */

}
