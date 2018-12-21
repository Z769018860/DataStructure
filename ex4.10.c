#include <stdio.h>
char *ss(char b[],int n,int m)
{
    char ch;
    if(m<n/2)
    {
        ch=b[m];
        b[m]=b[n-m-1];
        b[n-m-1]=ch;
        //printf("%s\n",b);
        return ss(b,n,m+1);
    }
    else
    {
        return b;
    }
}
int main()
{
    char b1[20];
    int n=0;
    scanf("%s",b1);
    while(b1[n++]!='\0');
    n-=1;
    printf("%s",ss(b1,n,0));
}
