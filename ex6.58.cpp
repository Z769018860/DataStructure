#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdlib>
#include<string>
using namespace std;

typedef int elementtype;
struct node{//�ڵ����
	node* lchild;
	node* rchild;
	bool ltag;
	bool rtag;
	elementtype element;
};
typedef node* head;//ָ������root
typedef node* tree;//ָ���������ĸ��ڵ�

void makeNull(head& h)//�������������ÿ�
{
	h->lchild=h;
	h->ltag=false;
	h->rchild=h;
	h->rtag=true;
}
head pointTotree(head& h,tree& t)//��headָ��tree,ע��headָ��Ĳ����Ǹ��ڵ㣬treeָ����ڵ�
{
	h->lchild=t;
	h->rchild=h;
	h->ltag=true;
	h->rtag=true;
	return h;
}

//�и���������һ���ڵ�
node* inNext(node* p)
{
	node* q=p->rchild;
	if(p->rtag==true)//��������������ҳ�������������ڵ�
		while(q->ltag==true)
			q=q->lchild;
	return q;
}
//�и���������һ���ڵ�
node* inPre(node* p)
{
	node *q= p->lchild;
	if(p->ltag==true)//���P�����������ڣ�����ǰ�����Ϊ�����������ҽ��
		while(q->rtag==true)
			q=q->rchild;
	return q;//�����������ҽ��
}
//�������
void thInOrder(head h)
{
	node* temp;
	temp=h;
	do{
		temp=inNext(temp);
		if(temp!=h)
			cout<<temp->element<<" ";
	}while(temp!=h);
}

//�����Һ���
void rInsert(node* s,node* r)
{
	node* w;
	r->rchild=s->rchild;
	r->rtag=s->rtag;
	r->lchild=s;
	r->ltag=false;//�²���Ľڵ�ľ��������������lchildָ����Ǹ��ڵ�
	s->rchild=r;
	s->rtag=true;//ԭ�ڵ���Һ���Ϊ�²���Ľڵ�
	if(r->rtag==true){
		//������������˼�ء�q|?��?|p�������������ڵ�s�������� ��
		//�ҳ�����ڵ�s�ĵ�nextλ�ã����������е�����ڵ㣬����lchildָ������ӵĽڵ�r
		//��Ϊ����ǰ������ڵ��lchildָ�����ԭ���ڵ�s
		w=inNext(r);
		w->lchild=r;
	}
}

//��������
void lInsert(node* s,node* l)
{
	node* w;
	l->lchild=s->lchild;
	l->ltag=s->ltag;
	l->rchild=s;
	l->rtag=false;
	s->lchild=l;
	s->ltag=true;
	if(l->ltag==true){//������Һ��ӷ������ƣ�ֻ������ҷ���Ե�����
		w=inPre(l);
		w->rchild=l;
	}
}
int main()
{
	head h=new node;
	node* root=new node;
	node* lc=new node;
	node* rc=new node;
	node* c=new node;

	root->element=1;
	lc->element=2;
	rc->element=3;
	c->element=4;

	h->rchild=root;
	h->lchild=h;
	h->ltag=true;
	h->rtag=true;

	root->lchild=h;
	root->rchild=h;
	root->ltag=false;
	root->rtag=false;
	//����������213
	lInsert(root,lc);
	rInsert(root,rc);
	thInOrder(h);
	cout<<endl;

	//root��߲���C
	lInsert(root,c);
	thInOrder(h);

  return 0;
}
