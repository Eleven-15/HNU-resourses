#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// 1. 重塑矩阵函数
void reshape_matrix(ll& n, ll& m, ll p, ll q) {
    // 更新矩阵的行列数
    n = p;
    m = q;
}

// 2. 转置矩阵函数
void transpose_matrix(vector<ll>& j1, ll& n, ll& m) {
    vector<ll> j2(n * m);  // 新矩阵
    for (ll i = 0; i < n; i++) {  // 原矩阵的行数
        for (ll j = 0; j < m; j++) {  // 原矩阵的列数
            j2[j * n + i] = j1[i * m + j];  // 转置
        }
    }
    j1 = j2;  // 更新原矩阵
    swap(n, m);  // 转置后交换行列数
}

// 3. 查询矩阵元素的函数
void query_matrix(const vector<ll>& j1, ll m, ll b, ll c) {
    cout << j1[b * m + c] << endl;
}

int main() {
    ll n, m, t;
    cin >> n >> m >> t;  // n 行 m 列 t 次操作
    
    // 输入原始矩阵数据
    vector<ll> j1(n * m);  // 1D 数组存储矩阵
    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < m; j++) {
            cin >> j1[i * m + j];
        }
    }

    vector<tuple<ll, ll, ll>> ops;  // 存储所有操作

    // 输入操作列表
    for (ll i = 0; i < t; i++) {
        ll a, b, c;
        cin >> a >> b >> c;
        ops.push_back(make_tuple(a, b, c));
    }

    // 按照存储的操作列表依次执行操作
    for (const auto& op : ops) {
        ll a, b, c;
        tie(a, b, c) = op;

        if (a == 1) {
            // 重塑矩阵操作
            reshape_matrix(n, m, b, c);
        }
        else if (a == 2) {
            // 转置矩阵操作
            transpose_matrix(j1, n, m);
        }
        else if (a == 3) {
            // 查询矩阵元素操作
            query_matrix(j1, m, b, c);
        }
    }

    return 0;
}
