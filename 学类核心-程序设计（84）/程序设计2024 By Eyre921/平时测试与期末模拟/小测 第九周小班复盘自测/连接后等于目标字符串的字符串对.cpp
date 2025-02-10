#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
	int n, counter = 0;
	cin >> n;
	string line, result;
	vector<string> v;
	for (int i = 0; i < n; ++i) {
		cin >> line;
		v.push_back(line);
	}

	// 对前n-1个元素进行遍历
	for (int i = 0; i < n - 1; ++i) {
		for (int j = 0; j < n - 1; ++j) {
			if (i != j) {
				result = v[i] + v[j];
				if (result == v[n - 1])
					counter++;
			}
		}
	}
	cout << counter << endl;
}

