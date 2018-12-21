#include <stdio.h>
#define MAXLEN 100
int m,n;
int array[MAXLEN][MAXLEN];
int maxl(int array[MAXLEN])
{
    int i,j,max_value,maxj;
    for (j=0;j<m;j++)
        if (array[j]>max_value)
    {
        max_value=array[j];
        maxj=j;
    }
    return maxj;
}
int maxr(int a,int b)
{
    int i,max_value;
    for (i=0;i<n;i++)
        if (array[i][b]>max_value)
            max_value=array[i][b];
    if (max_value==array[a][b])
        return 1;
    else return 0;
}
int main()
{
    int i,j;
    scanf("%d%d",&n,&m);
    for (i=0;i<n;i++)
        for (j=0;j<m;j++)
        scanf("%d",&array[i][j]);
    for (i=0;i<n;i++)
    {
        j=maxl(array[i]);
        if (maxr(i,j))
            printf("%d ",array[i][j]);
    }
    printf("\n");
    return 0;
}
