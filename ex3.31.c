#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 100
char a[MAXSIZE];
typedef struct Lnode{
    char data;
    struct Lnode *next;
}Lnode;
//³õÊ¼»¯Á´Õ»
void initStack(Lnode *ln){
    ln=(Lnode *)malloc(sizeof(Lnode));
    ln->next=NULL;
}
//ÅÐ¶ÏÁ´Õ»ÊÇ·ñÎª¿Õ
int StackEmpty(Lnode *ln){
    return (ln->next==NULL?1:0);
}
//½øÕ»
void push(Lnode *ln,char x){
    Lnode *p;
    p=(Lnode *)malloc(sizeof(Lnode));
    if(p ==NULL){
        printf("ERROR");
        exit(0);
    }
    p->next=NULL;
    p->data=x;
    p->next=ln->next;
    ln->next=p;
}
//³öÕ»
int pop(Lnode *ln,char *x){
    Lnode *p=ln->next;
    if(p ==NULL){
        return 0;
    }
    *x=p->data;
    ln->next=p->next;
    free(p);
    return 1;
}
void printStack(Lnode *ln){
    Lnode *p=ln->next;
    while(p!=NULL){
        printf("%d\n",p->data);
        p=p->next;
    }
}
void sym(char a[],int len);
void main(){
    Lnode ln;
    char x;
    int sign=0,i=0,len;
    initStack(&ln);
    while ((x=getchar())!='@')
    {
        a[i]=x;
        i++;
    }
    len=i;
    sym(a,len);
    return 0;
}
void sym(char a[],int len)
{
    int i;
    for (i=0;i<=len-1;i++)
    {
        if (a[i]!=a[len-1-i])
        {
            printf("0\n");
            return;
        }
    }
    printf("1\n");
}
