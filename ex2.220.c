#include<stdio.h>
#include<stdlib.h>
char va[1000];
int len;
int main()
{
    char c;
    int i=1000;
    while ((c=getchar())!=EOF)
        {
        if(c==','||c=='\n') continue;
        va[i--]=c;
    }
    len=i+1;
    for (i=len;i<1000;i++)
    {
        printf("%c,",va[i]);
    }
    printf("%c\n",va[1000]);
    return 0;
}
