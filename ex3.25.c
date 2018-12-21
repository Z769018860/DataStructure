#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define MAXSIZE 100
int F(int n);
int main()
{
    int n;
    scanf("%d",&n);
    printf("%d",F(n));
    return 0;
}
int F(int n)
{
    if (n==0)
        return n+1;
    else if (n>0)
        return F(n/2)*n;
}


