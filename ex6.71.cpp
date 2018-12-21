#include <stdio.h>
#include <stdlib.h>
#define m 3
typedef struct k{
    char data;
    struct k *child[m];
}tree;
/*ǰ���������*/
tree *createTree()
{   tree *t;
    /*1������ǡ�#����return;*/
    char x=getchar();
    if(x=='#') return NULL;
    /*2��������ڵ�*/
    t=(tree *)malloc(sizeof(tree));
    t->data=x;
    int i;
    for(i=0;i<m;i++) t->child[i]= createTree();
    return t;
}
/*�����ʾ�����,�ո��ַ���#*/
void printTree(tree *t,int space,int JH){
    /*���Ϊ������return��*/
    if(t==NULL) return ;
    /*�����*/
    int i,j,k;
    for(i=0;i<space;i++) printf(" ");
    printf("%c",t->data);
    for(j=0;j<JH;j++) printf("##");
    printf("\n");
    /*�������*/
    for(k=0;k<m;k++) printTree(t->child[k],space+2,JH-2);
}
int main()
{   tree *tr;
    tr=createTree();
    printTree(tr,2,30);
    return 0;
}
