#include "complex.h"
#include<iostream>
using namespace std;

void complex::show()
{
	cout<<x<<" "<<y;
}
complex complex::operator+(complex &c)
{
    complex temp;
    temp.x=this->x+c.x;
    temp.y=this->y+c.y; 
    return temp;
}

void complex::get()
{
	cin>>x>>y;
}
