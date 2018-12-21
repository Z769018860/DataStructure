#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define ERROR 0
#define OK 1
#define STACK_INIT_SIZE 100 //ջ�Ĵ洢�ռ��ʼ������
#define STACKINCREMENT 10 //ջ�Ĵ洢�ռ��ʼ��������

typedef int Status;
typedef int TElemType;
typedef struct BiTNode
{
  TElemType data;
  struct BiTNode *lchild,*rchild;
}BiTNode,*BiTree;//�������Ķ���������ṹ

typedef struct
{
  TElemType data;//���浱ǰ����Ľ���������
  char child;//child='D' ��ʾ�ý�������Һ��ӣ�child='L' ��ʾ�ý���������
             //child='R' ��ʾ�ý������Һ��ӣ�child='O' ��ʾ�ý�������Һ���
}NodeStatus;

typedef BiTNode **QElemType;
typedef struct QNode
{
  QElemType data;
  struct QNode *next;
}QNode,*QueuePtr;
//���еĽ��ṹ
typedef struct
{
  QueuePtr front;//��ͷָ�룬����ָ����е�ͷ��㣨�Ǵ�ͷ���Ķ��У�
  QueuePtr rear;//��βָ�룬ָ���βԪ��
}LinkQueue;
//�������У����е���ʽ����ṹ



Status InitQueue(LinkQueue *LQ)
{//����һ���ն���,ֻ��ͷ���
  if(!(LQ->front=(QueuePtr)malloc(sizeof(QNode)))) return ERROR;//����ͷ���
  LQ->front->next=NULL;
  LQ->rear=LQ->front;
  return OK;
}//InitQueue

Status EnQueue(LinkQueue *LQ,QElemType e)
{//����Ԫ��eΪ����*LQr��βԪ��
  QNode *p;
  if(!(p=(QNode*)malloc(sizeof(QNode)))) return ERROR;
  p->data=e;
  p->next=NULL;
  LQ->rear->next=p;
  LQ->rear=p;
  return OK;
}//EnQueue

Status DeQueue(LinkQueue *LQ,QElemType *e)
{//�����в��գ���ɾ����ͷԪ�أ�����Ԫ��㣩������*e���ؽ��������������ERROR
  if(LQ->front==LQ->rear) return ERROR;
  *e=LQ->front->next->data;
  LQ->front->next=LQ->front->next->next;//��ͷԪ�س�����
  if(LQ->front->next==NULL)     //Ŷ��ԭ����������ˡ�����������
 LQ->rear=LQ->front;//�����б�Ϊ�գ����޸Ķ�βָ��
  return OK;
}//DeQueue

Status DestroyQueue(LinkQueue *LQ)
{//���ٶ���
 QNode *p;
  while(LQ->front!=LQ->rear)
  {
 p=LQ->front->next;
 LQ->front->next=LQ->front->next->next;
    if(LQ->front->next==NULL)
   LQ->rear=LQ->front;//�����б�Ϊ�գ����޸Ķ�βָ��
 free(p);
  }//while
  free(LQ->front);//�ͷŶ�ͷ���
  return OK;
}//DestroyQueue






