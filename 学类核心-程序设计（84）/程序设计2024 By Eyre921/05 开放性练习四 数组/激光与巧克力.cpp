#include <bits/stdc++.h>
using namespace std;
int n, m;
bool is_in(int x, int y)
{
	return x >= 1 && x <= n && y >= 1 && y <= m;
}

void solve()
{
	int x1, y1, x2, y2;
	cin >> n >> m >> x1 >> y1 >> x2 >> y2;
	vector<vector<bool>> is_melted(n + 1, vector<bool>(m + 1, false));
	int dx = abs(x1 - x2), dy = abs(y1 - y2);
	int count_melted = 0;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1 ; j <= m; j++)
		{
			int nx = i + dx, ny = j + dy;
			if (is_in(nx, ny))
			{
				if (!is_melted[i][j])
				{
					count_melted++;
					is_melted[i][j] = true;
				}
				if (!is_melted[nx][ny])
				{
					count_melted++;
					is_melted[nx][ny] = true;
				}
			}
		}
	}
	cout << n*m - count_melted << endl;
}



int main()
{
	int t ;
	cin >> t;
	while (t--)
	{
		solve();
	}

}
