
#include <stdio.h>
#include <string.h>
#include <malloc.h>

#define OK 1
#define TRUE 1
#define FALSE 0
#define ERROR 0
#define INFEASIBLE -1

#define DestroyString ClearString // DestroyString()��ClearString()������ͬ
#define MAX_STR_LEN 40 // �û�����255(1���ֽ�)���ڶ�����󴮳�
typedef char SString[MAX_STR_LEN+1]; // 0�ŵ�Ԫ��Ŵ��ĳ���
typedef int Status; // Status�Ǻ���������,��ֵ�Ǻ������״̬���룬��OK��
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
    {// s2���ض�
        strncpy(&t[1],&s1[1],s1[0]);
        strncpy(&t[s1[0]+1],&s2[1],MAXSTRLEN-s1[0]);
        t[0]=MAXSTRLEN;t[MAXSTRLEN+1]='\0';
        uncut=FALSE;
    }
    else
    { //s1[0] = MAXSTRLEN����s2���ضϣ���ȡs1
    strncpy(&t[1],&s1[1],MAXSTRLEN);
    t[0]=MAXSTRLEN;t[MAXSTRLEN+1]='\0';
    uncut=FALSE;
    }
    return uncut;
}

//��s�дӵ�pos���ַ���ʼ������len���ַ��ŵ�sub��
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
//�����а����ڴ� s �ж� t��û�е��ַ����ɵ��´� r
{
    int i,k,j;
    StrAssign(r,'');
    for(i=1;i<=Strlen(s);i++)
    {
    StrAssign(c,SubString(s,i,1));
    for(j=1;j<i&&StrCompare(c,SubString(s,j,1));j++);
    //�ж� s�ĵ�ǰ�ַ� c �Ƿ��һ�γ���
    if(i==j)
    {
        for(k=1;k<=Strlen(t)&&StrCompare(c,SubString(t,k,1));k++);
        //�жϵ�ǰ�ַ��Ƿ������ t ��
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

