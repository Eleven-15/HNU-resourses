#include<iostream>
using namespace std;
int main()
{
	int n,g,r;  //����
	cin>>n>>g>>r;
	int a[n+1];  //��������a�洢·������ʱ��
	for(int i=0;i<n+1;i++)  //��������
	{
		cin>>a[i];
	}
	int q;
	cin>>q;
	int b[q];  //��������b�洢����������ʱ��
	for(int i=0;i<q;i++)  //��������
	{
		cin>>b[i];
	}
	for(int x=0;x<q;x++)  //ѭ�����������������ʱ��
	{
		int time=b[x]+a[0];   //����time��¼����������·�ڵ�ʱ��
		for(int y=0;y<n;y++)   //ѭ����·��ʱʱ���ж�
		{
			int t=time/(g+r);   //����t�洢���̵Ʊ任����
			if((time>=t*(g+r))&&(time<t*(g+r)+g))
			{  //������ʱ��λ�ڿ�ͨ��ʱ����
				time=time+a[y+1];  //ʱ��ֱ�Ӽ�����һ��·��ͨ��ʱ��
			}
			else time=(t+1)*(g+r)+a[y+1];
			//�����ȵȵ��̵�����һ��·��ͨ��ʱ��
		}
		cout<<time<<' ';  //���
	}
	return 0;
 }

