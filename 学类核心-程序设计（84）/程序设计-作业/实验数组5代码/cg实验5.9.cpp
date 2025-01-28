#include<iostream>
#include<algorithm>
using namespace std;
int main() {
	int n, k, M, D, i;
	cin >> n >> k >> M >> D;
	int a[M]; //储存每次循环阿迪所有的糖果
	for (i = 0; i < M; i++) {
		a[i] = 0;
	}
	int D1, n1;
	D1 = D;
	n1 = n;
	for (i = 1; i <= M; i++) { //一开始分配一个糖果
		D = D1;
		n = n1;
		for (int j = 0;; j++) { //糖果的分配 给安迪逐次分配糖果
			if (D <= 0) {
				break; //如果分配数超了，就break
			}
			n -= i * k;     //每分配一次，糖果就相应的减少
			a[i - 1] += i; // 给安迪分配糖果 然后存在数组中     
			if (n < i) { 
				break;//如果剩余糖果小于应分配数糖果，跳出循环
			}
			D--;
			if (n <= 0) { //没糖果就break
				break;
			}
		}
	}
	sort(a, a + M); //用sort升序排序，STL，暴力枚举可以用set容器（可自动排序，去重）
	cout << a[M - 1]; // 然后输出最大的
	return 0;
}
