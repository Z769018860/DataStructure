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
bitree creat_bt(){   //����չǰ�򽨶�����
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
void exchange(bitree t) //������������
{bitree p;
 if(t!=NULL)
   { p=t->lchild;t->lchild=t->rchild;
     t->rchild=p;
     exchange(t->lchild);
     exchange(t->rchild);
   }
}
void inorder(bitree bt) //�ݹ���������
{ if (bt){
       inorder(bt->lchild);
       printf("% d",bt->data);
       inorder(bt->rchild);
}
}
int main()
{bitree root;
printf("\n");
printf("��������������Ԫ�أ�");
root=creat_bt(); /*create tree of useing preorder*/
printf("����ǰ�����������ǣ�");
inorder(root);
exchange(root);
printf("\n����������������ǣ�");
inorder(root);
printf("\n");
}
