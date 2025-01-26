#include<bits/stdc++.h>
using namespace std;

const int M = 1e7;
const int mod = 998244353;

int qpow(int a, int p) {
  int ret = 1;
  while (p) {
    if (p & 1) ret = 1ll * a * ret % mod;
    a = 1ll * a * a % mod;
    p >>= 1;
  }
  return ret;
}

bool np[M + 5];
int p[M + 5], num, s[M + 5];
int k, q;

signed main() {
  #ifdef Sakuyalove
    freopen("in.in", "r", stdin);
    freopen("out.out", "w", stdout);
  #endif
  cin >> k >> q;
  s[1] = 1;
  for (int i = 2; i <= M; i++) {
    if (!np[i]) {
      p[++num] = i;
      s[i] = qpow(i, k);
    }
    for (int j = 1; j <= num; j++) {
      if (1ll * p[j] * i > M) break;
      np[p[j] * i] = 1;
      s[p[j] * i] = 1ll * s[p[j]] * s[i] % mod;
      if (i % p[j] == 0) break;
    }
  }
  for (int i = 1; i <= M; i++) s[i] = (s[i - 1] + s[i]) % mod;
  while (q--) {
    int l, r;
    cin >> l >> r;
    cout << (s[r] - s[l - 1] + mod) % mod << endl;
  }
  return 0;
}
