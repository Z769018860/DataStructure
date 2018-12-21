#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAXSIZE 100
int g[MAXSIZE][MAXSIZE];
void change(int a,int b,int s);
int m,n,k;
int main()
{
    scanf("%d%d%d",&m,&n,&k);
    int i,j,a,b,s;
    for (i=0;i<m;i++)
        for (j=0;j<n;j++)
        scanf("%d",&g[i][j]);
    printf("change:");
    scanf("%d%d",&a,&b);
    printf("to:");
    scanf("%d",&s);
    change(a,b,s);
    return 0;
}
void change(int a,int b,int s)
{
    int i,j;
    g[a][b]=s;
    if (a-1>=0)
    {
        g[a-1][b]=s;
        if (b-1>=0)
            g[a-1][b-1]=s;
    }
    if (b-1>=0)
        g[a][b-1]=s;
    if (a+1<=m)
    {
        g[a+1][b]=s;
        if (b+1<=n)
            g[a+1][b+1]=s;
    }
    if (b+1<=n)
        g[a][b+1]=s;

    for (i=0;i<m;i++)
    {
        for (j=0;j<n;j++)
            printf("%d ",g[i][j]);
        printf("\n");
    }
}
