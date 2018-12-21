
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
typedef struct {
    char *ch;   //���Ƿǿմ����򰴴�����+1����洢��
    int length; //����
    int strsize; //�洢�ռ��С���������Ľ�����
} HString;
// 1.��ʼ����
Status StrInit (HString *s);
// 2. ��ȡ���ĳ���
int StrLen(HString *s);
// 3. �Ƚ��������Ƿ����
Status IsStrEqual(HString *s,HString *t);
// 4. �Ƚ�������
Int StrComp(HString *s,HString *t);
//5. ���ַ�������sc�����ַ�������s
Status StrAssign (HString *s,char *sc);
//6. ��s1�� s2ƴ�ӳ�s
Status StrConcat (HString *s,HString *s1, HString *s2);
//7. ȡ�Ӵ�����s�дӵ�i���ַ���ʼ������j���ַ��ŵ�subs
Status StrSubstr(HString *subs, HString *s,int i,int j);
//8. ��s�ĵ�i���ַ�֮ǰ�����ַ���t
Status StrInsert (HString *s,int i,HString *t);
//9. ɾ��s�ĵ�i���ַ���ʼ������j���ַ�
Status StrDelete(HString *s,int i,int j);
//10. ���滻����s�ӵ�i���ַ���ʼj�������ַ����ַ���t�滻
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
    //��sc�Ĵ�����i����β������sc[i]=��\0��
    while(sc[i]!=��\0��) i++;
    if(i>= s->strsize)
    {
        s->ch =(char *)realloc(s->ch, (i+1)*sizeof(char));
        if(!s->ch) return ERROR;
        s->strsize = i+1;
    }
    s->length = i;
    for(i=0;i<s->length;i++)
        s->ch[i] = sc[i];
    s->ch[i]=��\0��;  //��ʽ�ز��ϴ�������־
    return OK;
}

Status StrConcat(HString *s,HString *s1, HString *s2)
{
// ��s1,s2ƴ�ӳ�s
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
    if(i<=0 || i>s->length+1) return ERROR; // λ�ò��Ϸ�����
    if(s->strsize < s->length + t->length)
    { //�ռ䲻��
        s->ch = (char *)realloc(s->ch,(s->length+t->length)* sizeof(char));
        if(!s->ch) return ERROR;
        s->strsize = s->length + t->length;
    }
    for(j=s->length-1;j>=i-1;j--) //�ַ����ƣ���Ų�ռ�
        s->ch[j+t->length] = s->ch[j];
    for(j=0;j<t->length;j++) // ����t
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
            s->strsize = s->length + t->length �Cj+1;
        }
        for(k=s->length;k>=i+j-1;k--) //����ƣ�Ų�ռ�
            s->ch[k-j+t->length] = s->ch[k];
    }
    else for(k=i-1+j;k<s->length;k++) s->ch[k-j+t->length] = s->ch[k]; //��ǰ��
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
            StrSubstr(&sub,s,pos,i-pos); //sub��� �����û����Ӵ�
            StrConcat(&newStr,&newStr,&sub);
            StrConcat(&newStr,&newStr,v);
            pos=i+m;
        }
    }
    if(StrSubstr(&sub,s,pos,n-pos+1)) StrConcat(s,&newStr,&sub);
    else StrCopy(s,&newStr);
    return;
}






