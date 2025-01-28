#include <iostream>
#include"RMB.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
	RMB a,b;
	a.get(); b.get();
	RMB c=a+b;
	c.show();
	RMB d=a-b;
	d.show();
	return 0;
}
