//������ģ�ⷽ��
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
        ui* w = new ui[k];                      //water w[]����ͷ
        for (ui i = 0; i < k; i++)cin >> w[i];
        bool* hua = new bool[n + 1]();           //bool hua ģ�����޽�ˮ
        ui j = 1;
        while (1) {
            for (ui i = 0; i < k; i++) {
                ui mi = max(w[i] - (j - 1), 1);   //include<cmath>
                ui mx = min(w[i] + (j - 1), n);   //��ʾ�ܽ���ˮ�Ļ�����Χ
                for (ui L = mi; L <= mx; L++) {   //ģ�⻨����ˮ֮���״̬
                    hua[L] = 1;
                }
            }
            if (count(hua, hua + n + 1, 1) == n) { cout << j << endl; break; }
            j++;       //STL,����ûѧ��ͬѧֱ���þͶ��ˣ�ͬsort���
        }              //count(���ҵ��׵�ַ�����ҵ�β��ַ�������ҵ�Ԫ�أ�������������Ԫ�صĸ���
        delete[]hua;
        delete[]w;
    }
    return 0;
}
