#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<iostream>
using namespace std;
#define MAX 100
#define RMAX 10
typedef char Type;
typedef struct BiNode{		//二叉链表
	Type data;
	BiNode *lchild,*rchild;
}BiNode,*BiTree;

typedef struct {	//队列
	BiTree *base;
	int front;
	int rear;
	int tag;
}Sq;


typedef struct{		//栈
	BiTree *base;
	int top;
	int size;
}Stack;

int  Gettop(Stack S,BiTree &e);
void Pop(Stack &S,BiTree &e);
void Push(Stack &S,BiTree e);
int Isempty(Stack S);
void InitStack(Stack &S);

void InitSq(Sq &QQ);
int Getlen(Sq QQ);
int Isempty(Sq QQ);
void InSq(Sq &QQ,BiTree e);
void OutSq(Sq &QQ,BiTree &e);
void GetHead(Sq QQ);

void Crea_BiTree(BiTree &Bt); //use #
void PreOrder(BiTree bt);	//先序非递归
void InOrder(BiTree Bt);	//中序递归
void InOrderT(BiTree bt);	//中序非递归

int IsCompleteTree(BiTree Bt)
{
	Sq q;BiTree e;
	InitSq(q);
	InSq(q,Bt);//根节点入队列
	OutSq(q,e);
	while(e!= NULL)//遇到空前，持续出队
	{
		InSq(q,e->lchild);//不管是不是NULL，左孩子先入队
		InSq(q,e->rchild);//右孩子入队
		OutSq(q,e);
	}
	while(!Isempty(q))//如果队列非空，留在里面的必定全是 NULL
	{
		OutSq(q,e);
		if(e!=NULL)//有一个不是 NULL 则判定不是完全二叉树
		{
			return 0;
		}
	}
	return 1;
}


int main()
{
	BiTree Bt;
	printf("用#+先序遍历输入\n");
	Crea_BiTree(Bt);

	if(IsCompleteTree(Bt))
		printf("yes\n");
	else
		printf("no\n");



	return 0;
}

void InOrder(BiTree Bt)		//中序递归
{//二叉树bt采用二叉链表存储，对bt进行中序遍历
	if(Bt)
    {
		InOrder(Bt->lchild);
        printf("%3c",Bt->data);     //访问根结点
        InOrder(Bt->rchild);
    }
}// InOrderTraverse

void InOrderT(BiTree bt)	//中序非递归
{//对bt进行中序遍历
	BiTree p;
	Stack S;
	if(bt){
       InitStack(S);   Push(S, bt);       //根节点进栈
       while(!Isempty(S))
	   {
            while(Gettop(S,p)&&p)
                   Push(S, p->lchild);    //向左一直走到头
            Pop(S, p);	    //空指针出栈
            if(!Isempty(S))
	   		{
			   Pop(S,p);
			   printf("%3c",p->data);  Push(S, p->rchild);
			}
       }
	}
}

void PreOrder(BiTree bt)
{
//二叉树bt采用二叉链表存储，对bt进行先序遍历
	printf("非递归先序遍历\n");
	Stack S;
	BiTree p;
	if(bt)
	{
	    InitStack(S);   Push(S, bt);     //根指针进栈
	    while(!Isempty(S))
		{
	        while(Gettop(S,p) && p) {
	            printf("%3c",p->data);
				Push(S,p->lchild);
			}   //向左一直走到尽头
	        Pop(S, p);	    //空指针退栈
	        if(!Isempty(S))
	        {
				Pop(S,p);	Push(S, p->rchild);
			}
	    }
	}
}

void Crea_BiTree(BiTree &Bt) //use #
{
	char ch;
	ch=getchar();
	if(ch=='#')
		Bt=NULL;
	else
	{
		Bt=(BiTree)malloc(sizeof(BiNode));
		Bt->data=ch;
		Crea_BiTree(Bt->lchild);
		Crea_BiTree(Bt->rchild);
	}
}


//初始化
void InitStack(Stack &S)
{
	S.base=(BiTree*)malloc(MAX*sizeof(BiTree));
	if(!S.base)
		return ;
	S.top=0;
	S.size=MAX;
}
//判空操作，返回 1 表示栈为空
int Isempty(Stack S)
{
	if(S.top==0)
		return 1;
	return 0;
}
//入栈操作
void Push(Stack &S,BiTree e)
{
	if(S.top>=S.size)
	{
		printf("该栈已满\n");
		return ;
	}

	S.base[S.top++]=e;
}
//出栈操作
void Pop(Stack &S,BiTree &e)
{
	if (Isempty(S))    return;     //栈为空
    e = S.base[--S.top];
}
//Gettop 取栈顶元素
int  Gettop(Stack S,BiTree &e){
 //若栈不空则用e返回S的栈顶元素

   if (S.top == 0)
         return 0;      //栈为空
   e = S.base[S.top-1];
   return 1;
}
	//	队列 	*******************************
void InitSq(Sq &QQ)
{
	QQ.base=(BiTree *)malloc(MAX * sizeof(BiTree));	//S.base=(BiTree*)malloc(MAX*sizeof(BiTree));
	if(!QQ.base)
		return ;
	QQ.front=QQ.rear=QQ.tag=0;
}

int Getlen(Sq QQ)
{
	if(!QQ.tag)		//分情况讨论tag为 0，长度肯定为 0；
		return 0;
	else
	{
		if(QQ.rear==QQ.front)
			return MAX;
		return (QQ.rear-QQ.front+MAX)%MAX;
	}

}

int Isempty(Sq QQ)
{
	if(QQ.front==QQ.rear && QQ.tag==0)
		return 1;
	return 0;
}

void InSq(Sq &QQ,BiTree e)
{

	if (QQ.front == QQ.rear && QQ.tag==1)	//tag与队头队尾必须同时满足
	{
		printf("%d\n",QQ.tag);
		printf("队列已满\n");
		return ;
	}
	QQ.tag=1;
	//	Q.base=(Type )malloc(MAX * sizeof(Type));
    QQ.base[QQ.rear] = e;
    QQ.rear =(QQ.rear+1)%MAX;
}
void OutSq(Sq &QQ,BiTree &e)
{
	if(QQ.front == QQ.rear && QQ.tag==0)
	{
		printf("队列已空\n");
		return;
	}
	e=QQ.base[QQ.front];
	QQ.front=(QQ.front+1)%MAX;
	if(QQ.front == QQ.rear)
		QQ.tag=0;
}

void GetHead(Sq QQ,BiTree e)
{
    if(QQ.front == QQ.rear && QQ.tag==0) return;
    e = QQ.base[QQ.front];
}
