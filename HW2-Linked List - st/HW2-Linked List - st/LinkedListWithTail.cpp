#include<stdio.h>
#include<stdlib.h>

#define NULL_VALUE -99999
#define SUCCESS_VALUE 99999



struct listNode
{
    int item;
    struct listNode * next;
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

    if(list==0)
        return 0;
    temp = list ; //start at the beginning


    while (temp != 0)
    {
        if (temp->item == item) return temp ;
        temp = temp->next ; //move to next node
    }


    return 0 ; //0 means invalid pointer in C, also called NULL value in C



}





void printList()
{


    struct listNode * temp;
    temp = list;
    if(!temp)
        printf("Empty list");




    while(temp!=0)
    {
        printf("%d->", temp->item);
        temp = temp->next;
    }


    printf("\n");


}





int insertItem(int item) //insert at the beginning of the linked list
{


    if(list==0)
    {
        listNode *newnode=new listNode();
        newnode->item=item;
        newnode->next=list;
        list=newnode;
        tail=list;


    }



    else
    {
        listNode *newnode=new listNode();
        newnode->item=item;
        newnode->next=list;
        list=newnode;


    }



    return SUCCESS_VALUE ;
}

int insertLast(int item)
{



    if(list==NULL) //If the list is empty
    {
        list=new listNode();
        list->item=item;
        list->next=NULL;
        tail=list;
    }


    else
    {
        listNode *newnode=new listNode();
        newnode->item=item;
        newnode->next=NULL;
        tail->next=newnode; //add the new node after tail node
        tail=tail->next; //move tail pointer forward
    }


    return SUCCESS_VALUE ;
}


int deleteItem(int item)
{


    if(list==0)
    {
        printf("List is empty\n");
    }


    else
    {
        struct listNode *temp, *prev ;
        temp = list ; //start at the beginning


        while (temp != 0)
        {
            if (temp->item == item)
            {
                break ;

            } //move to next node
            prev = temp;
            temp = temp->next ;
        }


        if (temp == 0)
        {
            printf("item not found to delete\n");
            return NULL_VALUE ;
        }


        else if (temp == list) //delete the first node
        {
            list = list->next ;
            free(temp) ;
        }


        else if(temp==tail)
        {
            prev->next=0;
            tail=prev;
            free(temp);
        }



        else
        {
            prev->next = temp->next ;
            free(temp);
        }
    }

    return SUCCESS_VALUE ;
}






int insertBefore(int oldItem, int newItem)
{


    struct listNode * temp;
    temp=searchItem(oldItem);
    if(temp==list)
    {
        insertItem(newItem);

    }

    else if(temp!=0)
    {
        listNode *current_node=list;


        while(current_node->next!=temp)
        {
            current_node=current_node->next;
        }


        struct listNode * newNode ;
        newNode = (struct listNode*) malloc (sizeof(struct listNode)) ;
        newNode->item = newItem ;
        newNode->next=temp;
        current_node->next=newNode;


    }
    else
    {
        insertItem(newItem);

    }
    return 0;

}






int deleteAfter(int item)
{
    if(list==0)
        printf("Empty list\n");


    else
    {
        struct listNode * temp;
        temp=searchItem(item);                    //14 15

        if(temp==tail)
            printf("No deletion done");


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
            free(temp2);
            printf("deletion done.\n");

        }

        else
            printf("No deletion done.\n");
    }
    return 0;
}



int deleteLast()
{

    if(list==0){
        printf("List is empty\n");
        return NULL_VALUE ;
    }


    else if(list->next==0)
    {
        struct listNode *temp;
        temp=list;
        list=0;
        tail=0;
        free(temp);

    }
    else
    {
        struct listNode *currNode,*prev ;
        currNode=list;

        while (currNode->next!=0)
        {
            prev=currNode;
            currNode = currNode->next;
        }

        prev->next=0;
        tail=prev;
        free(currNode);

    }
    return SUCCESS_VALUE ;

}



int main(void)
{
    initializeList();
    printf("1. Insert new item at first.   2. Delete item.\n");
    printf("3. Search item.   4. Insert new item at last.\n");
    printf("5. Insert before a definite item.    6. Delete after item.\n");
    printf("7.Delete Last item.   8.Print.  9. exit.\n");
    while(1)
    {


        int ch;
        scanf("%d",&ch);
        if(ch==1)
        {
            int item;
            scanf("%d", &item);
            insertItem(item);
        }
        else if(ch==2)
        {
            int item;
            scanf("%d", &item);
            deleteItem(item);
        }
        else if(ch==3)
        {
            int item;
            scanf("%d", &item);
            struct listNode * res = searchItem(item);
            if(res!=0) printf("Found.\n");
            else printf("Not found.\n");
        }
        else if(ch==4)
        {
            int item;
            scanf("%d", &item);
            insertLast(item);
        }

        else if(ch==5)
        {
            int newItem,oldItem;
            scanf("%d %d", &oldItem,&newItem);
            insertBefore(oldItem,newItem);
        }
        else if(ch==6)
        {
            int item;
            scanf("%d", &item);
            deleteAfter(item);
        }
        else if(ch==7)
        {

            deleteLast();
        }
        else if(ch==8)
        {
            printList();
        }
        else if(ch==9)
        {
            break;
        }
    }

}
