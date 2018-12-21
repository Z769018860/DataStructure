#include<stdio.h>
#include<malloc.h>
typedef struct binode{
   int data;
   struct binode *lchild,*rchild;
   }binode,*bitree;
typedef struct{
   bitree elem[100];
   int top;
   }stack;
bitree creat_bt(){   //按扩展前序建二叉树
bitree t;int x;
scanf("%d",&x);
if (x==0) t=NULL;
else { t=(bitree)malloc(sizeof(binode));
       t->data=x;
       t->lchild=creat_bt();
       t->rchild=creat_bt();
      }
return t;
}
void exchange(bitree t) //左、右子树交换
{bitree p;
 if(t!=NULL)
   { p=t->lchild;t->lchild=t->rchild;
     t->rchild=p;
     exchange(t->lchild);
     exchange(t->rchild);
   }
}
void inorder(bitree bt) //递归的中序遍历
{ if (bt){
       inorder(bt->lchild);
       printf("% d",bt->data);
       inorder(bt->rchild);
}
}
int main()
{bitree root;
printf("\n");
printf("建二叉树，输入元素：");
root=creat_bt(); /*create tree of useing preorder*/
printf("交换前的中序序列是：");
inorder(root);
exchange(root);
printf("\n交换后的中序序列是：");
inorder(root);
printf("\n");
}
