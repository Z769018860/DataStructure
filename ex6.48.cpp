#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define ERROR 0
#define OK 1
#define STACK_INIT_SIZE 100 //栈的存储空间初始分配量
#define STACKINCREMENT 10 //栈的存储空间初始分配增量

typedef int Status;
typedef int TElemType;
typedef struct BiTNode
{
  TElemType data;
  struct BiTNode *lchild,*rchild;
}BiTNode,*BiTree;//二叉树的二叉链表储存结构

typedef struct
{
  TElemType data;//保存当前输入的结点的数据域
  char child;//child='D' 表示该结点有左右孩子；child='L' 表示该结点仅有左孩子
             //child='R' 表示该结点仅有右孩子；child='O' 表示该结点无左右孩子
}NodeStatus;

typedef BiTNode **QElemType;
typedef struct QNode
{
  QElemType data;
  struct QNode *next;
}QNode,*QueuePtr;
//队列的结点结构
typedef struct
{
  QueuePtr front;//队头指针，这里指向队列的头结点（是带头结点的队列）
  QueuePtr rear;//队尾指针，指向队尾元素
}LinkQueue;
//单链队列，队列的链式储存结构



Status InitQueue(LinkQueue *LQ)
{//构造一个空队列,只有头结点
  if(!(LQ->front=(QueuePtr)malloc(sizeof(QNode)))) return ERROR;//生成头结点
  LQ->front->next=NULL;
  LQ->rear=LQ->front;
  return OK;
}//InitQueue

Status EnQueue(LinkQueue *LQ,QElemType e)
{//插入元素e为队列*LQr队尾元素
  QNode *p;
  if(!(p=(QNode*)malloc(sizeof(QNode)))) return ERROR;
  p->data=e;
  p->next=NULL;
  LQ->rear->next=p;
  LQ->rear=p;
  return OK;
}//EnQueue

Status DeQueue(LinkQueue *LQ,QElemType *e)
{//若队列不空，则删除队头元素（即首元结点），并用*e返回结果；否则函数返回ERROR
  if(LQ->front==LQ->rear) return ERROR;
  *e=LQ->front->next->data;
  LQ->front->next=LQ->front->next->next;//队头元素出队列
  if(LQ->front->next==NULL)     //哦，原来这里出错了××××××
 LQ->rear=LQ->front;//若队列变为空，则修改队尾指针
  return OK;
}//DeQueue

Status DestroyQueue(LinkQueue *LQ)
{//销毁队列
 QNode *p;
  while(LQ->front!=LQ->rear)
  {
 p=LQ->front->next;
 LQ->front->next=LQ->front->next->next;
    if(LQ->front->next==NULL)
   LQ->rear=LQ->front;//若队列变为空，则修改队尾指针
 free(p);
  }//while
  free(LQ->front);//释放队头结点
  return OK;
}//DestroyQueue






Status CreateBiTree(BiTree *T,char *s)
{//按层次顺序（从上自下，同一层次从左至右）输入二叉树中结点的值以及该结点拥有的孩子的情况
 //构造二叉链表表示的二叉树T；若s="NULL",表示构造一棵空二叉树，若s="NOTNULL" 表示二叉树非空
  if(T==NULL ||(strcmp(s,"NULL") && strcmp(s,"NOTNULL"))) return ERROR;//参数非法,入口断言

  if(!strcmp(s,"NULL"))
  {//构造空树
    *T=NULL;
 printf("构造了一个空二叉树！\n");
 return OK;
  }//if

  //若能来到这里，表明构造一个非空二叉树
  printf("构造一个非空二叉树！\n");

  NodeStatus NS;//保存当前输入的结点的值以及该结点拥有的孩子的情况
  LinkQueue LQ;//定义一个辅助队列
  InitQueue(&LQ);//构造一个只有头结点的空队列
  EnQueue(&LQ,T);//初始化队列元素
  QElemType p;//用p返回队头元素中的数据域
  char c=' ';//输助变量，用以确定输入的二叉树的结点是否结束；循环初始化字符c

  while(c!='/n')
  {
    scanf("%d %c",&(NS.data),&(NS.child));
 //printf("NS.data=%d  NS.child=%c/n",NS.data,NS.child );

    DeQueue(&LQ,&p);//取队头元素的数据域，并使队头元素出队列
 if(!((*p)=(BiTNode*)malloc(sizeof(BiTNode)))) return ERROR;
 //生成一个结点
 (*p)->data=NS.data;//二叉树中该结点的值
 //printf("(*p)->data=%d/n",(*p)->data);

    (*p)->lchild=NULL;//这里不能漏的吧
    (*p)->rchild=NULL;//这里不能漏的吧

 if(NS.child=='D')
 {//该结点有左右孩子
   EnQueue(&LQ,&((*p)->lchild));
      EnQueue(&LQ,&((*p)->rchild));
 }//if NS.child=='D'
    else if(NS.child=='L')
 {//该结点仅有左孩子
   EnQueue(&LQ,&((*p)->lchild));
 }// else if NS.child=='L'
 else if(NS.child=='R')
 {//该结点仅有右孩子
   EnQueue(&LQ,&((*p)->rchild));
 }//else if NS.child=='R'

 c=getchar();

  }//while

  DestroyQueue(&LQ);

  return OK;
}//CreateBiTree

