#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdlib>
#include<string>
using namespace std;

typedef int elementtype;
struct node{//节点的型
	node* lchild;
	node* rchild;
	bool ltag;
	bool rtag;
	elementtype element;
};
typedef node* head;//指向树根root
typedef node* tree;//指向线索树的根节点

void makeNull(head& h)//将线索二叉树置空
{
	h->lchild=h;
	h->ltag=false;
	h->rchild=h;
	h->rtag=true;
}
head pointTotree(head& h,tree& t)//令head指向tree,注意head指向的并不是根节点，tree指向根节点
{
	h->lchild=t;
	h->rchild=h;
	h->ltag=true;
	h->rtag=true;
	return h;
}

//中根遍历的下一个节点
node* inNext(node* p)
{
	node* q=p->rchild;
	if(p->rtag==true)//如果有右子树，找出右子树的最左节点
		while(q->ltag==true)
			q=q->lchild;
	return q;
}
//中根遍历的上一个节点
node* inPre(node* p)
{
	node *q= p->lchild;
	if(p->ltag==true)//如果P的左子树存在，则其前驱结点为左子树的最右结点
		while(q->rtag==true)
			q=q->rchild;
	return q;//左子树的最右结点
}
//中序遍历
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

//插入右孩子
void rInsert(node* s,node* r)
{
	node* w;
	r->rchild=s->rchild;
	r->rtag=s->rtag;
	r->lchild=s;
	r->ltag=false;//新插入的节点木有左子树，所以lchild指向的是父节点
	s->rchild=r;
	s->rtag=true;//原节点的右孩子为新插入的节点
	if(r->rtag==true){
		//这里是神马意思呢∑q|?Д?|p，就是如果被插节点s有右子树 ，
		//找出被插节点s的的next位置，即右子树中的最左节点，令其lchild指向新添加的节点r
		//因为插入前该最左节点的lchild指向的是原来节点s
		w=inNext(r);
		w->lchild=r;
	}
}

//插入左孩子
void lInsert(node* s,node* l)
{
	node* w;
	l->lchild=s->lchild;
	l->ltag=s->ltag;
	l->rchild=s;
	l->rtag=false;
	s->lchild=l;
	s->ltag=true;
	if(l->ltag==true){//与插入右孩子方法相似，只需把左右方向对调即可
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
	//构造线索树213
	lInsert(root,lc);
	rInsert(root,rc);
	thInOrder(h);
	cout<<endl;

	//root左边插入C
	lInsert(root,c);
	thInOrder(h);

  return 0;
}
