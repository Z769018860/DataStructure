#include <stdio.h>
#define MAXLEN 10000
typedef struct
{
    char sport;
    int gender;
    char schoolname;
    char result;
    int score
} resulttype;
typedef struct
{
    int malescore;
    int femalescore;
    int totalscore;
}scoretype;
void sum(resulttype result[]);
int main()
{
    resulttype result[MAXLEN];
    int i,n;
    scanf("%d",&n);
    for (i=0;i<n;i++)
    {
        scanf("%c%d%c%c%d",&result[i].sport,&result[i].gender,&result[i].schoolname,&result[i].result,&result[i].score);
    }
    sum(result);
    return 0;
}

void sum(resulttype result[])
{
    scoretype score[5];
    int j,i=0;
    for (j=0;j<5;j++)
    {
        score[i].totalscore=0;
        score[i].malescore=0;
        score[i].femalescore=0;
    }
    while(result[i].sport!=NULL)
    {
        switch(result[i].schoolname)
        {
        case 'A':
            score[0].totalscore+=result[i].score;
            if (result[i].gender==0) score[0].malescore+=result[i].score;
            else score[0].femalescore+=result[i].score;
        case 'B':
            score[1].totalscore+=result[i].score;
            if (result[i].gender==0) score[1].malescore+=result[i].score;
            else score[1].femalescore+=result[i].score;
        case 'C':
            score[2].totalscore+=result[i].score;
            if (result[i].gender==0) score[2].malescore+=result[i].score;
            else score[2].femalescore+=result[i].score;
        case 'D':
            score[3].totalscore+=result[i].score;
            if (result[i].gender==0) score[3].malescore+=result[i].score;
            else score[3].femalescore+=result[i].score;
        case 'E':
            score[4].totalscore+=result[i].score;
            if (result[i].gender==0) score[4].malescore+=result[i].score;
            else score[4].femalescore+=result[i].score;
        }
        i++;
    }
    for (i=0;i<5;i++)
    {
        printf("School %d :\n",i);
        printf("Total score:%d\n",score[i].totalscore);
        printf("Male score:%d\n",score[i].malescore);
        printf("Female score:%d\n",score[i].femalescore);
    }
}
