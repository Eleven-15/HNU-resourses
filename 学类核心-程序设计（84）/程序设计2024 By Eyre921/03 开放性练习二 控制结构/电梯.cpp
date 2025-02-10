#include <iostream>
using namespace std;


int main() {
	int n, cha, time;
	cin >> n;
	int queue[n];
	for (int i = 0; i < n; i++) {
		cin >> queue[i];
	}
	time = n * 5;
	time += queue[0] * 6;
	for (int i = 1; i < n; i++) {
		cha = queue[i] - queue[i - 1];
		if (cha > 0)
			time += cha * 6;
		else
			time -= cha * 4;
	}
	cout << time;
}
