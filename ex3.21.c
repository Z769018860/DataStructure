#include <stdio.h>
#define MAXLEN 100
int check(char c);
int main()
{
    int i = 0;
    char mem[MAXLEN];
    char c;
    int sign;
    int j;
    while ((c = getchar()) != '\n')
    {
        sign = check(c);
        if (sign == 3)
        {
            while (mem[--i] != '(')
                printf("%c", mem[i]);
            j = (mem[i-1]=='(')? -1:check(mem[i - 1]);
        }
        else if (sign == 4)
        {
            mem[i++] = c;
            j = -1;
        }
        else if (sign == 0)
            printf("%c",c);
        else
        {
            if (i<=j)
            {
                while (i>0 && check(mem[i-1])>=sign)
                    printf("%c", mem[--i]);
                mem[i++]=c;
                j = check(c);
            }
            else
            {
                mem[i++]=c;
                j=check(c);
            }
        }
    }
    while (i)
        printf("%c", mem[--i]);
    return 0;
}
int check(char c)//判定到底是哪一种类型的符号
{
    if (c == '-' || c == '+')
        return 1;
    else if (c == '*' || c == '/')
        return 2;
    else if (c == ')')
        return 3;
    else if (c == '(')
        return 4;
    else if ((c>64 && c<91)||(c > 96 && c < 123))
        return 0;
    else
        return -1;
}
