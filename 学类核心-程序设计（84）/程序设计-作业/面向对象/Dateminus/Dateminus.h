#ifndef DATEMINUS_H
#define DATEMINUS_H

class Dateminus
{
	public:
		void get();
		int operator-(Dateminus &c);
	protected:
		int x,y,z;
		
};

#endif
