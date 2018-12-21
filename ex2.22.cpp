#include <iostream>
using namespace std;
char va[1000];
int len;
int main()
{
    char c;
    int i=1000;
    while ((c=getchar())!=EOF) {
        if(c==','||c=='\n') continue;
        va[i--]=c;
    }
    len=i+1;
    for (i=len;i<1000;i++)
    {
        cout<<va[i]<<",";
    }
    cout<<va[1000]<<endl;
    return 0;
}
