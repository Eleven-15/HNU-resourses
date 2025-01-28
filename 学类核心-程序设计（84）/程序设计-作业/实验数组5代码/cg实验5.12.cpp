#include<iostream>
#include<algorithm>    //so easy
using namespace std;
int main(){
    int n;
    cin >> n;
    int* t = new int[n];
    for (int i = 0; i < n; i++)cin >> t[i];
    int k = count(t, t + n, 1);
    cout << k << endl;
    for (int j = 1; j < n; j++) {
        if (t[j] - t[j - 1] != 1) cout << t[j - 1]<<' ';
        if (j == n - 1)cout << t[j];
    }
    delete[]t;
    return 0;
}
