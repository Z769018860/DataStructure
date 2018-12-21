#include<stdio.h>
#include<malloc.h>
#define smax 45
typedef int datatype;
typedef struct lnode  //�ṹ��͹�����Ķ���
{
 int i,j;
 struct lnode *cptr,*rptr;
 union
 {
  struct lnode *next;
  datatype v;
 }uval;
}link;
int flag=0;
//����ϡ�����ĺ���������ʮ������ͷָ��
link *creatlinkmat()
{
 link *p,*q,*head,*cp[smax];
 int i,j,k,m,n,t,s;
 datatype v;
 printf("�����С��У�����Ԫ�ظ���(m,n,t���ּ��ö��ŷָ�)");
 scanf("%d,%d,%d",&m,&n,&t);//�����С��У�����Ԫ�ظ���
 if(m>n)s=m; else s=n;
 head=(link *)malloc(sizeof(link));  //����ʮ������ͷ���
 head->i=m;head->j=n;
 cp[0]=head;   //cp[]��ָ�����飬�ֱ�ָ��ͷ�����С��б�ͷ���
 for(i=1;i<=s;i++) //����ͷ���ѭ������
 {
  p=(link *)malloc(sizeof(link));
  p->i=0;p->j=0;
  p->rptr=p;p->cptr=p;
  cp[i]=p; cp[i-1]->uval.next=p;
 }
 cp[s]->uval.next=head;
 for(k=1;k<=t;k++)
 {
  printf("/t ��%d��Ԫ��(�к�i �к�j ֵv�����ּ��ÿո�ָ�):",k);
  scanf("%d%d%d",&i,&j,&v);
  p=(link *)malloc(sizeof(link));
  p->i=i;p->j=j;p->uval.v=v;
  q=cp[i];
  while((q->rptr!=cp[i])&&(q->rptr->j<j))
   q=q->rptr;
  p->rptr=q->rptr;
  q->rptr=p;
  q=cp[j];
  while((q->cptr!=cp[j])&&(q->cptr->i<i))
   q=q->cptr;
  p->cptr=q->cptr;
  q->cptr=p;
 }
 return head;
}
//�����㺯��
void insert(int i,int j,int v,link *cp[])
{
 link *p,*q;
 p=(link *)malloc(sizeof(link));
 p->i=i;p->j=j;p->uval.v=v;
 //�����Ǿ�*p�������i��������
 q=cp[i];
 while((q->rptr!=cp[i])&&(q->rptr->j<j))
  q=q->rptr;//�ڵ�i�����ҵ�һ���кŴ���j�Ľ��*(q->rptr)
 //�Ҳ���ʱ��*q�Ǹ��б��ϵ�β���
 p->rptr=q->rptr;
 q->rptr=p;//*p������*q֮��
 //�����ǽ��������j��������
 q=cp[j];//ȡ��j�б�ͷ���
 while((q->cptr!=cp[j])&&(q->cptr->i<i))
  q=q->cptr ;//�ڵ�j�����ҵ�һ���кŴ���i�Ľ��*(q->cptr)
 //�Ҳ���ʱ��*q�Ǹ��б��ϵ�β���
 p->cptr=q->cptr;
 q->cptr=p;//*p������*q֮��
}
//���ʮ������ĺ���
void print(link *A)
{
 link *p,*q,*r;//p�ǿ�����q�ǿ�����r�ǿ�������ĸ�ʽ
 int k,col,t,row;
 col=A->j;//����A������
 printf("����Ϊ��/n");
 p=A->uval.next;//pָ���һ����㣨����ͷ��㣩
 while(p!=A)
 {
  q=p->rptr;//pָ������һ�е�һ��ֵ
  if(q==A->cptr)break;//����л��д������ˣ�����
  r=p;//rָ����һ�е�ͷ���
  while(q!=p)
  {
   for(k=1;k<q->j-(r->j);k++)//���ͬһ�������������ݼ����
    printf("  0");
   printf("%3d",q->uval.v);//����Ǹ�����ֵ
   q=q->rptr;//qָ����һ�е���һ��Ԫ��
   r=r->rptr;//rָ��qǰ���һ������Ԫ��
  }
  k=r->j;//k��ֵ��ĳһ�е����һ������Ԫ������
  for(t=k;t<col;t++)//���һ�������һ������Ԫ�������
   printf("  0");
  printf("/n");
  p=p->uval.next;//pָ����һ��
 }
}
link *add(link *a,link *b)
{
 link *p,*q,*u,*v,*r,*cp[smax],*c;//p,q����ʮ����a������,u,v����ʮ����b������
 int s,i;
 if(a->i!=b->i||a->j!=b->j)
 { flag=1;return NULL; }
 //����c�ı�ͷ����
 c=(link *)malloc(sizeof(link));
 c->i=a->i;c->j=a->j;
 if(c->i>c->j)s=c->i; else s=c->j;
 cp[0]=c;
 for(i=1;i<=s;i++)
 {
  r=(link *)malloc(sizeof(link));
  r->i=0;r->j=0;
  r->rptr=r;r->cptr=r;
  cp[i]=r;
  cp[i-1]->uval.next=r;
 }
 cp[s]->uval.next =c;
  //�������
 p=a->uval.next;u=b->uval.next;
 while(p!=a&&u!=b)
 {
  q=p->rptr;v=u->rptr;
  if(q==p&&v!=u)//����a�е�p��Ϊ�գ�����b�ĵ�u�в�Ϊ��
   while(v!=u)//��b���еĶ����Ƶ��;�����
   {insert(v->i,v->j,v->uval.v,cp);v=v->rptr;}
  else if(v==u&&q!=p)//����a�е�p�в�Ϊ�գ�����b�ĵ�u��Ϊ��
   while(q!=p)
   {insert(q->i,q->j,q->uval.v,cp);q=q->rptr;}
  else if(q!=p&&v!=u)//����b�ĵ�u�к;���a�ĵ�p�ж���Ϊ��
  {
   while(q!=p&&v!=u)
   {
    if(q->j<v->j)//���a����Ԫ�ص�����С��b�ģ���a�е�����С��b��ֵ���嵽c��
    {insert(q->i,q->j,q->uval.v,cp);q=q->rptr;}
    else if(q->j>v->j)//���b����Ԫ�ص�����С��a�ģ���a�е�����С��b��ֵ���嵽c��
    {insert(v->i,v->j,v->uval.v,cp);v=v->rptr;}
    else//a��b��ǰ����ͬһ��λ�ã��жϼӵĺ��Ƿ�Ϊ�㣬��Ϊ������ӷ�����
    {if(q->uval.v+v->uval.v!=0)insert(q->i,q->j,(q->uval.v+v->uval.v),cp);
     q=q->rptr;v=v->rptr;
    }
   }
   if(q==p&&v!=u)//���bδ�����꣬��b��δ�����ֵ�����뵽�;�����
    while(v!=u)
    {insert(v->i,v->j,v->uval.v,cp);v=v->rptr;}
   else if(v==u&&q!=p)//���aδ�����꣬��a��δ�����ֵ�����뵽�;�����
     while(q!=p)
     {insert(q->i,q->j,q->uval.v,cp);q=q->rptr;}
   else; //���������ˣ�ʲô������
  }
  else ; //����b�ĵ�u�к;���a�ĵ�p�ж�Ϊ�գ�ʲô������

  p=p->uval.next;u=u->uval.next;//a��b��ָ����һ��
 }
 return c;
}
//
void main()
{
 link *A,*B,*C;
 A=creatlinkmat();print(A);
 B=creatlinkmat();print(B);
 C=add(A,B);
 if(flag==1)printf("����A��B�������!!");
 else printf("�;���CΪ��/n");print(C);
}

