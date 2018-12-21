#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
typedef struct node
{
    int data;
    int freq;
    struct node *prior;
    struct node *next;
}Node,*va;
void Locate(va dl,char x);
va createlist();
void traverselist(va dl);
int main()
{
    int i;
    char x;
    va dl;
    dl=createlist();
    while(x!='#')
    {
        Locate(dl,x);
        x=getchar();
    }
    traverselist(dl);
    return 0;
}
va createlist()
{
    va head,p,e;
    char ch;
    head=(va)malloc(sizeof(Node));
    e=head;
    ch=getchar();
    while(ch!='#')
    {
        p=(va)malloc(sizeof(Node));
        p->data=ch;
        p->freq=0;
        p->prior=e;
        e->next=p;
        e=p;
        ch=getchar();
    }
    e->next=head;
    head->prior=e;
    return head;
}

void traverselist(va dl)
{
    va p;
    p=dl->next;
    while(p!=dl)
    {
        printf("%c %d\n",p->data,p->freq);
        p=p->next;
    }
    return;
}
void Locate(va dl,char x)
{
    va p;
    va current;
    p=dl->next;
    while(p!=dl && p->data!=x)
        p=p->next;

    if(p!=dl)
    {
        p->freq++;
        current=p;
        current->prior->next=current->next;
        current->next->prior=current->prior;
        p=current->prior;
        while(p!=dl && current->freq>p->freq)
            p=p->prior;

        current->next=p->next;
        current->prior=p;
        p->next->prior=current;
        p->next=current;
    }
    else
    {
        printf("Sorry.Not find!\n");
    }
}

