#include<iostream>
#include<algorithm>
using namespace std;
struct road {
    int mi;
    int mx;         //����road�ṹ�壬��ʼ��վ���ĩվ�㣨һ������ά����ʹ��ʱ��Ҫ�����ϵ��
};
bool cmp(road r1, road r2) {
    return r1.mi < r2.mi;     //������֪��sortĬ�ϾͲ��ϵã��������ͣ�����Ҫ�ú����涨����
}
int main(){
    int n,y;
    cin >> n >> y;
    road* t = new road[n];
    for (int i = 0; i < n; i++) {
        cin >> t[i].mi >> t[i].mx;
    }
    sort(t, t + n, cmp);          //��·�ΰ��������С��������
    for (int i = 1; i < n; i++) {   //����һ��·����չ���������ܲ��ܰ�����0��Y����
        if (t[i].mi <= t[0].mx && t[i].mx > t[0].mx)t[0].mx = t[i].mx;
        if (t[i].mi < t[0].mi && t[i].mx >= t[0].mi)t[0].mi = t[i].mi;
    }
    if (t[0].mx >= y&&t[0].mi<=0)cout << "Yes";
    else cout << "No";
    delete[]t;
    return 0;
}