Status VisitNode(BiTNode *p)
{//访问二叉树中结点的数据域
  if(p==NULL) return ERROR;
  printf("%d ",p->data);
  return OK;
}//VisitNode

Status PreOrderTraverse(BiTree T,Status (*V)(BiTNode *))
{//先序遍历二叉树
  if(T==NULL) return OK;
  if((*V)(T))
    if(PreOrderTraverse(T->lchild,V))
   if(PreOrderTraverse(T->rchild,V))
    return OK;
  return ERROR;
}//PreOrderTraverse

Status PreOrderTraverse_2(BiTree T,TElemType e,BiTNode **p)
{//先序遍历二叉树,若找到一个结点的值与e 相等，则用*p指针返回这个结点的地址；否则函数返回ERROR
  if(T==NULL) return ERROR;
  if(T->data ==e)
  {
 *p=T;
  }//if
  else
  {
 if(!(PreOrderTraverse_2(T->lchild,e,p)))
   if(!(PreOrderTraverse_2(T->rchild,e,p)))
    return ERROR;
  }//else
  return OK;
}//PreOrderTraverse


typedef struct
{
  BiTNode *data;
  int tag;
}SElemType;//栈元素结点结构

typedef struct
{
  SElemType *base; //栈底指针，在栈构造之前和销毁之后，base的值为 NULL
  SElemType *top;  //栈顶指针，指向栈项元素的下一位
  int stacksize;   //当前已分配的存储空间，以元素SElemType为单位
}SqStack;          //栈的顺序存储表示

Status InitStack(SqStack *S)
{//构造一个空栈
  if(S==NULL) return ERROR;//参数非法
  if(!(S->base=(SElemType*)malloc(sizeof(SElemType)*STACK_INIT_SIZE))) return ERROR;
  //分栈的初始空间
  S->top=S->base;//初始化栈为空栈
  S->stacksize=STACK_INIT_SIZE;
  return OK;
}//InitStack


Status PushStack(SqStack *S,BiTNode *data,int tag)
{//插入一个栈顶元素，并以data和tag为新的栈顶元素的数据域
  if(S->top-S->base==S->stacksize)
  {//栈满
    if(!(S->base=(SElemType*)realloc(S->base,sizeof(SElemType)*(S->stacksize+STACKINCREMENT))))
      return ERROR;
 S->stacksize+=STACKINCREMENT;
 return OK;
  }//if

  S->top->data=data;
  S->top->tag=tag;
  S->top++;
  return OK;
}//PushStack

Status PopStack(SqStack *S,BiTNode **p)
{//若栈不空，则删除栈顶元素，并用*p返回栈顶元素中的data域的值
  if(S->base==S->top || p==NULL) return ERROR;
  *p=(S->top-1)->data;
  S->top--;
  return OK;
}//PopStack

Status DestroyStack(SqStack *S)
{//销毁栈
  free(S->base);
  S->base=S->top=NULL;
  S->stacksize=0;
  return OK;
}//DestroyStack

