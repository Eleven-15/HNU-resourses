#include<iostream>
using namespace std;         //˼·��ͬ��ģ�⣬��Ҫ��
typedef unsigned long long int ui;
int main(){
    ui t;
    cin >> t;
    while (t--) {
        ui L, v, l, r;
        cin >> L >> v >> l >> r;
        ui sum = 0;
        for (ui pos = 1; pos <=L; pos++) {
            if (pos % v == 0 && (pos<l || pos>r)) sum++; 
        }
        cout << sum << endl;
    }
    return 0;
}
