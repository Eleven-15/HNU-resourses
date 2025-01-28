#ifndef COMPLEX_H
#define COMPLEX_H

class complex
{
	public:
		complex()
		{
		};
		void show();
		complex operator+(complex &c);
		void get();
	protected:
		int x,y;
};

#endif
