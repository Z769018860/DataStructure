
#include <stdio.h>
#include <string.h>
#include <malloc.h>

#define OK 1
#define TRUE 1
#define FALSE 0
#define ERROR 0
#define INFEASIBLE -1

#define DestroyString ClearString // DestroyString()与ClearString()作用相同
#define MAX_STR_LEN 40 // 用户可在255(1个字节)以内定义最大串长
typedef char SString[MAX_STR_LEN+1]; // 0号单元存放串的长度
typedef int Status; // Status是函数的类型,其值是函数结果状态代码，如OK等
int StrConcat(SString t,SString s1,SString s2)
{
    int uncut;
    if (s1[0]+s2[0] <= MAXSTRLEN)
    {
        strncpy(&t[1],&s1[1],s1[0]);
        strncpy(&t[s1[0]+1],&s2[1],s2[0]);
        t[0]=s1[0]+s2[0];t[t[0]+1]='\0';
        uncut= TRUE;
    }
    else if(s1[0]<MAXSTRLEN)
    {// s2被截断
        strncpy(&t[1],&s1[1],s1[0]);
        strncpy(&t[s1[0]+1],&s2[1],MAXSTRLEN-s1[0]);
        t[0]=MAXSTRLEN;t[MAXSTRLEN+1]='\0';
        uncut=FALSE;
    }
    else
    { //s1[0] = MAXSTRLEN，故s2被截断，仅取s1
    strncpy(&t[1],&s1[1],MAXSTRLEN);
    t[0]=MAXSTRLEN;t[MAXSTRLEN+1]='\0';
    uncut=FALSE;
    }
    return uncut;
}

//将s中从第pos个字符开始的连续len个字符放到sub中
Status StrSubStr(SString sub,SString s,int pos,int len)
{
 if(pos<1 || pos>s[0] || len<0 ||
    zlen> s[0]-pos+1) return ERROR;
  strncpy(&sub[1],&s[pos],len);
  sub[0]= len; sub[sub[0]+1]='\0';
  return OK;
}

int StrIndex(SString s,SString t,int pos)
{
int i,j; i=pos;j=1;
while(i<=s[0] && j<=t[0])
    {
    if(s[i] == t[j]) {i++;j++;} //继续比较后继字符
    else {i=i-j+2;j=1;}
    //指针i后退(至当前匹配起始位置的下一位置)重新开始匹配
    }
    if(j>t[0]) return i-t[0];
    //匹配成功，返回子串t的位置
    else return 0;
}

Status StrAssign(SString T,char *chars)
{ // 生成一个其值等于chars的串T
    int i;
    if(strlen(chars)>MAX_STR_LEN)
        return ERROR;
    else
    {
        T[0]=strlen(chars);
        for(i=1;i<=T[0];i++)
            T[i]=*(chars+i-1);
        return OK;
    }
}


void String_Subtract(SString s,SString t,SString *r)
//求所有包含在串 s 中而 t中没有的字符构成的新串 r
{
    int i,k,j;
    StrAssign(r,'');
    for(i=1;i<=Strlen(s);i++)
    {
    StrAssign(c,SubString(s,i,1));
    for(j=1;j<i&&StrCompare(c,SubString(s,j,1));j++);
    //判断 s的当前字符 c 是否第一次出现
    if(i==j)
    {
        for(k=1;k<=Strlen(t)&&StrCompare(c,SubString(t,k,1));k++);
        //判断当前字符是否包含在 t 中
        if(k>Strlen(t)) StrAssign(r,Concat(r,c));
    }
}//for
}//String_Subtrac

int main()
{
    SString s,t,r;
    scanf("%s",s);
    scanf("%s",t);
    String_Subtract(s,t,*r);
    printf("%s\n",r);
    int i;
    for (i=0;i<Strlen(r);i++)
        printf("%d ",StrIndex(s,r[i],0));
    printf("\n");
    return 0;
}

