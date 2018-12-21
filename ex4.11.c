#include <stdio.h>
#define MAXLEN 200
int main()
{
    int a[MAXLEN],b[MAXLEN];
    char s[MAXLEN],t[MAXLEN];
    char c;
    int i=0,j=0,len1,len2;
    while ((c=getchar())!=' ')
    {
        s[i]=c;
        i++;
    }
    len1=i;
    for (i = 0;i < MAXLEN;i++)
        a[i] = -1;
    j=0;
    for (i=0;i<len1;i++)
    {
        if (a[s[i]]==-1)
        {
            a[s[i]]=i;
            j++;
        }
    }
    s[j]=0;
    while ((c = getchar()) != '\n')
    {
        if (a[c]!=-1)
        {
            j--;
            a[c] = -1;
        }
    }
    if (j == 0)
    {
        printf("-1");
        return 0;
    }
    int k=0;
    for (i=0;i<len1;i++)
        if (a[s[i]]!=-1)
        {
            printf("%c", s[i]);
            b[k]=a[s[i]];
            k++;
            a[s[i]]=-1;
        }
    printf(" ");
    for (i=0;i<k;i++)
        printf("%d",b[i]);
    return 0;
}
