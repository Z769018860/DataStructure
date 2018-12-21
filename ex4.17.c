#include <stdio.h>
#include <string.h>
#include <malloc.h>

#define MAXLEN 40

// ��strRes�е�t�滻Ϊs���滻�ɹ�����1�����򷵻�0��
int Replace(char s[],char t[], char v[]) {
    int i,flag = 0;
    char *p,*q,*ts;
    for(i = 0; s[i]; ++i) {
        if(s[i] == t[0]) {
            p = s + i;
            q = t;
            while(*q && (*p++ == *q++));
            if(*q == '\0') {
                ts = (char *)malloc(strlen(s) + 1);
                strcpy(ts,p);
                s[i] = '\0';
                strcat(s,v);
                strcat(s,ts);
                free(ts);
                flag = 1;
            }
        }
    }
    return flag;
}

int main() {
    char s[MAXLEN],t[MAXLEN],v[MAXLEN];
    scanf("%s",s);
    scanf("%s",t);
    scanf("%s",v);
    printf("�滻ǰ:%s\n",s);
    if(Replace(s,t,v)) printf("�滻��:%s\n",s);
    else printf("û���κ��滻��\n");
    return 0;
}
