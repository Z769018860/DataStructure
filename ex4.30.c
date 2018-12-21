#include <stdio.h>
#include <stdlib.h>
#define MAXLEN 100

typedef struct HString
{
    int len;
    char *s;
}HString;

void compare(char s[MAXLEN],int len)
{
    HString longest;
    int i,j,k,l;
    longest.len = 0;
    longest.s = NULL;
    for(i=1;i<=len;i++)
    {
        for(j=i+1;j<=len; j++)
        {
            if(s[i]==s[j])
            {
                for(k=i+1,l=j+1; k<j&&s[k]&&s[l]&&s[k]==s[l]; k++,l++)
                    ;
                if(longest.len < k-i)
                {
                    longest.s = s+i;
                    longest.len = k-i;
                }
            }
        }
    }
    if(longest.len>=2)
    {
        for(i=0;i<longest.len;i++)
            printf("%c",longest.s[i]);
        printf(" %d",longest.s-s-1);
    }
    else
        printf("-1");
    printf("\n");

}

int main()
{
    //fetch input
    char s[MAXLEN];
    int i = 0;
    int len;
    char c;
    while((c=getchar())!='\n')
        s[++i] = c;
    len=i;
    s[++i] = '\0';
    compare(s,len);
    return 0;
}
