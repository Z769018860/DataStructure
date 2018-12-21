#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define MAXSIZE 100
typedef struct q_node
{
    char data;
    struct q_node *next;
}q_node,*link_node;
typedef struct l_queue
{
    q_node *front;
    q_node *rear;
}*link_queue;

link_queue initqueue(void);
int emptyqueue(link_queue q);
int enqueue(link_queue q,char e);
int dequeue(link_queue q,char *e);
void clearqueue(link_queue q);
void destroyqueue(link_queue q);
int getfront(link_queue q,char *e);
int getlen(link_queue q);
void traversequeue(link_queue q);
void visit(link_queue q);
link_queue initqueue(void)
{
    link_node newnode=(link_node)malloc(sizeof(q_node));
    newnode->next=NULL;
    link_queue q=(link_node)malloc(sizeof(*q));
    q->front=q->rear=newnode;
    return q;
}

int emptyqueue(link_queue q)
{
    return q->front==q->rear;
}

int enqueue(link_queue q,char e)
{
    link_node newnode=(link_node)malloc(sizeof(q_node));
    if (!newnode)
        return 0;
    newnode->data=e;
    q->rear->next=newnode;
    q->rear=newnode;
    return 1;
}

int dequeue(link_queue q,char *e)
{
    if (q->front==q->rear)
        return 0;
    *e=q->front->next->data;
    link_node temp=q->front->next;
    q->front->next=temp->next;
    if (temp==q->rear->next)
        q->rear=q->front;
    free(temp);
    temp=NULL;
    return 1;
}

void clearqueue(link_queue q)
{
    link_node head=q->front->next;
    head->next=NULL;
    q->front=q->rear=head;
    link_node temp=head->next;
    while(temp)
    {
        link_node p=temp;
        temp=p->next;
        free(p);
        p=NULL;
    }
}

void destroyqueue(link_queue q)
{
    clearqueue(q);
    free(q);
    q=NULL;
}

int getfront(link_queue q,char *e)
{
    if (q->front==q->rear)
        return 0;
    *e=q->front->next->data;
    link_node temp=q->front->next;
    q->front->next=temp->next;
    free(temp);
    temp=NULL;
    return 1;
}

int lenqueue(link_queue q)
{
    link_node p=q->front->next;
    int count=0;
    while(p)
    {
        count+=1;
        p=p->next;
    }
    return count;
}

void traversequeue(link_queue q)
{
    link_node p = q -> front -> next;
    if(!p)
    {
        printf("╤сапн╙©у");
    }
    while(p)
    {
        printf("%d ", p -> data);
        p = p -> next;
    }
    printf("\n");
    return;
}

int main()
{
    link_queue q=initqueue();
    /*enqueue(q,'a');
    enqueue(q,'b');
    printf("length=%d\n",lenqueue(q));
    enqueue(q,'c');
    printf("length=%d\n",lenqueue(q));
    enqueue(q,'d');
    printf("length=%d\n",lenqueue(q));
    traversequeue(q);
    char *e=(char*)malloc(sizeof(*e));
    dequeue(q,e);
    printf("dequeue(),e=%c length=%d\n",*e,lenqueue(q));*/
    char c;
    while ((c=getchar())!='@')
    {
        enqueue(q,c);
    }
    traversequeue(q);
    clearqueue(q);
    traversequeue(q);
    printf("length:%d\n",lenqueue(q));
    return 0;
}



