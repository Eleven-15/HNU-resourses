#include <iostream>
using namespace std;
string who_win(int a, int b);

int main() {
	int t, a, b;
	cin >> t;
	for (int i = 0; i < t; i++) {
		cin >> a >> b;
		cout << who_win(a, b) << endl;
	}

}

string who_win(int a, int b) {
	int i = 1;
	bool turn = true;
	while (a >= 0 && b >= 0) {
		if (turn)
			a -= i;
		else
			b -= i;
		i++;
		turn = !turn;
	}
	if (a < 0)
		return "Bob";
	if (b < 0)
		return "Limak";
	return "";
}
