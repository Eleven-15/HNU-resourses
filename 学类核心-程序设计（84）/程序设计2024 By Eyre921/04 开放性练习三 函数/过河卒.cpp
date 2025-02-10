#include <iostream>
#include <vector>
using namespace std;

int dx[8]={-2,-2,-1,-1,1,1,2,2};
int dy[8]={1,-1,2,-2,2,-2,1,-1};

/*
如图，A 点有一个过河卒，需要走到目标 B 点。卒行走规则：
可以向下、或者向右。同时在棋盘上的任一点有一个对方的马（图中的C点），
该马所在的点和所有跳跃一步可达的点称为对方马的控制点（中国象棋规定马走“日”字）。
例如图中 C 点上的马可以控制 9 个点（图中的P1，P2 … P8 和 C）。卒不能通过对方马的控制点。
棋盘用坐标表示，A 点（0，0）、B 点（n,m）(n,m 为不超过 20 的整数，并由键盘输入)，
同样马的位置坐标是需要给出的（约定: C不等于A，同时C不等于B）。现在要求你计算出卒从 A 点能够到达 B 点的路径的条数。
 */
bool inBounds(int n, int m, int x, int y)
{
	return x >= 0 && y >= 0 && x <= n && y <= m;
}

void is_controled(vector<vector<bool>> &Bound, int cx, int cy, int n, int m)
{
	Bound[cx][cy] = true;
	for(int i = 0; i < 8; i++)
	{
		int tx = cx + dx[i];
		int ty = cy + dy[i];
		if(inBounds(n,m,tx,ty))
			Bound[tx][ty] = true;
	}
}

int main() {
	int n, m;
	cin >> n >> m;
	int cx, cy;
	cin >> cx >> cy;  // 马的位置
	// 初始化棋盘，未被占领记为false
	vector<vector<bool>> Bound(n + 1, vector<bool>(m + 1, false));

	// 找到马控制的位置,并标记为true
	is_controled(Bound,cx,cy,n,m);

	// 使用动态规划遍历所有位置
	// 初始化每个格子的路径数
	vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
	dp[0][0] = 1;
	for(int x = 0; x <= n; x++)
	{
		for(int y = 0; y <= m; y++)
		{
			// 如果被马控制，路径为0
			if(Bound[x][y]) dp[x][y] = 0;
			else
			{
				if (x > 0) dp[x][y] += dp[x - 1][y]; // 如果x是正数，则加上上面一个格子的路径
				if (y > 0) dp[x][y] += dp[x][y - 1];// 如果y是正数，则加上左面一个格子的路径
			}
		}
	}

	// 返回最后一个格子的路径数
	cout << dp[n][m] << endl;
	return 0;
}
