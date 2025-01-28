#include <iostream>
#include <string>
#include <algorithm>
#include <map>
#include<cstdio>
#include<string.h>
using namespace std;
map <string, int>M;
int main() {
	string str1 = "qwertasdfgzxcvb";
	int flag = 1;
	int num, D = 1;
	cin >> num;
	string line;
	int time = 0;
	while (num--) {
		int T = 2;
		D = 1;
		cin >> line;
		if (M[line] != 0) D = 2;
		M[line] = 1;
		transform(line.begin(), line.end(), line.begin(), ::tolower);
		int type=str1.find(line[0]);
		flag = (type == -1) ? -1 : 1;
		for (int i = 1; i < line.size(); i++) {
			type = str1.find(line[i]);
			int temp = (type == -1) ? -1 : 1;
			if (flag == temp) {
				T += 4;
				continue;
			}
			else {
				flag = temp;
				T += 2;
			}
		}
		T /= D;
		time += T;
	}
	cout << time << endl;
	return 0;
}

