#include <stdio.h>
#define MAXLEN 1000
char a[MAXLEN],b[MAXLEN],c[MAXLEN],d[MAXLEN];
int research(int len2,int len3);
void del(int len1,int len);
int main()
{
    int len1,i1,i2,i3,len2,len3,len;
    char item;
    while ((item=getchar())!=EOF)
    {
        if(item==','||item=='\n') continue;
        if (item==';') break;
        a[i1++]=item;
    }
    len1=i1;
    while ((item=getchar())!=EOF)
    {
        if(item==','||item=='\n') continue;
        if (item==';') break;
        b[i2++]=item;
    }
    len2=i2;
    while ((item=getchar())!=EOF)
    {
        if(item==','||item=='\n') continue;
        if (item==';') break;
        c[i3++]=item;
    }
    len3=i3;
    len=research(len2,len3);
    del(len1,len);
    return 0;
}
int research(int len2,int len3)
{
    int i,j=0,len=0;
    for (i=0;i<len2;i++)
    {
        while (j<len3)
        {
        if (c[j]<b[i]&&j<len3-1)
            j++;
        else if (c[j]==b[i])
        {
            d[len]=b[i];
            len++;
            j++;
        }
        else break;
        }

    }
    /*for (i=0;i<len;i++)
        printf(" %d",d[i]);
    printf("\n");*/
    return len;
}
void del(int len1,int len)
{
    int i,j=0,k;
    for (i=0;i<len;i++)
    {
        j=0;
        while (j<len1)
        {
        if (a[j]<d[i]&&j<len1)
            j++;
        else if (a[j]==d[i])
        {
            for (k=j;k<len1-1;k++)
                a[k]=a[k+1];
            len1--;
        }
        else break;
        }

    }
    for (i=0;i<len1-1;i++)
        printf("%c,",a[i]);
    printf("%c\n",a[len1-1]);
}
