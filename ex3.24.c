#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define MAXSIZE 100
int g(int m,int n);
int main()
{
    int m,n;
    scanf("%d%d",&m,&n);
    printf("%d",g(m,n));
    return 0;
}
int g(int m,int n)
{
    if (m==0&&n>=0)
        return 0;
    else if (m>0,n>=0)
        return g(m-1,n)+n;
}


