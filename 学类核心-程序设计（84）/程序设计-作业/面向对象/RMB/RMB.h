#ifndef RMB_H
#define RMB_H
using namespace std;

class RMB
{
	public:
		void show();
		void get();
		RMB operator+(RMB &c);
		RMB operator-(RMB &c);
		int abs(int a);
	protected:
		int x,y,z;
};

#endif
