#include<iostream>
using namespace std;
int main()
{
    int n,k;
    cin>>n>>k;//�����������Ը��ͻ����
    int a[n];//��Ӧ���ӵļ�����
    for(int i=0;i<n;i++)
    {
        cin>>a[i];
    }
    int b[k][2];//��ͻ���ӵı��
    for(int i=0;i<k;i++)
    {
        for(int j=0;j<2;j++)
        {
            cin>>b[i][j];
        }
    }

    for(int t=0;t<n;t++)
    {   int sum=0,x=0;
        for(int j=0;j<n;j++)//������һ����ÿ�������ܳ�Ϊ�������ӵ�ʦ�ĺ�������
        {
            if(j!=t&&a[t]>a[j])
            {
                sum++;
                for(int i=0;i<k;i++)
                { int f=0;
                  if(b[i][0]==t+1) {x=b[i][1];f=1;}
                  else if(b[i][1]==t+1) {x=b[i][0];f=1;}
                  if(j==x-1&&f==1) {sum--;}
                }
            }
        }
        cout<<sum<<' ';
    }
    cout<<endl;
    return 0;
}



