#include<iostream>
using namespace std;
int main()
{
	int T,N,minX,maxX;  //����
	cin>>T;
	for(int i=0;i<T;i++)
	{
		int c[2]={0,0};  //��������c�洢ż���������ĸ���
		cin>>N>>minX>>maxX;
		int b[N][2];    //��������b�洢�����wi��bi
		for(int x=0;x<N;x++)   //�������wi��bi
		{
			for(int y=0;y<2;y++)
			{
				cin>>b[x][y];
			}
		}
		for(int s=minX;s<=maxX;s++)   //��minX��maxXѭ���ж�
		{
			int t=s;   //����tֵ�洢������������ֵ
			for(int x=0;x<N;x++)  //���и����ѭ������
			{
				t=t*b[x][0]+b[x][1];
			}
			if(t%2==0) c[0]++;   //�ж���ż����¼����
			else c[1]++;
	    }
	    cout<<c[0]<<' '<<c[1]<<endl;  //���
	}
}

