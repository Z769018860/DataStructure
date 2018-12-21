#include <stdio.h>
#define MAXLEN 1000
int a[MAXLEN];
void insert(int data,int len);
int main()
{
    int len,i,data;
    scanf("%d",&len);
    for (i=0;i<len;i++)
        scanf("%d",&a[i]);
    scanf("%d",&data);
    insert(data,len);
    return 0;
}
void insert(int data,int len)
{
    int k=0,i;;
    while (a[k]<data)
        k++;
    for (i=len;i>k;i--)
        a[i]=a[i-1];
    a[k]=data;
    printf("%d",a[0]);
    for (i=1;i<=len;i++)
        printf(" %d",a[i]);
    printf("\n");
}