Status FiClosForfather(BiTree T,BiTNode *p,BiTNode *q,BiTNode **Forf)
{//找二叉树T中的两结点*p和*q的最近共同祖先，并用*Forf返回这个最近共同祖先
  if(T==NULL || p==NULL || q==NULL || Forf==NULL ) return ERROR;//参数非法，入口断言

  int m=0;//每次拭到结点*p和*q中的一个时，m++
  int n=0;//当m=0时，表示当前栈顶元素的指针域data所指向的二叉树中的结点的祖先的个数
          //当m!=0时，表示首次找到结点*p和*q中一个时，这个结点的祖先的个数；在这之后，
          //如果这些祖先出栈，则n自减1

  SqStack S;
  InitStack(&S);
  PushStack(&S,T,0);
  while(m!=2 && S.base!=S.top)
  {
    if((S.top-1)->tag==0)
 {//在这之前未曾到过这个结点，现在是第1次来到这个结点
   (S.top-1)->tag=1;
   if((S.top-1)->data==p || (S.top-1)->data==q)
   {//找到结点*p和*q中的一个
     m++;
  if(p==q)
    m++;
   }//if

   if((S.top-1)->data->lchild!=NULL)
   {
        PushStack(&S,(S.top-1)->data->lchild,0);//左孩子进栈
  if(m==0)
    n++;
   }//if
 }//if (S.top-1)->tag==0
 else if((S.top-1)->tag==1)
 {//在这之前已经有1次来到这个结点，现在是第2次
      (S.top-1)->tag=2;
   if((S.top-1)->data->rchild!=NULL)
   {
        PushStack(&S,(S.top-1)->data->rchild,0);//右孩子进栈
  if(m==0)
    n++;
   }//if
 }//else if (S.top-1)->tag==1
 else
 {//即 (S.top-1)->tag==2 表明在这之前已有2次到过这个结点，现在是第3次，要出栈了，即“回退”
   if(m==1 && (S.top-S.base)==n)
  n--;
   //已经找到两结点*p和*q中的一个了！
   if(m==0)
  n--;
   //还未找到两结点*p和*q中的任一个！
   S.top--;//栈顶元素出栈
 }//else
  }//while

  if(m==2)
  {//在二叉树T中同时找到结点*p和*q，那么当然可以找到这两个结点的最近共同祖先
    *Forf=NULL;//初始化；必须，如果结点*p和*q中有一个与结点*T相同，那么，因为*T树根无双亲,
            //那此时结点*p和*q的最近共同祖先不存在
 SElemType *temp;
 temp=S.base;
 for(int i=1;i<=n;i++)
 {
   *Forf=temp->data;
   temp++;
 }//for
    DestroyStack(&S);
 return OK;//找到结点*p和*q的最近共同祖先
  }//if
  DestroyStack(&S);
  return ERROR;//因为结点*p和*q不全在二叉树T中，导致找不到这两个结点的最近共同祖先
}//FiClosForfather


int main()
{
  Status (*V)(BiTNode*);
  V=VisitNode;
  BiTree T;
  CreateBiTree(&T,"NOTNULL");
  printf("先序遍历二叉树：\n");
  PreOrderTraverse(T,V);
  printf("\n");

  BiTNode *root,*p,*q;
  PreOrderTraverse_2(T,1,&root);//结点的值为 1 的结点
  PreOrderTraverse_2(T,11,&p);//结点的值为 12 的结点
  PreOrderTraverse_2(T,7,&q);//结点的值为 7 的结点
  //从二叉树中找任意的3个结点，分别用指针root p q 返回这3个结点（约定都能）
  printf("root->data=%d/np->data=%d/nq->data=%d\n",root->data,p->data,q->data);

  BiTNode *Forf;
  int result=FiClosForfather(root,p,q,&Forf);

  if(result==1)
  {
  if(Forf!=NULL)
    printf("结点*p和*q的最近共同祖先是：%d\n",Forf->data);
  else
       printf("结点*p和*q的最近共同祖先是：0\n");
  }//if
  else
 printf("找不到结点*p和*q的最近共同祖先！\n");


}//main
