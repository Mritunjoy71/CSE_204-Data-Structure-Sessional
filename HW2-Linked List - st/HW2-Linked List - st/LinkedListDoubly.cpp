#include<stdio.h>
#include<stdlib.h>


#define NULL_VALUE -99999
#define SUCCESS_VALUE 99999

struct listNode
{
    int item;
    struct listNode * next;
    struct listNode * prev;
};

struct listNode * list;

struct listNode * tail;

void initializeList()
{
    list = 0;  //initially set to NULL
    tail = 0;
}
struct listNode * searchItem(int item)
{
    struct listNode * temp ;
    temp = list ; //start at the beginning
    while (temp != 0)
    {
        if (temp->item == item) return temp ;
        temp = temp->next ; //move to next node
    }
    return 0 ; //0 means invalid pointer in C, also called NULL value in C
}


///insesrtfirst




int insertFirst(int item) //insert at the beginning
{
    struct listNode * newNode ;
    newNode = (struct listNode*) malloc (sizeof(struct listNode)) ;
    newNode->item = item ;

    if(list==0) //inserting the first item
    {
        newNode->next = 0;
        newNode->prev = 0;
        list = newNode;
        tail = newNode;
    }
    else
    {
        newNode->next = list;
        list->prev = newNode;
        newNode->prev = 0;
        list = newNode;
    }
    return SUCCESS_VALUE ;
}



///inssertlast


int insertLast(int item)
{

    if(list==NULL) //If the list is empty
    {
        list=new listNode();
        list->item=item;
        list->next=NULL;
        list->prev=0;
        tail=list;
    }
    else
    {
        listNode *newnode=new listNode();
        newnode->item=item;
        newnode->next=NULL;
        newnode->prev=tail;
        tail->next=newnode; //add the new node after tail node
        tail=tail->next; //move tail pointer forward
    }
    return SUCCESS_VALUE ;
}


///insertbefore


int insertBefore(int oldItem, int newItem)
{
    struct listNode *temp;
    temp=searchItem(oldItem);
    if(temp==list)
    {
        insertFirst(newItem);

    }

    else if(temp!=0)
    {

        struct listNode * newNode ;
        newNode = (struct listNode*) malloc (sizeof(struct listNode)) ;
        newNode->item = newItem ;
        newNode->next=temp;
        newNode->prev=temp->prev;
        temp->prev->next=newNode;
        temp->prev=newNode;




    }
    else
    {
        insertFirst(newItem);

    }
    return 0;

}



///deleteafter

int deleteAfter(int item)
{
    if(list==0)
        printf("Empty list\n");
    else
    {
        struct listNode * temp;
        temp=searchItem(item);                    //14 15 17 19

        if(temp==tail)
            printf("No deletion done.\n");
        else if(temp && temp->next->next==0)
        {
            struct listNode *temp2;
            temp2=temp->next;
            temp->next=0;
            tail=temp;
            free(temp2);
            printf("deletion done.\n");

        }
        else if(temp && temp->next!=0)
        {
            struct listNode *temp2;
            temp2=temp->next;
            temp->next=temp2->next;
            temp2->next->prev=temp;
            free(temp2);
            printf("deletion done.\n");

        }

        else
            printf("No deletion done.\n");
    }
    return 0;
}



///delete


int deleteItem(int item)
{
    if(list==0)
    {
        printf("List is empty\n");
    }
    else
    {
        struct listNode *temp ;
        temp = searchItem(item);
        if (temp == 0)
        {
            printf("item not found to delete\n");
            return NULL_VALUE ;
        }
        else if (temp == list) //delete the first node
        {

            list = list->next ;
            list->prev=0;
            free(temp) ;
        }
        else if(temp==tail)
        {
            tail->prev->next=0;
            tail=tail->prev;
            free(temp);
        }
        else
        {

            temp->prev->next=temp->next;
            temp->next->prev=temp->prev;
            free(temp);
        }
    }
    return SUCCESS_VALUE ;
}

///deletelast


int deleteLast()
{
    if(list==0)
    {
        printf("List is empty.\n");
        return SUCCESS_VALUE ;
    }
    else
    {
        struct listNode *temp;
        if(list->next==0)
        {
            temp=list;
            list=0;
            tail=0;
            free(temp);
        }
        else if(list->next==tail)
        {
            temp=tail;
            list->next=0;
            tail=list;
            free(temp);
        }
        else
        {
            tail->prev->next=0;
            temp=tail;                         ///15 66
            tail=tail->prev;

            free(temp);
        }
    }

}


///print



void printListForward()
{
    if(list==0)
        printf("List is empty");
    else
    {
        struct listNode * temp;
        temp = list;
        while(temp!=0)
        {
            printf("%d->", temp->item);
            temp = temp->next;
        }

    }
    printf("\n");

}

void printListBackward()
{

    if(list==0)
        printf("List is empty");
    else
    {
        struct listNode * temp;
        temp = tail;
        while(temp!=0)
        {
            printf("%d->", temp->item);
            temp = temp->prev;
        }
    }
    printf("\n");


}

///main


int main(void)
{
    initializeList();
    printf("1. Insert new item. 2.Insert last 3. Delete item after. 4. Search item.\n");
    printf("5. Delete last item 6. Print forward. 7. Print backward.\n 8. Insert before  9. delete item 10. exit.\n");
    printf("enter your choice\n");
    while(1)
    {

        int ch;
        scanf("%d",&ch);
        if(ch==1)
        {
            int item;
            scanf("%d", &item);
            insertFirst(item);
        }
        else if(ch==2)
        {
            int item;
            scanf("%d", &item);
            insertLast(item);
        }
        else if(ch==3)
        {
            int item ;
            scanf("%d",&item);
            deleteAfter(item);
        }
        else if(ch==4)
        {
            int item;
            scanf("%d", &item);
            struct listNode * res = searchItem(item);
            if(res!=0) printf("Found.\n");
            else printf("Not found.\n");
        }
        else if(ch==5)
            deleteLast();

        else if(ch==6)
        {
            printListForward();
        }
        else if(ch==7)
        {
            printListBackward();
        }
        else if(ch==8)
        {
            int olditem,newitem ;
            scanf("%d %d",&olditem,&newitem);
            insertBefore(olditem,newitem);

        }
        else if(ch==9)
        {
            int item;
            scanf("%d",&item);
            deleteItem(item);
        }

        else if(ch==10)
        {
            break;
        }

    }

}
