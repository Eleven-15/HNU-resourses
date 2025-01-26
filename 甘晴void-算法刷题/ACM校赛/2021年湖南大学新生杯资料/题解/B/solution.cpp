#include<bits/stdc++.h>
using namespace std;

int main() {
  #ifdef Sakuyalove
    freopen("in.in", "r", stdin);
    freopen("out.out", "w", stdout);
  #endif
  int T;
  cin >> T;
  assert(1 <= T && T <= (int)1e4);
  while (T--) {
    long long a, b, c, d;
    cin >> a >> b >> c >> d;
    assert(1 <= a && a <= (int)(1e9));
    assert(1 <= b && b <= (int)(1e9));
    assert(1 <= c && c <= (int)(1e9));
    assert(1 <= d && d <= (int)(1e9));
    assert(a != b || c != d);
    assert(a * d != b * c || a * c != b * d);
    long long e = llabs(a * c - b * d), f = a * d + b * c;
    if (e == 0) {
	  e = llabs(a * d - b * c), f = a * c + b * d;
      assert(1 <= e && e <= (long long)4e18 && 1 <= f && f <= (long long)4e18);
      assert((__int128)(a * a + b * b) * (__int128)(c * c + d * d) == ((__int128)e * e + (__int128)f * f));
      cout << e << ' ' << f << endl;
    }
    else {
      assert(1 <= e && e <= (long long)4e18 && 1 <= f && f <= (long long)4e18);
      assert((__int128)(a * a + b * b) * (__int128)(c * c + d * d) == ((__int128)e * e + (__int128)f * f));
      cout << e << ' ' << f << endl;
    }
  }
  return 0;
}