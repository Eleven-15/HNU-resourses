#include<iostream>
#include<cmath>             //数组枚举和数学问题罢了
using namespace std;
int main(){
    int n,d;
    cin >> n>>d;
    int* t = new int[n];
    for (int i = 0; i < n; i++)cin >> t[i];
    int res = 2;
    for (int i = t[0] + 1; i < t[n - 1]; i++) {
            int mi=10000001;
        for (int j = 0; j < n; j++) {
            int tmp = abs(t[j] - i);
            if (tmp < mi)mi = tmp;
        }
        if (mi == d)res++;
    }
    cout << res;
    delete[]t;
    return 0;
}
 