Status CreateBiTree(BiTree *T,char *s)
{//�����˳�򣨴������£�ͬһ��δ������ң�����������н���ֵ�Լ��ý��ӵ�еĺ��ӵ����
 //������������ʾ�Ķ�����T����s="NULL",��ʾ����һ�ÿն���������s="NOTNULL" ��ʾ�������ǿ�
  if(T==NULL ||(strcmp(s,"NULL") && strcmp(s,"NOTNULL"))) return ERROR;//�����Ƿ�,��ڶ���

  if(!strcmp(s,"NULL"))
  {//�������
    *T=NULL;
 printf("������һ���ն�������\n");
 return OK;
  }//if

  //�������������������һ���ǿն�����
  printf("����һ���ǿն�������\n");

  NodeStatus NS;//���浱ǰ����Ľ���ֵ�Լ��ý��ӵ�еĺ��ӵ����
  LinkQueue LQ;//����һ����������
  InitQueue(&LQ);//����һ��ֻ��ͷ���Ŀն���
  EnQueue(&LQ,T);//��ʼ������Ԫ��
  QElemType p;//��p���ض�ͷԪ���е�������
  char c=' ';//��������������ȷ������Ķ������Ľ���Ƿ������ѭ����ʼ���ַ�c

  while(c!='/n')
  {
    scanf("%d %c",&(NS.data),&(NS.child));
 //printf("NS.data=%d  NS.child=%c/n",NS.data,NS.child );

    DeQueue(&LQ,&p);//ȡ��ͷԪ�ص������򣬲�ʹ��ͷԪ�س�����
 if(!((*p)=(BiTNode*)malloc(sizeof(BiTNode)))) return ERROR;
 //����һ�����
 (*p)->data=NS.data;//�������иý���ֵ
 //printf("(*p)->data=%d/n",(*p)->data);

    (*p)->lchild=NULL;//���ﲻ��©�İ�
    (*p)->rchild=NULL;//���ﲻ��©�İ�

 if(NS.child=='D')
 {//�ý�������Һ���
   EnQueue(&LQ,&((*p)->lchild));
      EnQueue(&LQ,&((*p)->rchild));
 }//if NS.child=='D'
    else if(NS.child=='L')
 {//�ý���������
   EnQueue(&LQ,&((*p)->lchild));
 }// else if NS.child=='L'
 else if(NS.child=='R')
 {//�ý������Һ���
   EnQueue(&LQ,&((*p)->rchild));
 }//else if NS.child=='R'

 c=getchar();

  }//while

  DestroyQueue(&LQ);

  return OK;
}//CreateBiTree

Status VisitNode(BiTNode *p)
{//���ʶ������н���������
  if(p==NULL) return ERROR;
  printf("%d ",p->data);
  return OK;
}//VisitNode

Status PreOrderTraverse(BiTree T,Status (*V)(BiTNode *))
{//�������������
  if(T==NULL) return OK;
  if((*V)(T))
    if(PreOrderTraverse(T->lchild,V))
   if(PreOrderTraverse(T->rchild,V))
    return OK;
  return ERROR;
}//PreOrderTraverse

Status PreOrderTraverse_2(BiTree T,TElemType e,BiTNode **p)
{//�������������,���ҵ�һ������ֵ��e ��ȣ�����*pָ�뷵��������ĵ�ַ������������ERROR
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
}SElemType;//ջԪ�ؽ��ṹ

typedef struct
{
  SElemType *base; //ջ��ָ�룬��ջ����֮ǰ������֮��base��ֵΪ NULL
  SElemType *top;  //ջ��ָ�룬ָ��ջ��Ԫ�ص���һλ
  int stacksize;   //��ǰ�ѷ���Ĵ洢�ռ䣬��Ԫ��SElemTypeΪ��λ
}SqStack;          //ջ��˳��洢��ʾ

Status InitStack(SqStack *S)
{//����һ����ջ
  if(S==NULL) return ERROR;//�����Ƿ�
  if(!(S->base=(SElemType*)malloc(sizeof(SElemType)*STACK_INIT_SIZE))) return ERROR;
  //��ջ�ĳ�ʼ�ռ�
  S->top=S->base;//��ʼ��ջΪ��ջ
  S->stacksize=STACK_INIT_SIZE;
  return OK;
}//InitStack


