#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int MatchCheck(char a[],int len){
    int flag = 0;
    char s[10000];
    int top,i;
    char temp;
    // 初始化一个栈
    top = 0;
    for(i=0;i<len;i++){
        if(a[i]=='['){
            s[++top]=a[i];
            continue;
        }
        if(a[i]==']'){
            temp = s[top];
            if(temp=='['){
                flag = 1;
                top--;
                continue;
            }else{
                flag = 0;
                break;
            }
        }

        if(a[i]=='('){
            s[++top]=a[i];
            continue;
        }
        if(a[i]==')'){
            temp = s[top];
            if(temp=='('){
                flag = 1;
                top--;
                continue;
            }else{
                flag = 0;
                break;
            }
        }
    }
    if(flag&&(top==0)){
        return 1;
    }else{
        return 0;
    }

}
int main()
{
    int i=0;
    char c;
    int len;
    char a[10000]={'\0'};
     int count = 1;
     int result;
     while((c=getchar())!=EOF){
        a[i]=c;
        i++;
     }
    len = strlen(a);
    result=MatchCheck(a,len);
         if(result){
             printf("1\n");
         }else{
             printf("0\n");
         }
     return 0;
}
