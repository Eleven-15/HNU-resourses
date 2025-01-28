#include <iostream>
using namespace std;
class Dir
{
	public:
	int x;
	int y;	
};
int main()
{
	Dir sta[2];
	cin>>sta[0].x>>sta[0].y>>sta[1].x>>sta[1].y;
	int n,num=0;
	cin>>n;
	Dir dd[n]; 
	for(int i=0;i<n;i++)
	{
		cin>>dd[i].x>>dd[i].y;
		if((dd[i].x>=sta[0].x&&dd[i].x<=sta[1].x)&&(dd[i].y<=sta[0].y&&dd[i].y>=sta[1].y))
			num++;
	}
	cout<<num;
	return 0;
}

