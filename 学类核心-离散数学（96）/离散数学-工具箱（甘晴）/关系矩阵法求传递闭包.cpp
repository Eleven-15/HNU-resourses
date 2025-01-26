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

    matrix multi(int x);   
    void out();    
    void input();

    matrix operator+(matrix &another); 
    matrix operator*(matrix &another);  
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

matrix::matrix(matrix &A, int m, int n)  
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

void matrix::out()    
{
    for(int  i=0;  i<rows;  i++)
    {
             for(int  j=0;  j<cols;  j++)
             {
             	if (p[i][j]!=0) cout<<1<<" ";
             	else cout<<0<<" ";
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

matrix matrix::operator*(matrix &another)  
{
    matrix tmp(rows, another.cols);
    for(int i=0; i<rows; i++)
    {
        for(int j=0; j<another.cols; j++)
        {
           tmp.p[i][j]=0;
           for (int k=0;k<cols;k++)
           {
               tmp.p[i][j]+=(p[i][k]*another.p[k][j]);
           }

        }
    }
    return tmp;
}

int main()
{
    int M;
    cin>>M;
    matrix mA(M, M); 
    mA.input();

	cout<<endl;
    matrix mm3=mA;
    matrix mtr=mA;
    for(int i=2;i<6;i++)
	{
		cout<<"MtR"<<i-1<<"="<<endl;
		mtr.out();
		mm3=mA*mm3;
		cout<<"MR("<<i<<")="<<endl;
		mm3.out();
		cout<<endl;
		mtr=mtr+mm3;
		cout<<endl;
		for (int j=0;j<=20;j++) cout<<"-";
		cout<<endl;
	 } 
	system("pause"); 


    return 0;
}

