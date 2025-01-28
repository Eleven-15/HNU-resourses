#include<iostream>
#include<algorithm>
using namespace std;
struct road {
    int mi;
    int mx;         //定义road结构体，表开始的站点和末站点（一样，二维数组使用时，要理清关系）
};
bool cmp(road r1, road r2) {
    return r1.mi < r2.mi;     //众所周知，sort默认就不认得，复合类型，所以要用函数规定规则
}
int main(){
    int n,y;
    cin >> n >> y;
    road* t = new road[n];
    for (int i = 0; i < n; i++) {
        cin >> t[i].mi >> t[i].mx;
    }
    sort(t, t + n, cmp);          //将路段按出发点从小到大排序
    for (int i = 1; i < n; i++) {   //将第一个路段拓展，看最终能不能包括【0，Y】段
        if (t[i].mi <= t[0].mx && t[i].mx > t[0].mx)t[0].mx = t[i].mx;
        if (t[i].mi < t[0].mi && t[i].mx >= t[0].mi)t[0].mi = t[i].mi;
    }
    if (t[0].mx >= y&&t[0].mi<=0)cout << "Yes";
    else cout << "No";
    delete[]t;
    return 0;
}
