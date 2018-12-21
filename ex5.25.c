#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 100
typedef int ElemType;
typedef struct
{
    int i,j;            // 行下标,列下标
    ElemType e;         // 非零元素值
}Triple;

typedef struct
{
    Triple data[MAXSIZE+1];     // 非零元三元组表,data[0]未用
    int mu,nu,tu;               // 矩阵的行数、列数和非零元个数
}TSMatrix;


// 创建稀疏矩阵M
int CreateSMatrix(TSMatrix *M)
{
    int i,m,n;
    ElemType e;
    int k;

    printf("请输入矩阵的行数, 列数, 非零元素个数：（以逗号隔开）\n");
    scanf("%d,%d,%d", &(*M).mu, &(*M).nu, &(*M).tu);
    (*M).data[0].i=0;
    for(i = 1; i <= (*M).tu; i++)
    {
        do
        {
            printf("请按行序输入第 %d 个非零元素的行( 1 ～ %d )," "列 ( 1 ～ %d ),元素值：(以逗号隔开)\n", i , (*M).mu, (*M).nu);
            scanf("%d,%d,%d", &m, &n, &e);
            k=0;
            if(m < 1 || m > (*M).mu || n < 1 || n > (*M).nu)
                k=1;
            if(m < (*M).data[i-1].i || m == (*M).data[i-1].i && n <= (*M).data[i-1].j)
                k=1;
        }while(k);
        (*M).data[i].i = m; //行下标
        (*M).data[i].j = n; //列下标
        (*M).data[i].e = e; //该下标所对应的值
    }
    return 1;
}

// 销毁稀疏矩阵M，所有元素置空
void DestroySMatrix(TSMatrix *M)
{
    (*M).mu=0;
    (*M).nu=0;
    (*M).tu=0;
}


// 输出稀疏矩阵M
void PrintSMatrix(TSMatrix M)
{
    int i;
    printf("\n %d 行, %d 列， %d 个非零元素。\n",M.mu, M.nu, M.tu);
    printf("======================\n");
    printf("%4s %4s %8s\n", "i", "j", "e");
    printf("======================\n");
    for(i=1;i<=M.tu;i++)
        printf("%4d %4d %8d\n", M.data[i].i, M.data[i].j, M.data[i].e);
    printf("======================\n");
}

// 由稀疏矩阵M复制得到T
int CopySMatrix(TSMatrix M,TSMatrix *T)
{
    (*T)=M;
    return 1;
}

// AddSMatrix函数要用到
int comp(int c1,int c2)
{
    int i;
    if(c1<c2)
        i=1;
    else if(c1==c2)
        i=0;
    else
        i=-1;
    return i;
}

// 求两个稀疏矩阵的和Q=M+N
int AddSMatrix(TSMatrix M,TSMatrix N,TSMatrix *Q)
{
    Triple *Mp,*Me,*Np,*Ne,*Qh,*Qe;
    if(M.mu!=N.mu)
        return 0;
    if(M.nu!=N.nu)
        return 0;
    (*Q).mu=M.mu;
    (*Q).nu=M.nu;
    Mp=&M.data[1];      // Mp的初值指向矩阵M的非零元素首地址
    Np=&N.data[1];      // Np的初值指向矩阵N的非零元素首地址
    Me=&M.data[M.tu];   // Me指向矩阵M的非零元素尾地址
    Ne=&N.data[N.tu];   // Ne指向矩阵N的非零元素尾地址
    Qh=Qe=(*Q).data;    // Qh、Qe的初值指向矩阵Q的非零元素首地址的前一地址
    while(Mp <= Me && Np <= Ne)
    {
        Qe++;
        switch(comp(Mp->i,Np->i))
        {
        case  1:
            *Qe=*Mp;
            Mp++;
            break;
        case  0:
            // M、N矩阵当前非零元素的行相等,继续比较列
            switch(comp(Mp->j,Np->j))
            {
            case  1:
                *Qe=*Mp;
                Mp++;
                break;
            case  0:
                *Qe=*Mp;
                Qe->e+=Np->e;
                if(!Qe->e) // 元素值为0，不存入压缩矩阵
                    Qe--;
                Mp++;
                Np++;
                break;
            case -1:
                *Qe=*Np;
                Np++;
            }
            break;
        case -1:
            *Qe=*Np;
            Np++;
        }
    }
    if(Mp>Me) // 矩阵M的元素全部处理完毕
        while(Np<=Ne)
        {
            Qe++;
            *Qe=*Np;
            Np++;
        }
    if(Np>Ne) // 矩阵N的元素全部处理完毕
        while(Mp<=Me)
        {
            Qe++;
            *Qe=*Mp;
            Mp++;
        }
    (*Q).tu=Qe-Qh; // 矩阵Q的非零元素个数
    return 1;
}

