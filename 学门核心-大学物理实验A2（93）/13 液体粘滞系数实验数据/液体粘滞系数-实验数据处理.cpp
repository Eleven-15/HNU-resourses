#include<bits/stdc++.h>
using namespace std;
int main()
{
	//液体粘滞系数实验数据处理代码 
	//by wolf 9.30
	//rou是密度，yita是那个符号，Re的计算方式参见书本，其他字符与实验单对应 
	double rou=7.8*1000;
	double rou0=0.95*1000;
	double d=1.00125/1000;
	double g=9.8;
	double D=2/100;
	double v0=13.71/1000;//更改这里的v0数据为你自己算出来的数据 
	double yita=(rou-rou0)*g*d*d/(v0*18);
	double yita1=(rou-rou0)*g*d*d/(v0*18.0*(1.0+2.4*((d*10000)/(D*10000))));
	//这句有bug，希望有大佬能调一下 
	double Re=v0*d*rou0/yita;
	cout<<"yita="<<yita<<endl;
	cout<<"Re="<<Re<<endl;
	cout<<"yita1="<<yita1<<endl;//yita1由于c++浮点运算位数的限制无法计算，需要手算 
  return 0;
}

