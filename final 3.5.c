#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_LENGTH 1000000

struct count
{
    int total_line;//������
    int comments_line;//ע������
    int blank_line;//������
    int code_line;//��������
    int function;//һ��������ܺ�����
    int maxlen;//ѡ������������
    int position;//ѡ���������λ��
};
//����һ���ṹ��

void getfile(char *ch) {
	int i = 0;
	FILE *fp = NULL;
	char fname[50];
	printf("�����ļ�·����");
	scanf("%s", fname);
	fp = fopen(fname, "r");
	if (NULL == fp)
	{
		printf("����");
		exit(1);
	}
	while ((ch[i] = getc(fp)) != EOF)
	{
		i++;
	}
	fclose(fp);
	fp = NULL;
	return;
}
//�ļ��������
struct count analyse(char s[])
{
    int i=0;
    int blank=1;//�����ж��Ƿ��ǿ���
    struct count p;
    int brace=0,brace2=0,sign=0,sign2=0,function_line=0,position=0;
    p.total_line=0;
    p.code_line=0;
    p.blank_line=0;
    p.comments_line=0;
    p.function=0;
    p.maxlen=0;
    p.position=0;
    while (s[i]!=EOF)
    {
        if (blank==1)//��Ϊһ�еĿ�ͷ��δ������ĸ�ַ�,�����������0
        {
            while (s[i]==' ')
                i++;//�ų����пո�ĸ���
            if (s[i]=='\n')//�ж��Ƿ��У�������˿ո���ǻ�������Ϊ����
            {
                p.total_line++;//������
                p.blank_line++;//�ո���
                i++;//������һ���ַ�
                blank=1;//���У�����һ�п�ͷ
            }else
            if (s[i]=='/'&&s[i+1]=='/')//�ж��Ƿ���ע����
            {
                p.comments_line++;
                while (s[i]!='\n'&&s[i]!=EOF)
                    i++;//����������ע������ֱ�Ӷ������з�
                p.total_line++;
                if (s[i]!=EOF)
                    i++;
                if (s[i]=='\n')
                    blank=1;
            }
            else
                blank=0;//�������ע���кͿ��У�����к����ж���
        }else
        {
            if (s[i]=='{')
            {
                brace++;
                if (sign2==1&&brace2==0)//���֮ǰ�Ѿ���һ�ԣ������ж����{}Ϊ����
                {
                    sign=1;
                    position=p.total_line;
                }
                i++;
            }
            else if (s[i]=='}')
            {
                brace--;
                if (brace==0&&sign==1)//һ�����������������{}������ж�
                {
                    if (p.maxlen<function_line)
                    {
                        p.maxlen=function_line+1;
                        p.position=position;
                    }
                    function_line=0;
                    position=0;
                    p.function++;
                    sign=0;
                    sign2=0;
                }
                i++;
            }
            else if (s[i]=='(')
            {
                brace2++;
                sign2=0;
                i++;
            }
            else if (s[i]==')')
            {
                brace2--;
                if (brace2==0&&brace==0&&sign==0&&s[i+1]!=';')
                    sign2=1;
                i++;
            }
            else if (s[i]=='\n')
            {
                if (sign==1&&brace!=0)
                    function_line++;
                p.total_line++;
                blank=1;
                i++;
            }
            else
                i++;
        }
    }
    p.code_line=p.total_line-p.blank_line-p.comments_line;
    return p;
}

struct count judge(struct count p)
{
    struct count result;
    float comments_rate,blank_rate,average_line;
    average_line=(float)p.code_line/p.function;
    comments_rate=(float)p.comments_line/p.total_line;
    blank_rate=(float)p.blank_line/p.total_line;
    if (average_line>=10&&average_line<=15)
        result.code_line=1;
    else if ((average_line>=8&&average_line<=9)||(average_line>=16&&average_line<=20))
        result.code_line=2;
    else if ((average_line>=5&&average_line<=7)||(average_line>=21&&average_line<=24))
        result.code_line=3;
    else result.code_line=4;

    if (comments_rate>=0.15&&comments_rate<=0.25)
        result.comments_line=1;
    else if ((comments_rate>=0.10&&comments_rate<=0.24)||(comments_rate>=0.26&&comments_rate<=0.30))
        result.comments_line=2;
    else if ((comments_rate>=0.05&&comments_rate<=0.09)||(comments_rate>=0.31&&comments_rate<=0.35))
        result.comments_line=3;
    else result.comments_line=4;

    if (blank_rate>=0.15&&blank_rate<=0.25)
        result.blank_line=1;
    else if ((blank_rate>=0.10&&blank_rate<=0.24)||(blank_rate>=0.26&&blank_rate<=0.30))
        result.blank_line=2;
    else if ((blank_rate>=0.05&&blank_rate<=0.09)||(blank_rate>=0.31&&blank_rate<=0.35))
        result.blank_line=3;
    else result.blank_line=4;

    return result;
}

void print (struct count p,struct count result,char name[])
{
    float comments_rate,blank_rate,average_line,code_rate;
    average_line=(float)p.code_line/p.function;
    code_rate=(float)p.code_line/p.total_line;
    comments_rate=(float)p.comments_line/p.total_line;
    blank_rate=(float)p.blank_line/p.total_line;
    printf("The results of analysing program file \"%s\"\n",name);
    printf("\n");
    printf("    Lines of code:%d\t\n",p.code_line);
    printf("    Lines of comments:%d\t\n",p.comments_line);
    printf("    Blank lines:%d\t\n",p.blank_line);
    printf("\n");
    printf("       Code      Comments      Space\t\n");
    printf("       ====      ========      =====\t\n");
    printf("    %f%%  %f%%  %f%%\t\n",code_rate*100,comments_rate*100,blank_rate*100);
    printf("\n");
    printf("    The program includes %d functions\n",p.function);
    printf("    The average length of a section of code is %.1f lines\n",average_line);
    printf("    The length of the deepest function is %d lines\n",p.maxlen);
    printf("    The position is %d lines\n",p.position);
    printf("\n");
    if (result.code_line==1)
        printf("    Grade A:Excellent routine size style.\n");
    else if (result.code_line==2)
        printf("    Grade B:Good routine size style.\n");
    else if (result.code_line==3)
        printf("    Grade C:Normal routine size style.\n");
    else if (result.code_line==4)
        printf("    Grade D:Bad routine size style.\n");

    if (result.comments_line==1)
        printf("    Grade A:Excellent commenting style.\n");
    else if (result.comments_line==2)
        printf("    Grade B:Good commenting style.\n");
    else if (result.comments_line==3)
        printf("    Grade C:Normal commenting style.n");
    else if (result.comments_line==4)
        printf("    Grade D:Bad commenting style.\n");

    if (result.blank_line==1)
        printf("    Grade A:Excellent white space style.\n");
    else if (result.blank_line==2)
        printf("    Grade B:Good white space style.\n");
    else if (result.blank_line==3)
        printf("    Grade C:Normal white space style.n");
    else if (result.blank_line==4)
        printf("    Grade D:Bad white space style.\n");
}

int main()
{
	char file[MAX_LENGTH], name[50];
	struct count p, result;
	printf("�����ļ�����");
	scanf("%s", name);
	printf("\n");
	getfile(file);
	p = analyse(file);
	result = judge(p);
	print(p ,result, name);
	return 0;
}