#include<stdio.h>
#include<stdlib.h>
#include <iostream>
#define MAXLEN 1000
using namespace std;
typedef struct LNode{
    int data;
    struct LNode *next;
}LNode,*LinkList;
LinkList createlist();
int va[MAXLEN];
int mink,maxk;
int i=0;
int main(void)
{
    while(cin >> va[i]){
        i++;
    }
    mink=va[i-2];
    maxk=va[i-1];
    LinkList vaHead=NULL;
    vaHead=createlist();
    return 0;
}

LinkList createlist()
{
    LinkList L;
    L = (LinkList)malloc(sizeof(LNode));

    LNode *p,*q,*s;
    q=L;
    L->data = 0;
    L->next = NULL;

    i=i-2;
    int j;

    for(j=0;j<=i-1;j++){
        p=(LNode*)malloc(sizeof(LNode));

        q->next = p;
        q = p;
        p->data = va[j];
        p->next = NULL;
    }

    q=L;
    p=q->next;
    while(p && p->data<=mink){
        q=p;
        p=p->next;
    }
    while(p && p->data<maxk){
        s=p;
        q->next=p->next;
        p=p->next;
        free(s);
    }
        for(p=L->next;p;p=p->next){
        printf("%d",p->data);
        if(p->next)
            printf(" ");
    }
    return p;
}
