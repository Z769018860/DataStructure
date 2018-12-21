#include <stdio.h>
#include <stdlib.h>
#define m 3
typedef struct k{
    char data;
    struct k *child[m];
}tree;
/*前序遍历建树*/
tree *createTree()
{   tree *t;
    /*1、如果是‘#’则return;*/
    char x=getchar();
    if(x=='#') return NULL;
    /*2、否则，造节点*/
    t=(tree *)malloc(sizeof(tree));
    t->data=x;
    int i;
    for(i=0;i<m;i++) t->child[i]= createTree();
    return t;
}
/*凹入表示法输出,空格，字符，#*/
void printTree(tree *t,int space,int JH){
    /*如果为空树，return；*/
    if(t==NULL) return ;
    /*输出根*/
    int i,j,k;
    for(i=0;i<space;i++) printf(" ");
    printf("%c",t->data);
    for(j=0;j<JH;j++) printf("##");
    printf("\n");
    /*输出子树*/
    for(k=0;k<m;k++) printTree(t->child[k],space+2,JH-2);
}
int main()
{   tree *tr;
    tr=createTree();
    printTree(tr,2,30);
    return 0;
}
