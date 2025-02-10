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
/*
【问题描述】

       在一家重要的研究机构工作，小希参与了一项重要的试验：使用激光装置融化巧克力。

      该装置有包含 n×m 个单元的一个长方形区域以及一个机械臂组成，每个单元为一个 1×1  的小方块。机械臂上有两束激光垂直射向其表面，任何时候激光束都会射向两个单元的中心。由于两个激光束发射装置装在同一个机械臂上，故移动是同步的，也就是说，移动都在同一方向上。

      已知的事实为：

开始时整个区域被大小为 n×m 的巧克力块覆盖，两束激光均处于区域上方且已激活

只有被激光射向单元的巧克力将融化，其他单元内的不受影响

机械臂的任何移动必须平行于区域的边缘，每次移动后激光都会同时射向两个单元的中心

任何时候激光都只能射向本区域

       给出 n 和 m，表示区域的大小，行号从上往下从 1 到 n，列号从左到右为 1 到 m。

       给出两束激光最开始时的位置 (x1,  y1) 和 (x2,  y2），其中 x1、x2 为行号，y1、y2 为列号。

       请找出这个区域内有多少单元的巧克力不能被融化。

【输入形式】

       输入的第一行为一个正整数 t，表示测试数据的组数。

       接下来的 t 每行6个正整数 n、m、x1、y1、x2、y2 (2?≤?n,?m?≤?109, 1?≤?x1,?x2?≤?n, 1?≤?y1,?y2?≤?m)，分别表示区域的行数和列数，以及开始时激光束所在的位置。   

【输出形式】

       输出的t行，每行对应每组测试用例的结果
【样例输入】

2
4 4 1 1 3 3
4 3 1 1 2 2
【样例输出】

8
2
*/
