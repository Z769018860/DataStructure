#include <iostream>

using namespace std;

int main(void)

{

    char a[1000],aa[1000];

    char b[1000],bb[1000];

    int i1 = 0;

    int i2 = 0;

    char item = 'a';

    int secondStr = -1;

    while(cin >> item){

    	if(item == ';'){

    		secondStr = 1;

    		continue;

    	}

    	if(secondStr < 0){

    		if(item == ','){

    			continue;

    		}else{

    			va[i1] = item;

    		}

    		i1++;

    	}else{

    		if(item == ','){

    			continue;

    		}else{

    			vb[i2] = item;

    		}

    		i2++;

    	}

    }
    len1=i1;len2=i2;
    compare(len1,len2);
	return 0;

}
void compare(int len1,int len2);
void compare(int len1,int len2)
{
    int i=0;
    while ((a[i]==b[i])&&(len1>0)&&(len2>0))
    {
        i++;
        len1--;
        len2--;
    }
    if ((len1==len2)&&(len1==0))
        printf("0\n");
    if (((len1==0)&&(len2>len1))||(a[i]<b[i]))
        printf("1\n");
    if (((len2==0)&&(len1>len2))||(a[i]>b[i]))
        printf("2\n");
}