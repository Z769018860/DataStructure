#include <iostream>
#include <cstring>
using namespace std;
#define OK 1
#define TRUE 1
#define FALSE 0
#define ERROR 0
#define INFEASIBLE -1

#define DestroyString ClearString // DestroyString()与ClearString()作用相同
#define MAXstrlen 40 // 用户可在255(1个字节)以内定义最大串长
typedef char SString[MAXstrlen+1]; // 0号单元存放串的长度
typedef int Status; // Status是函数的类型,其值是函数结果状态代码，如OK等
SString s,t,v;
int StrConcat(SString t,SString s1,SString s2)
{
    int uncut;
    if (s1[0]+s2[0] <= MAXstrlen)
    {
        strncpy(&t[1],&s1[1],s1[0]);
        strncpy(&t[s1[0]+1],&s2[1],s2[0]);
        t[0]=s1[0]+s2[0];t[t[0]+1]='\0';
        uncut= TRUE;
    }
    else if(s1[0]<MAXstrlen)
    {// s2被截断
        strncpy(&t[1],&s1[1],s1[0]);
        strncpy(&t[s1[0]+1],&s2[1],MAXstrlen-s1[0]);
        t[0]=MAXstrlen;t[MAXstrlen+1]='\0';
        uncut=FALSE;
    }
    else
    { //s1[0] = MAXstrlen，故s2被截断，仅取s1
    strncpy(&t[1],&s1[1],MAXstrlen);
    t[0]=MAXstrlen;t[MAXstrlen+1]='\0';
    uncut=FALSE;
    }
    return uncut;
}

//将s中从第pos个字符开始的连续len个字符放到sub中
Status StrSubStr(SString sub,SString s,int pos,int len)
{
 if(pos<1 || pos>s[0] || len<0 ||len> s[0]-pos+1) return ERROR;
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
    if(strlen(chars)>MAXstrlen)
        return ERROR;
    else
    {
        T[0]=strlen(chars);
        for(i=1;i<=T[0];i++)
            T[i]=*(chars+i-1);
        return OK;
    }
}
Status StrEmpty(SString S)
{ // 若S为空串，则返回TRUE，否则返回FALSE
    if(S[0]==0)
        return TRUE;
    else
        return FALSE;
}

int StrCompare(SString S,SString T)
{// 初始条件：串S和T存在。操作结果：若S>T，则返回值>0；若S=T，则返回值=0；若S<T，则返回值<0
    int i;
    for(i=1;i<=S[0]&&i<=T[0];++i)
        if(S[i]!=T[i])
            return S[i]-T[i];
    return S[0]-T[0];
}
Status StrInsert(SString S,int pos,SString T)
{ // 初始条件：串S和T存在，1≤pos≤strlen(S)+1
    // 操作结果：在串S的第pos个字符之前插入串T。完全插入返回TRUE，部分插入返回FALSE
    int i;
    if(pos<1||pos>S[0]+1)
        return ERROR;
    if(S[0]+T[0]<=MAXstrlen)
    { // 完全插入
        for(i=S[0];i>=pos;i--)
            S[i+T[0]]=S[i];
        for(i=pos;i<pos+T[0];i++)
            S[i]=T[i-pos+1];
        S[0]+=T[0];
        return TRUE;
    }
    else
    { // 部分插入
        for(i=MAXstrlen;i>=pos+T[0];i--)
            S[i]=S[i-T[0]];
        for(i=pos;i<pos+T[0]&&i<=MAXstrlen;i++)
            S[i]=T[i-pos+1];
        S[0]=MAXstrlen;
        return FALSE;
    }
}
Status StrDelete(SString S,int pos,int len)
{ // 初始条件：串S存在，1≤pos≤StrLength(S)-len+1
    // 操作结果：从串S中删除第pos个字符起长度为len的子串
    int i;
    if(pos<1||pos>S[0]-len+1||len<0)
        return ERROR;
    for(i=pos+len;i<=S[0];i++)
        S[i-len]=S[i];
    S[0]-=len;
    return OK;
}


int String_Replace(SString &S,SString T,SString V)
//将串 S 中所有子串 T 替换为 V,并返回置换次数
{
    int n,i,j,k,l;
for(n=0,i=1;i<=S[0]-T[0]+1;i++)
{
for(j=i,k=1;T[k]&&S[j]==T[k];j++,k++);
if(k>T[0]) //找到了与 T 匹配的子串:分三种情况处理
{
if(T[0]==V[0])
for(l=1;l<=T[0];l++) //新子串长度与原子串相同时:直接替换
S[i+l-1]=V[l];
else if(T[0]<V[0]) //新子串长度大于原子串时:先将后部右移
{
for(l=S[0];l>=i+T[0];l--)
S[l+V[0]-T[0]]=S[l];
for(l=1;l<=V[0];l++)
S[i+l-1]=V[l];
}
else //新子串长度小于原子串时:先将后部左移
{
for(l=i+V[0];l<=S[0]+V[0]-T[0];l++)
S[l]=S[l-V[0]+T[0]];
for(l=1;l<=V[0];l++)
S[i+l-1]=V[l];
}
S[0]=S[0]-T[0]+V[0];
i+=V[0];n++;
}//if
}//for
return n;
}//String_Replac

int main()
{
    int n;
    cin>>s;
    cin>>t;
    cin>>v;
    if ((n=String_Replace(&s,t,v))!=0)
        cout<<s<<endl<<n<<endl;
    else
        cout<<"ERROR!"<<endl;
    return 0;
}

