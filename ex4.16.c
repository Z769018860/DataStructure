
#include <stdio.h>
#include <string.h>
#include <malloc.h>

#define OK 1
#define TRUE 1
#define FALSE 0
#define ERROR 0
#define INFEASIBLE -1

#define DestroyString ClearString // DestroyString()��ClearString()������ͬ
#define MAXstrlen 40 // �û�����255(1���ֽ�)���ڶ�����󴮳�
typedef char SString[MAXstrlen+1]; // 0�ŵ�Ԫ��Ŵ��ĳ���
typedef int Status; // Status�Ǻ���������,��ֵ�Ǻ������״̬���룬��OK��
SString r;
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
    {// s2���ض�
        strncpy(&t[1],&s1[1],s1[0]);
        strncpy(&t[s1[0]+1],&s2[1],MAXstrlen-s1[0]);
        t[0]=MAXstrlen;t[MAXstrlen+1]='\0';
        uncut=FALSE;
    }
    else
    { //s1[0] = MAXstrlen����s2���ضϣ���ȡs1
    strncpy(&t[1],&s1[1],MAXstrlen);
    t[0]=MAXstrlen;t[MAXstrlen+1]='\0';
    uncut=FALSE;
    }
    return uncut;
}

//��s�дӵ�pos���ַ���ʼ������len���ַ��ŵ�sub��
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
    if(s[i] == t[j]) {i++;j++;} //�����ȽϺ���ַ�
    else {i=i-j+2;j=1;}
    //ָ��i����(����ǰƥ����ʼλ�õ���һλ��)���¿�ʼƥ��
    }
    if(j>t[0]) return i-t[0];
    //ƥ��ɹ��������Ӵ�t��λ��
    else return 0;
}

Status StrAssign(SString T,char *chars)
{ // ����һ����ֵ����chars�Ĵ�T
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


int StrCompare(SString S,SString T,int len)
{// ��ʼ��������S��T���ڡ������������S>T���򷵻�ֵ>0����S=T���򷵻�ֵ=0����S<T���򷵻�ֵ<0
    int i;
    for(i=0;i<len;i++)
        if(S[i]!=T[i])
            return ((S[i]-T[i])>0)?1:-1;
    return 0;
}

int main()
{
    SString s,t,r;
    char c;
    int i=0,j=0,len1,len2,len;
    while ((c=getchar())!=' ')
    {
        s[i]=c;
        i++;
    }
    len1=i;
    while ((c=getchar())!='\n')
    {
        t[j]=c;
        j++;
    }
    len2=j;
    if (len1>=len2) len=len1;
    else len=len2;
    printf("%d\n",StrCompare(s,t,len));
    return 0;
}

