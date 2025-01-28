#include <iostream>
#include"Dateminus.h"
using namespace std;

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
	Dateminus a,b;
	a.get();
	b.get();
	int c=a-b;
	cout<<c;
	return 0;
}
