#include<iostream>
using namespace std;
int main()
{
    int n, s;
    cin >> n >> s;
    int fj[n][2];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            cin >> fj[i][j];
        }
    }
    int b[n + 1][2];//������һά�ĳ���Ϊn+1��ԭ�����迼�ǵ����ǰһ���������һ��ɻ�����½ʱ��
    for (int i = 0; i < n + 1; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            if (i == 0) { b[i][j] = fj[n - 1][j]; }
            else { b[i][j] = fj[i - 1][j]; }//���ά����b���ÿ�����һ��ɻ�����½��ʱ��
        }
 
    }
    int x = 0, y = 0, c = 0, total = 0, h = 0, m = 0;
    for (int i = 0; i < n + 1; i++)//�ۺϱȽ�
    {
        if (i < n)
        {
            x = b[i][0] * 60 + b[i][1];
            total = x + 1 + s;//+1Ϊ�������ʱ1����
            if (total >= 24 * 60) { total = total - 24 * 60; }
            y = b[i + 1][0] * 60 + b[i + 1][1];//��Ӧ������½��ʱ��
            c = y - total;
            if (c >= (s + 1))
            {
                h = (total) / 60;
                m = total - h * 60;
                break;
            }
        }
        else if (i == n)
        {
            x = b[i][0] * 60 + b[i][1];
            total = x + 1 + s;
            if (total >= 24 * 60) { total = total - 24 * 60; }
            h = (total) / 60;
            m = total - h * 60;
        }
 
    }
    cout << h << ' ' << m << endl;
    return 0;
}
