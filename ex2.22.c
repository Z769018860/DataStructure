#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
typedef struct node
{
    int data;
    struct node *next;
}Node,*va;

va createlist();
void traverselist(va);
void reverse(va vaHead);
int main()
{
    va vaHead=NULL;
    int data,i;
    int num1=0,num2=0,num;
    int choose;
    int return_val;
    int mink,mank;
    vaHead=createlist();
    traverselist(vaHead);
    reverse(vaHead);
    traverselist(vaHead);
    return 0;
}
va createlist()
{
    int i;
    int len;
    int val;
    int num;
    va vaHead=(va)malloc(sizeof(Node));
    va vaTail=vaHead;
    vaTail->next=NULL;
    scanf("%d",&len);
    for (i=0;i<len;i++)
    {
        scanf("%d",&val);
        va vaNew=(va)malloc(sizeof(Node));
        vaNew->data=val;
        vaTail->next=vaNew;
        vaNew->next=NULL;
        vaTail=vaNew;
    }
    return vaHead;
}
void traverselist(va vaHead)
{
    va v=vaHead->next;
    while(NULL!=v)
    {
        printf("%d",v->data);
        v=v->next;
    }
    printf("\n");
    return;
}
void reverse(va vaHead)
{
    va p,q;
    p=vaHead->next;
    vaHead->next=NULL;
    while(p)
    {
        q=p;
        p=p->next;
        q->next=vaHead->next;
        vaHead->next=q;
    }
}
