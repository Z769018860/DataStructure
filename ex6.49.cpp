#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<iostream>
using namespace std;
#define MAX 100
#define RMAX 10
typedef char Type;
typedef struct BiNode{		//��������
	Type data;
	BiNode *lchild,*rchild;
}BiNode,*BiTree;

typedef struct {	//����
	BiTree *base;
	int front;
	int rear;
	int tag;
}Sq;


typedef struct{		//ջ
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
void PreOrder(BiTree bt);	//����ǵݹ�
void InOrder(BiTree Bt);	//����ݹ�
void InOrderT(BiTree bt);	//����ǵݹ�

int IsCompleteTree(BiTree Bt)
{
	Sq q;BiTree e;
	InitSq(q);
	InSq(q,Bt);//���ڵ������
	OutSq(q,e);
	while(e!= NULL)//������ǰ����������
	{
		InSq(q,e->lchild);//�����ǲ���NULL�����������
		InSq(q,e->rchild);//�Һ������
		OutSq(q,e);
	}
	while(!Isempty(q))//������зǿգ���������ıض�ȫ�� NULL
	{
		OutSq(q,e);
		if(e!=NULL)//��һ������ NULL ���ж�������ȫ������
		{
			return 0;
		}
	}
	return 1;
}


int main()
{
	BiTree Bt;
	printf("��#+�����������\n");
	Crea_BiTree(Bt);

	if(IsCompleteTree(Bt))
		printf("yes\n");
	else
		printf("no\n");



	return 0;
}

void InOrder(BiTree Bt)		//����ݹ�
{//������bt���ö�������洢����bt�����������
	if(Bt)
    {
		InOrder(Bt->lchild);
        printf("%3c",Bt->data);     //���ʸ����
        InOrder(Bt->rchild);
    }
}// InOrderTraverse

void InOrderT(BiTree bt)	//����ǵݹ�
{//��bt�����������
	BiTree p;
	Stack S;
	if(bt){
       InitStack(S);   Push(S, bt);       //���ڵ��ջ
       while(!Isempty(S))
	   {
            while(Gettop(S,p)&&p)
                   Push(S, p->lchild);    //����һֱ�ߵ�ͷ
            Pop(S, p);	    //��ָ���ջ
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
//������bt���ö�������洢����bt�����������
	printf("�ǵݹ��������\n");
	Stack S;
	BiTree p;
	if(bt)
	{
	    InitStack(S);   Push(S, bt);     //��ָ���ջ
	    while(!Isempty(S))
		{
	        while(Gettop(S,p) && p) {
	            printf("%3c",p->data);
				Push(S,p->lchild);
			}   //����һֱ�ߵ���ͷ
	        Pop(S, p);	    //��ָ����ջ
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


//��ʼ��
void InitStack(Stack &S)
{
	S.base=(BiTree*)malloc(MAX*sizeof(BiTree));
	if(!S.base)
		return ;
	S.top=0;
	S.size=MAX;
}
//�пղ��������� 1 ��ʾջΪ��
int Isempty(Stack S)
{
	if(S.top==0)
		return 1;
	return 0;
}
//��ջ����
void Push(Stack &S,BiTree e)
{
	if(S.top>=S.size)
	{
		printf("��ջ����\n");
		return ;
	}

	S.base[S.top++]=e;
}
//��ջ����
void Pop(Stack &S,BiTree &e)
{
	if (Isempty(S))    return;     //ջΪ��
    e = S.base[--S.top];
}
//Gettop ȡջ��Ԫ��
int  Gettop(Stack S,BiTree &e){
 //��ջ��������e����S��ջ��Ԫ��

   if (S.top == 0)
         return 0;      //ջΪ��
   e = S.base[S.top-1];
   return 1;
}
	//	���� 	*******************************
void InitSq(Sq &QQ)
{
	QQ.base=(BiTree *)malloc(MAX * sizeof(BiTree));	//S.base=(BiTree*)malloc(MAX*sizeof(BiTree));
	if(!QQ.base)
		return ;
	QQ.front=QQ.rear=QQ.tag=0;
}

int Getlen(Sq QQ)
{
	if(!QQ.tag)		//���������tagΪ 0�����ȿ϶�Ϊ 0��
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

	if (QQ.front == QQ.rear && QQ.tag==1)	//tag���ͷ��β����ͬʱ����
	{
		printf("%d\n",QQ.tag);
		printf("��������\n");
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
		printf("�����ѿ�\n");
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
