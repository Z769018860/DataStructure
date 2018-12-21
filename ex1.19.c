#include <stdio.h>
#define MAXINT 65535
#define ARRSIZE 300
int a[ARRSIZE];
void com(int n);
int main()
{
    int n;
    scanf("%d",&n);
    com(n);
    return 0;
}
void com(int n)
{
    int i;
    a[0]=1;
    if (n>ARRSIZE)
    {
        for (i=1;i<ARRSIZE;i++)
            if (a[i-1]*i*2>MAXINT)
            {
                printf("%d\n",a[i-1]);
                exit(0);
            }
            else
            {
                a[i]=a[i-1]*i*2;
            }
        printf("%d\n",a[ARRSIZE-1]);
        printf("ERROR:n is larger than arrsize!\n");
    }
    else
    {
        for (i=1;i<n;i++)
            if (a[i-1]*i*2>MAXINT)
            {
                printf("%d\n",a[i-1]);
                exit(0);
            }
            else
            {
                a[i]=a[i-1]*i*2;
            }
        printf("%d\n",a[n-1]);
    }
}
