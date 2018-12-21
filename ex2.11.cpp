#include <iostream>
#define MAXLEN 1000
using namespace std;
int a[MAXLEN];
void insert(int data,int len);
int main(void)

{

    int i = 0;
    int x;

    while(cin >> a[i]){

    	i++;

    }
    x=a[i-1];
    insert(x,i-1);
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
    cout<<a[0];
    for (i=1;i<=len;i++)
        cout<<" "<<a[i];
    cout<<endl;
}
