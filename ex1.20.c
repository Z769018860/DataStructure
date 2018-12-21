#include <stdio.h>
#define MAXLEN 100
float a[MAXLEN];
void sum(int n,float x);
int main()
{
    int n,i;
    float x;
    scanf("%d",&n);
    for (i=0;i<n;i++)
        scanf("%f",&a[i]);
    scanf("%f",&x);
    sum(n,x);
    return 0;
}
void sum(int n,float x)
{
    float sum=0,xx=1;
    int i;
    for (i=0;i<n;i++)
    {
        sum+=a[i]*xx;
        xx*=x;
    }

    printf("%.5f\n",sum);
}
