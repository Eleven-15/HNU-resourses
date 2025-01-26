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
    long long x1, y1, x2, y2, A, B, C;
    cin >> x1 >> y1 >> x2 >> y2 >> A >> B >> C;
    assert((int)(-1e9) <= x1 && x1 <= (int)(1e9));
    assert((int)(-1e9) <= y1 && y1 <= (int)(1e9));
    assert((int)(-1e9) <= x2 && x2 <= (int)(1e9));
    assert((int)(-1e9) <= y2 && y2 <= (int)(1e9));
    assert((int)(-1e9) <= A && A <= (int)(1e9));
    assert((int)(-1e9) <= B && B <= (int)(1e9));
    assert((int)(-1e9) <= C && C <= (int)(1e9));
    assert(A * x1 + B * y1 + C != 0);
    assert(A * x2 + B * y2 + C != 0);
    assert(A * A + B * B != 0);
    assert(x1 != x2 || y1 != y2);
    cout << (((A * x1 + B * y1 + C) > 0) == ((A * x2 + B * y2 + C) > 0) ? "Yes" : "No") << endl;
  }
  return 0;
}