#include <stdio.h>
void func(int a[][3][3],int m,int n,int l)
{
    int i,j,k;
    for (i=m-1;i>=0;--i)
    {
        for (j=n-1;j>=0;--j)
        {
            for (k=l-1;k>=0;--k)
            {
                if (a[i][j][k]!=0)
                {
                    if (a[i][j][k]==1&&!i&&!j&&!k)
                        printf("1");
                    else
                    {
                        if (a[i][j][k]!=1)
                            printf("%d",a[i][j][k]);
                        if (i)
                            printf("xE%d",i);
                        if (j)
                            printf("yE%d",j);
                        if (k)
                            printf("zE%d",k);
                        if (!(!i&&!j&&!k))
                            printf("+");
                    }
                }
            }
        }
    }
}

int main(int argc,char *argv[])
{
    int m=2,n=3,l=2;
    int a[3][3][3]={-3,2,4,6,-1,0,-3,9,8,
                    11,-2,-3,8,3,5,7,3,-5,
                    2,3,5,-7,9,-3,3,0,1};
    func(a,3,3,3);
    printf("\n");
    return 0;
}
