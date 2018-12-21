
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
typedef struct {
    char *ch;   //若是非空串，则按串长度+1分配存储区
    int length; //串长
    int strsize; //存储空间大小，包含串的结束符
} HString;
// 1.初始化串
Status StrInit (HString *s);
// 2. 获取串的长度
int StrLen(HString *s);
// 3. 比较两个串是否相等
Status IsStrEqual(HString *s,HString *t);
// 4. 比较两个串
Int StrComp(HString *s,HString *t);
//5. 将字符串常量sc赋给字符串变量s
Status StrAssign (HString *s,char *sc);
//6. 将s1和 s2拼接成s
Status StrConcat (HString *s,HString *s1, HString *s2);
//7. 取子串，将s中从第i个字符开始的连续j个字符放到subs
Status StrSubstr(HString *subs, HString *s,int i,int j);
//8. 在s的第i个字符之前插入字符串t
Status StrInsert (HString *s,int i,HString *t);
//9. 删除s的第i个字符开始的连续j个字符
Status StrDelete(HString *s,int i,int j);
//10. 串替换，将s从第i个字符开始j个连续字符用字符串t替换
Status StrReplace (HString *s,int i,int j,HString *t);
Status StrInit(HString *s)
{
    s->ch = (char *)malloc(INITSTRLEN *sizeof(char));
    if(!s->ch) return ERROR;
    s->ch[0]='\0';
    s->length = 0;
    s->strsize= INITSTRLEN;
    return OK;
}

int StrLen(HString *s)
{
    return s->length;
}

Status IsStrEqual(HString *s1,HString *s2)
{
    int i=0;
    for(i=0;i<s1->length && i< s2->length; i++)
    if(s1->ch[i]!= s2->ch[i]) return ERROR;
    if (i<s1->length || i<s2->length) return ERROR;
    else return OK;
}

int StrComp(HString *s,HString *t)
{
    for(i=0;i<s->length && i<t->length;i++)
    if(s->ch[i] !=t->ch[i])
        return (s->ch[i]-t->ch[i]);
    return s->length-t->length;
}

Status StrAssign(HString *s,char *sc)
{
    int i=0;
    //求sc的串长度i，串尾特征是sc[i]=‘\0’
    while(sc[i]!=‘\0’) i++;
    if(i>= s->strsize)
    {
        s->ch =(char *)realloc(s->ch, (i+1)*sizeof(char));
        if(!s->ch) return ERROR;
        s->strsize = i+1;
    }
    s->length = i;
    for(i=0;i<s->length;i++)
        s->ch[i] = sc[i];
    s->ch[i]=‘\0’;  //显式地补上串结束标志
    return OK;
}

Status StrConcat(HString *s,HString *s1, HString *s2)
{
// 将s1,s2拼接成s
    int i;
    if(s->strsize < (s1->length + s2->length))
    {
        s->ch = (char *)realloc(s->ch, (s1->length+s2->length+1) * sizeof(char));
        if(!s->ch) return ERROR;
        s->strsize = s1->length + s2->length+1;
    }
    i=0;
    while(i<s1->length)
    {
        s->ch[i]=s1->ch[i];
        i++;
    }
    while(i<s1->length+s2->length)
    {
        s->ch[i]=s2->ch[i-s1->length];
        i++;
    }
    s->ch[i]='\0';
    s->length = s1->length+s2->length;
    return OK;
}


Status StrSubstr(HString *subs,HString *s,int i,int j)
{
    int k;
    if(i<=0 || i> s->length || j<0 || j>s->length -i +1)
        return ERROR;
    if(subs->strsize < j)
    {
        subs->ch =(char *)realloc(subs->ch,(j+1)*sizeof(char));
        if(!subs->ch) return ERROR;
        subs->strsize =j+1;
    }
    for(k=0;k<j;k++) subs->ch[k] = s->ch[i-1+k];
    subs->ch[j]='\0';
    subs->length=j;
    return OK;
}

Status StrInsert(HString *s,int i,HString *t)
{
    int j;
    if(i<=0 || i>s->length+1) return ERROR; // 位置不合法出错
    if(s->strsize < s->length + t->length)
    { //空间不够
        s->ch = (char *)realloc(s->ch,(s->length+t->length)* sizeof(char));
        if(!s->ch) return ERROR;
        s->strsize = s->length + t->length;
    }
    for(j=s->length-1;j>=i-1;j--) //字符后移，腾挪空间
        s->ch[j+t->length] = s->ch[j];
    for(j=0;j<t->length;j++) // 插入t
        s->ch[i+j-1] = t->ch[j];
    s->length += t->length;
    return OK;
}

Status StrReplace(HString *s,int i,int j,HString *t)
{
    int k;
    if(i<=0 || i> s->length || j<=0 || j>s->length-i+1) return ERROR;
    if(j<t->length)
    {
        if(s->length+t->length-j>s->strsize)
        {
            s->ch =(char *)realloc(s->ch,(s->length+t->length-j+1)*sizeof(char));
            if(!s->ch) return ERROR;
            s->strsize = s->length + t->length –j+1;
        }
        for(k=s->length;k>=i+j-1;k--) //向后移，挪空间
            s->ch[k-j+t->length] = s->ch[k];
    }
    else for(k=i-1+j;k<s->length;k++) s->ch[k-j+t->length] = s->ch[k]; //向前移
    s->length = s->length + t->length -j; s->ch[s->length+1]='\0';
    for(k=0;k<t->length;k++)
        s->ch[k+i-1] = t->ch[k];
    return OK;
}

int StrIndex(HString *s,HString *t,int pos)
{
    int i,m,n;
    HString sub; StrInit (&sub);
    if(pos>0)
    {
        i=pos;n=StrLen(s);m=StrLen(t);
        while(i<=n-m+1)
        {
            StrSubstr(&sub,s,i,m);
            if(!IsStrEqual(&sub,t)) i++;
            else return i;
        }
    }
    return 0;
}

void StrRepSubstr(HString *s,HString *t,HString *v)
{
    int n,m,pos,i;
    HString newStr,sub; StrInit(&newStr);StrInit(&sub);
    n=StrLen(s);m=StrLen(t);pos=1; i=1;
    while(pos<=n-m+1 && i)
    {
        i=StrIndex(s,t,pos);
        if(i!=0)
        {
            StrSubstr(&sub,s,pos,i-pos); //sub存放 无需置换的子串
            StrConcat(&newStr,&newStr,&sub);
            StrConcat(&newStr,&newStr,v);
            pos=i+m;
        }
    }
    if(StrSubstr(&sub,s,pos,n-pos+1)) StrConcat(s,&newStr,&sub);
    else StrCopy(s,&newStr);
    return;
}






