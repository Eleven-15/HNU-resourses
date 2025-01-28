#include<iostream>
using namespace std;
int main()
{
	int n,g,r;  //定义
	cin>>n>>g>>r;
	int a[n+1];  //定义数组a存储路段运行时间
	for(int i=0;i<n+1;i++)  //输入数据
	{
		cin>>a[i];
	}
	int q;
	cin>>q;
	int b[q];  //定义数组b存储公交车出发时间
	for(int i=0;i<q;i++)  //输入数据
	{
		cin>>b[i];
	}
	for(int x=0;x<q;x++)  //循环，输出公交车到达时间
	{
		int time=b[x]+a[0];   //定义time记录公交车到达路口的时间
		for(int y=0;y<n;y++)   //循环，路口时时间判断
		{
			int t=time/(g+r);   //定义t存储红绿灯变换次数
			if((time>=t*(g+r))&&(time<t*(g+r)+g))
			{  //当到达时间位于可通行时间内
				time=time+a[y+1];  //时间直接加上下一段路程通过时间
			}
			else time=(t+1)*(g+r)+a[y+1];
			//否则先等到绿灯在下一段路程通过时间
		}
		cout<<time<<' ';  //输出
	}
	return 0;
 }