Status PushStack(SqStack *S,BiTNode *data,int tag)
{//����һ��ջ��Ԫ�أ�����data��tagΪ�µ�ջ��Ԫ�ص�������
  if(S->top-S->base==S->stacksize)
  {//ջ��
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
{//��ջ���գ���ɾ��ջ��Ԫ�أ�����*p����ջ��Ԫ���е�data���ֵ
  if(S->base==S->top || p==NULL) return ERROR;
  *p=(S->top-1)->data;
  S->top--;
  return OK;
}//PopStack

Status DestroyStack(SqStack *S)
{//����ջ
  free(S->base);
  S->base=S->top=NULL;
  S->stacksize=0;
  return OK;
}//DestroyStack

Status FiClosForfather(BiTree T,BiTNode *p,BiTNode *q,BiTNode **Forf)
{//�Ҷ�����T�е������*p��*q�������ͬ���ȣ�����*Forf������������ͬ����
  if(T==NULL || p==NULL || q==NULL || Forf==NULL ) return ERROR;//�����Ƿ�����ڶ���

  int m=0;//ÿ���õ����*p��*q�е�һ��ʱ��m++
  int n=0;//��m=0ʱ����ʾ��ǰջ��Ԫ�ص�ָ����data��ָ��Ķ������еĽ������ȵĸ���
          //��m!=0ʱ����ʾ�״��ҵ����*p��*q��һ��ʱ������������ȵĸ���������֮��
          //�����Щ���ȳ�ջ����n�Լ�1

  SqStack S;
  InitStack(&S);
  PushStack(&S,T,0);
  while(m!=2 && S.base!=S.top)
  {
    if((S.top-1)->tag==0)
 {//����֮ǰδ�����������㣬�����ǵ�1������������
   (S.top-1)->tag=1;
   if((S.top-1)->data==p || (S.top-1)->data==q)
   {//�ҵ����*p��*q�е�һ��
     m++;
  if(p==q)
    m++;
   }//if

   if((S.top-1)->data->lchild!=NULL)
   {
        PushStack(&S,(S.top-1)->data->lchild,0);//���ӽ�ջ
  if(m==0)
    n++;
   }//if
 }//if (S.top-1)->tag==0
 else if((S.top-1)->tag==1)
 {//����֮ǰ�Ѿ���1�����������㣬�����ǵ�2��
      (S.top-1)->tag=2;
   if((S.top-1)->data->rchild!=NULL)
   {
        PushStack(&S,(S.top-1)->data->rchild,0);//�Һ��ӽ�ջ
  if(m==0)
    n++;
   }//if
 }//else if (S.top-1)->tag==1
 else
 {//�� (S.top-1)->tag==2 ��������֮ǰ����2�ε��������㣬�����ǵ�3�Σ�Ҫ��ջ�ˣ��������ˡ�
   if(m==1 && (S.top-S.base)==n)
  n--;
   //�Ѿ��ҵ������*p��*q�е�һ���ˣ�
   if(m==0)
  n--;
   //��δ�ҵ������*p��*q�е���һ����
   S.top--;//ջ��Ԫ�س�ջ
 }//else
  }//while

  if(m==2)
  {//�ڶ�����T��ͬʱ�ҵ����*p��*q����ô��Ȼ�����ҵ����������������ͬ����
    *Forf=NULL;//��ʼ�������룬������*p��*q����һ������*T��ͬ����ô����Ϊ*T������˫��,
            //�Ǵ�ʱ���*p��*q�������ͬ���Ȳ�����
 SElemType *temp;
 temp=S.base;
 for(int i=1;i<=n;i++)
 {
   *Forf=temp->data;
   temp++;
 }//for
    DestroyStack(&S);
 return OK;//�ҵ����*p��*q�������ͬ����
  }//if
  DestroyStack(&S);
  return ERROR;//��Ϊ���*p��*q��ȫ�ڶ�����T�У������Ҳ������������������ͬ����
}//FiClosForfather


int main()
{
  Status (*V)(BiTNode*);
  V=VisitNode;
  BiTree T;
  CreateBiTree(&T,"NOTNULL");
  printf("���������������\n");
  PreOrderTraverse(T,V);
  printf("\n");

  BiTNode *root,*p,*q;
  PreOrderTraverse_2(T,1,&root);//����ֵΪ 1 �Ľ��
  PreOrderTraverse_2(T,11,&p);//����ֵΪ 12 �Ľ��
  PreOrderTraverse_2(T,7,&q);//����ֵΪ 7 �Ľ��
  //�Ӷ��������������3����㣬�ֱ���ָ��root p q ������3����㣨Լ�����ܣ�
  printf("root->data=%d/np->data=%d/nq->data=%d\n",root->data,p->data,q->data);

  BiTNode *Forf;
  int result=FiClosForfather(root,p,q,&Forf);

  if(result==1)
  {
  if(Forf!=NULL)
    printf("���*p��*q�������ͬ�����ǣ�%d\n",Forf->data);
  else
       printf("���*p��*q�������ͬ�����ǣ�0\n");
  }//if
  else
 printf("�Ҳ������*p��*q�������ͬ���ȣ�\n");


}//main
