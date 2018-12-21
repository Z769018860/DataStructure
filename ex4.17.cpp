#include <iostream>
#include <cstring>
using namespace std;
#define OK 1
#define TRUE 1
#define FALSE 0
#define ERROR 0
#define INFEASIBLE -1

#define DestroyString ClearString // DestroyString()��ClearString()������ͬ
#define MAXstrlen 40 // �û�����255(1���ֽ�)���ڶ�����󴮳�
typedef char SString[MAXstrlen+1]; // 0�ŵ�Ԫ��Ŵ��ĳ���
typedef int Status; // Status�Ǻ���������,��ֵ�Ǻ������״̬���룬��OK��
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
Status StrEmpty(SString S)
{ // ��SΪ�մ����򷵻�TRUE�����򷵻�FALSE
    if(S[0]==0)
        return TRUE;
    else
        return FALSE;
}

int StrCompare(SString S,SString T)
{// ��ʼ��������S��T���ڡ������������S>T���򷵻�ֵ>0����S=T���򷵻�ֵ=0����S<T���򷵻�ֵ<0
    int i;
    for(i=1;i<=S[0]&&i<=T[0];++i)
        if(S[i]!=T[i])
            return S[i]-T[i];
    return S[0]-T[0];
}
Status StrInsert(SString S,int pos,SString T)
{ // ��ʼ��������S��T���ڣ�1��pos��strlen(S)+1
    // ����������ڴ�S�ĵ�pos���ַ�֮ǰ���봮T����ȫ���뷵��TRUE�����ֲ��뷵��FALSE
    int i;
    if(pos<1||pos>S[0]+1)
        return ERROR;
    if(S[0]+T[0]<=MAXstrlen)
    { // ��ȫ����
        for(i=S[0];i>=pos;i--)
            S[i+T[0]]=S[i];
        for(i=pos;i<pos+T[0];i++)
            S[i]=T[i-pos+1];
        S[0]+=T[0];
        return TRUE;
    }
    else
    { // ���ֲ���
        for(i=MAXstrlen;i>=pos+T[0];i--)
            S[i]=S[i-T[0]];
        for(i=pos;i<pos+T[0]&&i<=MAXstrlen;i++)
            S[i]=T[i-pos+1];
        S[0]=MAXstrlen;
        return FALSE;
    }
}
Status StrDelete(SString S,int pos,int len)
{ // ��ʼ��������S���ڣ�1��pos��StrLength(S)-len+1
    // ����������Ӵ�S��ɾ����pos���ַ��𳤶�Ϊlen���Ӵ�
    int i;
    if(pos<1||pos>S[0]-len+1||len<0)
        return ERROR;
    for(i=pos+len;i<=S[0];i++)
        S[i-len]=S[i];
    S[0]-=len;
    return OK;
}


int String_Replace(SString &S,SString T,SString V)
//���� S �������Ӵ� T �滻Ϊ V,�������û�����
{
    int n,i,j,k,l;
for(n=0,i=1;i<=S[0]-T[0]+1;i++)
{
for(j=i,k=1;T[k]&&S[j]==T[k];j++,k++);
if(k>T[0]) //�ҵ����� T ƥ����Ӵ�:�������������
{
if(T[0]==V[0])
for(l=1;l<=T[0];l++) //���Ӵ�������ԭ�Ӵ���ͬʱ:ֱ���滻
S[i+l-1]=V[l];
else if(T[0]<V[0]) //���Ӵ����ȴ���ԭ�Ӵ�ʱ:�Ƚ�������
{
for(l=S[0];l>=i+T[0];l--)
S[l+V[0]-T[0]]=S[l];
for(l=1;l<=V[0];l++)
S[i+l-1]=V[l];
}
else //���Ӵ�����С��ԭ�Ӵ�ʱ:�Ƚ�������
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

