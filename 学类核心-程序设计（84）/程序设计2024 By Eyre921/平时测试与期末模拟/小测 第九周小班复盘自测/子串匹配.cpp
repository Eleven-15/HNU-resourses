#include <iostream>
#include <string>
using namespace std;

int main() {
	string s, t;
	getline(cin, s);
	cin >> t;
	size_t found = s.find(t);
	if (found != s.npos) {
		cout << found;
	} else {
		cout << "-1";
	}
}
