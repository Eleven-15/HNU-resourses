#include<iostream>
using namespace std;
int main()
{
	int T,N,minX,maxX;  //定义
	cin>>T;
	for(int i=0;i<T;i++)
	{
		int c[2]={0,0};  //定义数组c存储偶数和奇数的个数
		cin>>N>>minX>>maxX;
		int b[N][2];    //定义数组b存储各层的wi和bi
		for(int x=0;x<N;x++)   //输入各层wi和bi
		{
			for(int y=0;y<2;y++)
			{
				cin>>b[x][y];
			}
		}
		for(int s=minX;s<=maxX;s++)   //从minX到maxX循环判断
		{
			int t=s;   //定义t值存储最初输入的数据值
			for(int x=0;x<N;x++)  //进行各层的循环计算
			{
				t=t*b[x][0]+b[x][1];
			}
			if(t%2==0) c[0]++;   //判断奇偶，记录个数
			else c[1]++;
	    }
	    cout<<c[0]<<' '<<c[1]<<endl;  //输出
	}
}

