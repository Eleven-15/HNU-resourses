#include <iostream>
#include <cstdlib>
using namespace std;
class matrix
{
private:
    int rows, cols;
    int **p;
public:
    matrix();
    matrix(int &M, int &N);
    matrix(matrix &A, int m, int n);
    ~matrix();

    matrix multi(int x);   // 数乘
    int det();           // 计算行列式
    void out();    //输出矩阵
    void input();

    matrix operator+(matrix &another); //重载加法运算实现矩阵相加
    matrix operator*(matrix &another); //重载乘法运算实现矩阵相乘
};
matrix::matrix(int &M, int &N)
{
    rows=M, cols=N;
    p=new int*[rows];
    for(int i=0;i<M;i++)
    {
        p[i]=new int[cols];
    }
}

matrix::matrix(matrix &A, int m, int n)   //从矩阵A中删除第m行第n列后得到新的矩阵
{
    rows=A.rows-1,  cols=A.cols-1;
            p=new  int*[rows];
            for(int  i=0;i<rows;i++)
            {
                    p[i]=new  int[cols];
            }
            for(int  i=0;  i<m;  i++)
                    for(int  j=0;  j<n;  j++)
                          p[i][j]=A.p[i][j];
    
            for(int  i=0;  i<m;  i++)
                    for(int  j=n+1;  j<A.cols;  j++)
                          p[i][j-1]=A.p[i][j];
    
            for(int  i=m+1;  i<A.rows;  i++)
                    for(int  j=0;  j<n;  j++)
                          p[i-1][j]=A.p[i][j];
    
            for(int  i=m+1;  i<A.rows;  i++)
                    for(int  j=n+1;  j<A.cols;  j++)
                          p[i-1][j-1]=A.p[i][j];

}

matrix::~matrix()
{
    for(int i=0; i<rows; i++)
        delete[] p[i];

    delete[] p;
}

matrix matrix::multi(int x)   // 数乘
{
    matrix tmp(rows, cols);
    for(int  i=0;  i<rows;  i++)
                    for(int  j=0;  j<cols;  j++)
                            tmp.p[i][j]=p[i][j]*x;
    return tmp;
}

void matrix::out()    //输出矩阵
{
     /* 逐行输出，数据间用空格分隔 */
    for(int  i=0;  i<rows;  i++)
    {
             for(int  j=0;  j<cols;  j++)
             {
                   cout<<p[i][j]<<" ";
             }
    cout<<endl;
    }

}

void matrix::input()
{
    for(int i=0; i<rows; i++)
        for(int j=0; j<cols; j++)
            cin>>p[i][j];

}

matrix matrix::operator+(matrix &another) 
{
    matrix tmp(rows, cols);
    for(int  i=0;  i<rows;  i++)
                    for(int  j=0;  j<cols;  j++)
                            tmp.p[i][j]=p[i][j]+another.p[i][j];
    return tmp;
}

matrix matrix::operator*(matrix &another)  //重载乘法运算实现矩阵相乘
{
    matrix tmp(rows, another.cols);
    for(int i=0; i<rows; i++)
    {
        for(int j=0; j<another.cols; j++)
        {
           /* 计算A矩阵的第i行与B矩阵的第j列元素对应相乘后之和，作为新矩阵的第i行第j列元素的值 */
           tmp.p[i][j]=0;
           for (int k=0;k<cols;k++)
           {
               tmp.p[i][j]+=(p[i][k]*another.p[k][j]);
           }

        }
    }
    return tmp;
}

int matrix::det()
{
    if (rows==1)
        return p[0][0];
    else
    {
        int result=0, flag;
        for(int i=0; i<cols; i++)
        {
            flag=(i%2)?-1:1;
            matrix tmp(*this, 0, i);
            result=result+flag*p[0][i]*tmp.det();    // 使用代数余子式求行列式的值, 递归
        }
        return result;
    }
}
int main()
{
    int M,N;
    cin>>M>>N;
    matrix mA(M, N); 
    mA.input();
    
//	int x;
//    cin>>x;
//
//    matrix mm1=mA.multi(x);
//
//    mm1.out();

    int K, L;
    cin>>K>>L;
    matrix mB(K, L);  
    mB.input();


//    if (M==K && N==L)
//    {
//        matrix mm2=mA+mB;
//        mm2.out();
//    }
    
    cout<<endl; 
    if (N==K)
    {
        matrix mm3=mA*mB;
        mm3.out();
    }
//
//    if (M==N)
//        cout<<mA.det()<<endl;
//
//    if (K==L)
//        cout<<mB.det()<<endl;

    return 0;
}


