#include <stdio.h>
#define MAXLEN 100
int L[MAXLEN],R[MAXLEN],T[MAXLEN],n;
int Visit(int u,int v)
{
	int Nv;
	Nv=NumElem(v); // 返回结点v的下标
	if(Nv==-1) exit(-2); // 结点v不存在，退出

	if(u==v) return 1;
	if(L[Nv]==0){//左子树不存在
		if(R[Nv]==0)//右子树也不存在
			return 0;
		else{// 右子树存在，继续访问右子树
			if(Visit(u,R[Nv])) return 1;
			else return 0;
		}
	}
	else{// 左子树存在
		if(Visit(u,L[Nv]))// 左子树中存在目标
			return 1;
		else{// 左子树中没有目标，需访问右子树
			if(R[Nv]==0)// 没有右子树
				return 0;
			else{// 右子树存在，继续访问右子树
				if(Visit(u,R[Nv])) return 1;
				else return 0;
			}
		}
	}
}
// 返回结点在数组T中的下标
int NumElem(int x)
{
	int i=0;
	while(i<n&&T[i]!=x) i++;
	if(T[i]==x) return i;
	else return -1;
}
int main()
{
    int i,u,v,j;
    scanf("%d",&n);
    for (i=0;i<=n;i++)
        scanf("%d",&L[i]);
    for (i=0;i<=n;i++)
        scanf("%d",&R[i]);
    for (i=0;i<=n;i++)
        for (j=0;i<=n;j++)
    {
        if (L[j]==i||R[j]==i)
            T[i]=j;
    }
    scanf("%d%d",&u,&v);
    if (Visit(u,v)==1)
        printf("Yes!\n");
    else printf("No!\n");
    return 0;
}
