#include <stdio.h>
int x,y,z;
void swap(int *a,int *b);
int main()
{
    scanf("%d%d%d",&x,&y,&z);
    if (x<y)
        swap(&x,&y);
    if (x<z)
        swap(&x,&z);
    if (y<z)
        swap(&y,&z);
    printf("%d %d %d\n",x,y,z);
    return 0;
}

void swap(int *a,int *b)
{
    int temp;
    temp=*a;
    *a=*b;
    *b=temp;
}
