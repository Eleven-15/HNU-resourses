//暴力的模拟方法
#include<iostream>
#include<cmath>
#include<algorithm>
using namespace std;
typedef  int ui;
int main() {
    ui T;
    cin >> T;
    while (T--) {
        ui n, k;
        cin >> n >> k;
        ui* w = new ui[k];                      //water w[]代表浇头
        for (ui i = 0; i < k; i++)cin >> w[i];
        bool* hua = new bool[n + 1]();           //bool hua 模拟有无浇水
        ui j = 1;
        while (1) {
            for (ui i = 0; i < k; i++) {
                ui mi = max(w[i] - (j - 1), 1);   //include<cmath>
                ui mx = min(w[i] + (j - 1), n);   //表示能浇到水的花花范围
                for (ui L = mi; L <= mx; L++) {   //模拟花浇到水之后的状态
                    hua[L] = 1;
                }
            }
            if (count(hua, hua + n + 1, 1) == n) { cout << j << endl; break; }
            j++;       //STL,（还没学的同学直接用就对了，同sort类比
        }              //count(查找的首地址，查找的尾地址，所查找的元素），返回所查找元素的个数
        delete[]hua;
        delete[]w;
    }
    return 0;
}
