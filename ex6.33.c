#include <stdio.h>
#define MAXLEN 100
int L[MAXLEN],R[MAXLEN],n;
int Visit(int u,int v)
{
	if(u==v) return 1;
	if(L[v]==0){//左子树不存在
		if(R[v]==0)//右子树也不存在
			return 0;
		else{// 右子树存在，继续访问右子树
			if(Visit(u,R[v])) return 1;
			else return 0;
		}
	}
	else{// 左子树存在
		if(Visit(u,L[v]))// 左子树中存在目标
			return 1;
		else{// 左子树中没有目标，需访问右子树
			if(R[v]==0)// 没有右子树
				return 0;
			else{// 右子树存在，继续访问右子树
				if(Visit(u,R[v])) return 1;
				else return 0;
			}
		}
	}
}

int main()
{
    int i,u,v;
    scanf("%d",&n);
    for (i=0;i<=n;i++)
        scanf("%d",&L[i]);
    for (i=0;i<=n;i++)
        scanf("%d",&R[i]);
    scanf("%d%d",&u,&v);
    if (Visit(u,v)==1)
        printf("Yes!\n");
    else printf("No!\n");
    return 0;
}
