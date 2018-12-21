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
int insertnode(va,int,int);
int delnode(va,int);
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
    //scanf("%d",&data);
    scanf("%d%d",&mink,&mank);
    va pointer;
    pointer=vaHead;
    while (pointer!=NULL)
    {
        if (pointer->data<mink)
            num1++;
        if (pointer->data<mank)
            num2++;
        pointer=pointer->next;
    }
    //if (insertnode(vaHead,num,data)==1)
        //traverselist(vaHead);
    //else
        //printf("ERROR!\n");
        num=num2-num1+1;
    for(i=0;i<num;i++)
    {
        return_val=delnode(vaHead,num1+1);
        if (return_val==0)
        {
            printf("ERROR!\n");
        }
        else
        {
            traverselist(vaHead);
        }
    }

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
int insertnode(va vaHead,int front,int data)
{
    int i=0;
    va _node=vaHead;
    va vaSwap;
    if ((front<1)&&(NULL!=_node))
    {
        return 0;
    }
    while (i<front-1)
    {
        _node=_node->next;
        ++i;
    }
    va vaNew=(va)malloc(sizeof(Node));
    vaNew->data=data;
    vaSwap=_node->next;
    _node->next=vaNew;
    vaNew->next=vaSwap;
    return 1;
}
int delnode(va vaHead,int back)
{
    int i=0;
    int data;
    va _node=vaHead;
    va vaSwap;
    if ((back<1)&&(NULL==_node->next))
    {
        printf("ERROR!\n");
        return 0;
    }
    while (i<back-1)
    {
        _node=_node->next;
        ++i;
    }
    vaSwap=_node->next;
    data=vaSwap->data;
    _node->next=_node->next->next;
    free(vaSwap);
    return data;
}

