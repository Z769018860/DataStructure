#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
typedef struct PolyNode {
    int  coef;
    int  exp;
    struct PolyNode *next;
} PolyNode, *PolyLink;  // ����ʽԪ�أ���������

typedef PolyLink LinkedPoly; // ��ʽ����ʽ
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
/* ϡ�����ʽ pa ��ѭ���������洢�ṹ��     */
/* ���������޸ĳ����ĵ����������ͷ����ý�� */
{
    LinkedPoly p,s;
    p = pa;
    s = p -> next;
    while(p -> next != pa){
        if(s -> exp == 0){   //ָ��Ϊ0ʱ�����⴦��
            p -> next = s -> next;
            free(s);
            s = p -> next;   //��¼��һ�ڵ�
        }
        else{   //�󵼹���
            s -> coef = s -> exp * s -> coef;
            s -> exp--;
            s = s -> next;    //s�ڵ�������
            p = p-> next;     //p�ڵ�������
        }
    }
}


