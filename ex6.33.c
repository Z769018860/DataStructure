#include <stdio.h>
#define MAXLEN 100
int L[MAXLEN],R[MAXLEN],n;
int Visit(int u,int v)
{
	if(u==v) return 1;
	if(L[v]==0){//������������
		if(R[v]==0)//������Ҳ������
			return 0;
		else{// ���������ڣ���������������
			if(Visit(u,R[v])) return 1;
			else return 0;
		}
	}
	else{// ����������
		if(Visit(u,L[v]))// �������д���Ŀ��
			return 1;
		else{// ��������û��Ŀ�꣬�����������
			if(R[v]==0)// û��������
				return 0;
			else{// ���������ڣ���������������
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
