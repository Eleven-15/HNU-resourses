#include <iostream>
using namespace std;

int result(int n, int x)
{
  if (n == 0)
    return 0;
  if (n == 1)
    return x;
  return (result(n - 1, x) + result(n - 2, x) + x);
}
int main()
{
  int x;
  x = 4;
  cout << result(9, x) << endl;
  return 0;
}
