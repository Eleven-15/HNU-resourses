#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
	int n;
	cin >> n;
	vector<int> vec(n, 0);
	for (int i = 0; i < n; i++)
		cin >> vec[i];
	sort(vec.begin(), vec.end(), greater<int>());
	for (size_t i = 0; i < vec.size(); ++i) {
		cout << vec[i];
		if (i != vec.size() - 1) { // 不是最后一个元素时输出空格
			cout << " ";
		}
	}
}
