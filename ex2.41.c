#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
typedef struct PolyNode {
    int  coef;
    int  exp;
    struct PolyNode *next;
} PolyNode, *PolyLink;  // 多项式元素（项）结点类型

typedef PolyLink LinkedPoly; // 链式多项式
void Difference(LinkedPoly pa);
PolyLink createlist();
void traverselist(PolyLink dl);
int main()
{
    int i;
    PolyLink dl;
    dl=createlist();
    Difference(dl);
    traverselist(dl);
    return 0;
}
PolyLink createlist()
{
    int i;
    int len;
    int val,val2;
    int num;
    PolyLink PolyLinkHead=(PolyLink)malloc(sizeof(PolyNode));
    PolyLink PolyLinkTail=PolyLinkHead;
    PolyLinkTail->next=NULL;
    scanf("%d",&len);
    for (i=0;i<len;i++)
    {
        scanf("%d%d",&val,&val2);
        PolyLink PolyLinkNew=(PolyLink)malloc(sizeof(PolyNode));
        PolyLinkNew->coef=val;
        PolyLinkNew->exp=val2;
        PolyLinkTail->next=PolyLinkNew;
        PolyLinkNew->next=NULL;
        PolyLinkTail=PolyLinkNew;
    }
    return PolyLinkHead;
}

void traverselist(LinkedPoly dl)
{
    PolyLink p;
    p=dl->next;
    while(p!=NULL)
    {
        printf("%d %d\n",p->coef,p->exp);
        p=p->next;
    }
    return;
}
void Difference(LinkedPoly pa)
/* 稀疏多项式 pa 以循环链表作存储结构，     */
/* 将此链表修改成它的导函数，并释放无用结点 */
{
    LinkedPoly p,s;
    p = pa;
    s = p -> next;
    while(p -> next != pa){
        if(s -> exp == 0){   //指数为0时作特殊处理
            p -> next = s -> next;
            free(s);
            s = p -> next;   //记录下一节点
        }
        else{   //求导过程
            s -> coef = s -> exp * s -> coef;
            s -> exp--;
            s = s -> next;    //s节点往后移
            p = p-> next;     //p节点往后移
        }
    }
}


