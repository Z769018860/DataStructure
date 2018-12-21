#include <stdio.h>
#define MAXLEN 100
int L[MAXLEN],R[MAXLEN],T[MAXLEN],n;
int Visit(int u,int v)
{
	int Nv;
	Nv=NumElem(v); // ���ؽ��v���±�
	if(Nv==-1) exit(-2); // ���v�����ڣ��˳�

	if(u==v) return 1;
	if(L[Nv]==0){//������������
		if(R[Nv]==0)//������Ҳ������
			return 0;
		else{// ���������ڣ���������������
			if(Visit(u,R[Nv])) return 1;
			else return 0;
		}
	}
	else{// ����������
		if(Visit(u,L[Nv]))// �������д���Ŀ��
			return 1;
		else{// ��������û��Ŀ�꣬�����������
			if(R[Nv]==0)// û��������
				return 0;
			else{// ���������ڣ���������������
				if(Visit(u,R[Nv])) return 1;
				else return 0;
			}
		}
	}
}
// ���ؽ��������T�е��±�
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
