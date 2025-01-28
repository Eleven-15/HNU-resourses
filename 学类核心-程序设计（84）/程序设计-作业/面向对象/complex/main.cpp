#include <iostream>
#include"complex.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
	complex a,b;
	a.get();
	b.get();
	complex c=a+b;
	c.show();
	
	return 0;
}