//求两个稀疏矩阵的差Q=M-N
int SubtSMatrix(TSMatrix M,TSMatrix N,TSMatrix *Q)
{
    int i;
    for(i=1;i<=N.tu;i++)
        N.data[i].e*=-1;
    AddSMatrix(M,N,Q);
    return 1;
}

//求两个稀疏矩阵的乘积Q = M*N
int MultSMatrix(TSMatrix M,TSMatrix N,TSMatrix *Q)
{
    // h,l分别为矩阵Q的行、列值,Qn为矩阵Q的非零元素个数，初值为0
    int i,j,h=M.mu,l=N.nu,Qn=0;
    ElemType *Qe;
    if(M.nu!=N.mu)
        return 0;
    (*Q).mu=M.mu;
    (*Q).nu=N.nu;
    Qe=(ElemType *)malloc(h*l*sizeof(ElemType)); // Qe为矩阵Q的临时数组
    // 矩阵Q的第i行j列的元素值存于*(Qe+(i-1)*l+j-1)中，初值为0
    for(i=0;i<h*l;i++)
        *(Qe+i)=0; // 赋初值0
    for(i=1;i<=M.tu;i++) // 矩阵元素相乘，结果累加到Qe
        for(j=1;j<=N.tu;j++)
            if(M.data[i].j==N.data[j].i)
                *(Qe+(M.data[i].i-1)*l+N.data[j].j-1) +=
                    M.data[i].e * N.data[j].e;
    for(i=1;i<=M.mu;i++)
        for(j=1;j<=N.nu;j++)
            if(*(Qe+(i-1)*l+j-1)!=0)
            {
                Qn++;
                (*Q).data[Qn].e=*(Qe+(i-1)*l+j-1);
                (*Q).data[Qn].i=i;
                (*Q).data[Qn].j=j;
            }
    free(Qe);
    (*Q).tu=Qn;
    return 1;
}

//稀疏矩阵的转置
int transposeSMatrix(TSMatrix M,TSMatrix *T)
{
    int p,q,col;
    (*T).mu=M.nu;
    (*T).nu=M.mu;
    (*T).tu=M.tu;
    if((*T).tu)
    {
        q=1;
        for(col=1;col<=M.nu;++col)   //先将列转换成行
            for(p=1;p<=M.tu;++p) //再将行转换成列
                if(M.data[p].j==col)
                {
                    (*T).data[q].i=M.data[p].j;
                    (*T).data[q].j=M.data[p].i;
                    (*T).data[q].e=M.data[p].e;
                    ++q;
                }
    }
    return 1;
}


// 快速求稀疏矩阵M的转置矩阵
int FasttransposeSMatrix(TSMatrix M,TSMatrix *T)
{
    int p,q,t,col,*num,*cpot;
    num=(int *)malloc((M.nu+1)*sizeof(int));    // 生成数组（[0]不用）
    cpot=(int *)malloc((M.nu+1)*sizeof(int));   // 生成数组（[0]不用）
    (*T).mu=M.nu;
    (*T).nu=M.mu;
    (*T).tu=M.tu;
    if((*T).tu)
    {
        for(col=1;col<=M.nu;++col)
            num[col]=0; // 设初值
        for(t=1;t<=M.tu;++t) // 求M中每一列含非零元素个数
            ++num[M.data[t].j];
        cpot[1]=1;
        // 求第col列中第一个非零元在(*T).data中的序号
        for(col=2;col<=M.nu;++col)
            cpot[col]=cpot[col-1]+num[col-1];
        for(p=1;p<=M.tu;++p)
        {
            col=M.data[p].j;
            q=cpot[col];
            (*T).data[q].i=M.data[p].j;
            (*T).data[q].j=M.data[p].i;
            (*T).data[q].e=M.data[p].e;
            ++cpot[col];
        }
    }
    free(num);
    free(cpot);
    return 1;
}


int main()
{
    TSMatrix A,B,C;
    CreateSMatrix(&A);
    printf("矩阵A：\n");
    PrintSMatrix(A);
    printf("\n\n");
    CopySMatrix(A,&B);
    printf("矩阵B:\n");
    PrintSMatrix(B);
    printf("\n\n");
    printf("矩阵C1为：(A+B): \n");
    AddSMatrix(A,B,&C);
    PrintSMatrix(C);
    DestroySMatrix(&C);
    printf("\n\n");
    printf("矩阵C2为 ：(A-B): \n");
    SubtSMatrix(A,B,&C);
    PrintSMatrix(C);
    DestroySMatrix(&C);
    printf("\n\n");
    printf("矩阵C3为 ：(A的转置): \n");
    transposeSMatrix(A,&C);
    PrintSMatrix(C);
    return 0;
}
