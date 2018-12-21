#include <stdio.h>
#define MAXLEN 10000
int f[MAXLEN];
int fib(int k,int m);
int main()
{
    int k,m;
    scanf("%d%d",&k,&m);
    printf("f(%d,%d)=%d\n",k,m,fib(k,m));
    return 0;
}

int fib(int k,int m)
{
    int i,j,sum;
    if (m<=k-2) return 0;
    if (m==k-2) return 1;
    for (i=0;i<=k-2;i++)
        f[i]=0;
    f[k-1]=1;
    for (i=k;i<=m;i++)
    {
        sum=0;
        for (j=i-k;j<i;j++)
            sum+=f[j];
        f[i]=sum;
    }
    return f[m];
}
