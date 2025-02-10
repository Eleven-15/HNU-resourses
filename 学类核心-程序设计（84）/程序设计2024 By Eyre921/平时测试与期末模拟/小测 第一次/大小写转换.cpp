#include <iostream>
#include <cctype>
using namespace std;

int main() {
	char letter;

	cin >> letter;

	if (islower(letter)) {
		char upperLetter = toupper(letter);
		cout << upperLetter << endl;
	} else if (isupper(letter)) {
		char lowerLetter = tolower(letter);
		cout << lowerLetter << endl;
	} else {
		return 1;
	}

	return 0;
}

