#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 100
char a[MAXSIZE],b[MAXSIZE];
typedef struct Lnode{
    char data;
    struct Lnode *next;
}Lnode;
//��ʼ����ջ
void initStack(Lnode *ln){
    ln=(Lnode *)malloc(sizeof(Lnode));
    ln->next=NULL;
}
//�ж���ջ�Ƿ�Ϊ��
int StackEmpty(Lnode *ln){
    return (ln->next==NULL?1:0);
}
//��ջ
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
//��ջ
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
void sym(char a[],char b[],int len);
void main(){
    Lnode ln;
    char x;
    int sign=0,i=0,len;
    initStack(&ln);
    while ((x=getchar())!='@')
    {
        if (x=='&')
        {
            sign=1;
            len=i;
            i=0;
        }
        if (sign==0)
        {
            a[i]=x;
            i++;
        }
        else if (x!='&')
        {
            b[i]=x;
            i++;
        }
    }
    sym(a,b,len);
    return 0;
}
void sym(char a[],char b[],int len)
{
    int i;
    for (i=0;i<=len-1;i++)
    {
        if (a[i]!=b[len-1-i])
        {
            printf("0\n");
            return;
        }
    }
    printf("1\n");
}
