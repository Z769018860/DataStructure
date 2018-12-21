#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<iostream>
using namespace std;

typedef char ElemType;

typedef struct LNode{
	ElemType data[4];
	struct LNode *next;
}LNode,*LinkList;
char s;
int count;


void print(LinkList &head) {

    if(head == NULL)
        return;
    LNode* node = head->next;
    printf("numbers of L\n");
    for(int i = 1; node != NULL; i++) {
//		puts(node->data);
       printf("%s",node->data);
        node = node->next;
    }

}


LinkList crea_last(LinkList &L,int n)
{
	L = new LNode;
	L->next = NULL;

	LNode *endNode = L;
	for(int i=0;i<n;i++)
	{
		LNode *p=new LNode;
		gets(p->data);
		p->next=NULL;
		endNode->next = p;
        endNode = p;
	}
	print(L);
	return L;
}

void Out(LinkList &L)
{
	LinkList p;
	p=L->next;
	s=p->data[count];
	count++;
	if(count==4)
	{
		count=0;
		L->next=p->next;
		free(p);
	}
}
int main()
{
	int n=0;
	int index=0;
	LNode *head;
	char a[100];
	count=0;
	printf("\t\tplease input the number of L: ");
    scanf("%d",&n);
    getchar();
    LinkList L = crea_last(head,n/4+1);
    for(int i=0;i<n/2;i++)
    {
    	Out(L);
    	a[index++]=s;
	}
	if(n%2!=0)
		Out(L);
	printf("\n");
	for(int i=index-1;i>=0;i--)
	{
		Out(L);
		if(a[i]!=s)
		{
			printf("NO\n");
			return 0;
		}
	}
	printf("OK\n");
	return 0;
}
