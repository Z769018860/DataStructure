#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define MAXSIZE 100
typedef struct q_node
{
    char data;
    struct q_node *next;
}q_node,*link_node;

link_node initqueue()
{
    link_node q;
    q=(link_node)malloc(sizeof(q_node));
    q->next=q;
    return q;
}
void enqueue(link_node q,char x)
{
    link_node p;
    p=(link_node)malloc(sizeof(q_node));
    p->data=x;
    p->next=q->next;
    q->next=p;
    q=p;
}

int dequeue(link_node q,char x)
{
    if(q==q->next)
        return 0;
    link_node p;
    p=q->next->next;
    x=p->data;
    q->next->next=p->next;
    free(p);
    return 1;
}

void traversequeue(link_node q)
{
    link_node p = q-> next;
    while(p!=NULL)
    {
        printf("%c", p -> data);
        p = p -> next;
    }
    printf("\n");
    return;
}
int main()
{
    link_node q=initqueue();

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
    scanf("%c",c);
    dequeue(q,c);
    traversequeue(q);
    return 0;
}



