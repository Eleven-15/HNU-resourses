#include<iostream>
using namespace std;

//շת�����(ŷ������㷨)
int measure1(int x, int y)
{	
	int z = y;
	while(x%y!=0)
	{			//�����������������Լ���������н�С���Ǹ���������������������Լ����
		z = x%y;
		x = y;
		y = z;	
	}
	return z;
}

void fun (){
	int n1, n2, max;
	cout << "����������: ";
	cin >> n1 >> n2;

	// ��ȡ������
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
	cout<<"շת������õ������Լ��Ϊ:"<<measure1(x,y)<<fun(x,y) <<endl;
	return 0;


}



