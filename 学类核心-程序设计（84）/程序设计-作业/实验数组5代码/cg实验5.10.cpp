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
    int b[n + 1][2];//声明第一维的长度为n+1的原因是需考虑当天的前一天晚上最后一班飞机的着陆时间
    for (int i = 0; i < n + 1; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            if (i == 0) { b[i][j] = fj[n - 1][j]; }
            else { b[i][j] = fj[i - 1][j]; }//向二维数组b存进每天最后一班飞机的着陆的时间
        }
 
    }
    int x = 0, y = 0, c = 0, total = 0, h = 0, m = 0;
    for (int i = 0; i < n + 1; i++)//综合比较
    {
        if (i < n)
        {
            x = b[i][0] * 60 + b[i][1];
            total = x + 1 + s;//+1为起飞需用时1分钟
            if (total >= 24 * 60) { total = total - 24 * 60; }
            y = b[i + 1][0] * 60 + b[i + 1][1];//对应航班着陆的时间
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
