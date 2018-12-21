#include<stdio.h>
#include<malloc.h>
#define smax 45
typedef int datatype;
typedef struct lnode  //结构体和共用体的定义
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
//建立稀疏矩阵的函数，返回十字链表头指针
link *creatlinkmat()
{
 link *p,*q,*head,*cp[smax];
 int i,j,k,m,n,t,s;
 datatype v;
 printf("输入行、列，非零元素个数(m,n,t数字间用逗号分隔)");
 scanf("%d,%d,%d",&m,&n,&t);//输入行、列，非零元素个数
 if(m>n)s=m; else s=n;
 head=(link *)malloc(sizeof(link));  //建立十字链表头结点
 head->i=m;head->j=n;
 cp[0]=head;   //cp[]是指针数组，分别指向头结点和行、列表头结点
 for(i=1;i<=s;i++) //建立头结点循环链表
 {
  p=(link *)malloc(sizeof(link));
  p->i=0;p->j=0;
  p->rptr=p;p->cptr=p;
  cp[i]=p; cp[i-1]->uval.next=p;
 }
 cp[s]->uval.next=head;
 for(k=1;k<=t;k++)
 {
  printf("/t 第%d个元素(行号i 列号j 值v，数字间用空格分隔):",k);
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
//插入结点函数
void insert(int i,int j,int v,link *cp[])
{
 link *p,*q;
 p=(link *)malloc(sizeof(link));
 p->i=i;p->j=j;p->uval.v=v;
 //以下是经*p结点插入第i行链表中
 q=cp[i];
 while((q->rptr!=cp[i])&&(q->rptr->j<j))
  q=q->rptr;//在第i行中找第一个列号大于j的结点*(q->rptr)
 //找不到时，*q是该行表上的尾结点
 p->rptr=q->rptr;
 q->rptr=p;//*p插入在*q之后
 //以下是将结点插入第j列链表中
 q=cp[j];//取第j列表头结点
 while((q->cptr!=cp[j])&&(q->cptr->i<i))
  q=q->cptr ;//在第j行中找第一个列号大于i的结点*(q->cptr)
 //找不到时，*q是该行表上的尾结点
 p->cptr=q->cptr;
 q->cptr=p;//*p插入在*q之后
}
//输出十字链表的函数
void print(link *A)
{
 link *p,*q,*r;//p是控制行q是控制列r是控制输出的格式
 int k,col,t,row;
 col=A->j;//矩阵A的列数
 printf("矩阵为：/n");
 p=A->uval.next;//p指向第一个结点（不是头结点）
 while(p!=A)
 {
  q=p->rptr;//p指向这以一行的一个值
  if(q==A->cptr)break;//如果行或列处理完了，跳出
  r=p;//r指向这一行的头结点
  while(q!=p)
  {
   for(k=1;k<q->j-(r->j);k++)//输出同一行上两非零数据间的零
    printf("  0");
   printf("%3d",q->uval.v);//输出那个非零值
   q=q->rptr;//q指向这一行的下一个元素
   r=r->rptr;//r指向q前面的一个非零元素
  }
  k=r->j;//k的值是某一行的最后一个非零元的列数
  for(t=k;t<col;t++)//输出一行上最后一个非零元后面的零
   printf("  0");
  printf("/n");
  p=p->uval.next;//p指向下一行
 }
}
link *add(link *a,link *b)
{
 link *p,*q,*u,*v,*r,*cp[smax],*c;//p,q控制十字链a的行列,u,v控制十字链b的行列
 int s,i;
 if(a->i!=b->i||a->j!=b->j)
 { flag=1;return NULL; }
 //建立c的表头环链
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
  //矩阵相加
 p=a->uval.next;u=b->uval.next;
 while(p!=a&&u!=b)
 {
  q=p->rptr;v=u->rptr;
  if(q==p&&v!=u)//矩阵a中第p行为空，矩阵b的第u行不为空
   while(v!=u)//将b的行的都复制到和矩阵中
   {insert(v->i,v->j,v->uval.v,cp);v=v->rptr;}
  else if(v==u&&q!=p)//矩阵a中第p行不为空，矩阵b的第u行为空
   while(q!=p)
   {insert(q->i,q->j,q->uval.v,cp);q=q->rptr;}
  else if(q!=p&&v!=u)//矩阵b的第u行和矩阵a的第p行都不为空
  {
   while(q!=p&&v!=u)
   {
    if(q->j<v->j)//如果a中有元素的列数小于b的，将a中的所有小于b的值都插到c中
    {insert(q->i,q->j,q->uval.v,cp);q=q->rptr;}
    else if(q->j>v->j)//如果b中有元素的列数小于a的，将a中的所有小于b的值都插到c中
    {insert(v->i,v->j,v->uval.v,cp);v=v->rptr;}
    else//a、b当前是在同一个位置，判断加的和是否为零，不为零才做加法运算
    {if(q->uval.v+v->uval.v!=0)insert(q->i,q->j,(q->uval.v+v->uval.v),cp);
     q=q->rptr;v=v->rptr;
    }
   }
   if(q==p&&v!=u)//如果b未处理完，将b中未处理的值都插入到和矩阵中
    while(v!=u)
    {insert(v->i,v->j,v->uval.v,cp);v=v->rptr;}
   else if(v==u&&q!=p)//如果a未处理完，将a中未处理的值都插入到和矩阵中
     while(q!=p)
     {insert(q->i,q->j,q->uval.v,cp);q=q->rptr;}
   else; //都处理完了，什么都不做
  }
  else ; //矩阵b的第u行和矩阵a的第p行都为空，什么都不做

  p=p->uval.next;u=u->uval.next;//a、b都指向下一行
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
 if(flag==1)printf("矩阵A、B不能相加!!");
 else printf("和矩阵C为：/n");print(C);
}

