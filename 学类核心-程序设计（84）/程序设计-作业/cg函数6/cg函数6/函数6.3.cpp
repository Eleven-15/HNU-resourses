#include<iostream>
using namespace std;

//辗转相除法(欧几里德算法)
int measure1(int x, int y)
{	
	int z = y;
	while(x%y!=0)
	{			//定理：两个整数的最大公约数等于其中较小的那个数和两数相除余数的最大公约数。
		z = x%y;
		x = y;
		y = z;	
	}
	return z;
}

void fun (){
	int n1, n2, max;
	cout << "输入两个数: ";
	cin >> n1 >> n2;

	// 获取最大的数
	max = (n1 > n2) ? n1 : n2;
	do
	{
		if (max % n1 == 0 && max % n2 == 0)
		{
			cout <<  max<<endl;
			break;
		}
		else
			++max;
	} while (true);

}




int main(){
	int x,y;
	cin>>x;
	cin>>y;
	cout<<"辗转相除法得到的最大公约数为:"<<measure1(x,y)<<fun(x,y) <<endl;
	return 0;


}



