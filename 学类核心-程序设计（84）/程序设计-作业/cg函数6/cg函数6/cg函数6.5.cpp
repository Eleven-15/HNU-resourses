#include<iostream>
#include<string>
 
using namespace std;
void fun(string sum)
{
	if (sum.length() == 1)
		cout << 0;
	else
	{
		int ret=0;
		for (int i = 1; i < sum.length(); i++)
		{
			ret = i;
			if (sum[i] != 48)
				break;
		}
		for (; ret < sum.length(); ret++)
			cout << sum[ret];
	}
 
}
int main()
{
	string sum;
	getline(cin, sum);
	fun(sum);
 
}
