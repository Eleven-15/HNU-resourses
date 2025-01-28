#include<iostream>
using namespace std;

class mark
{
	public:
		int sum;
		string name;
		mark(){
		}
		~mark(){
		}
		void get()
		{ 
			cin>>name;
			cin>>score[0];
			min=score[0]; 
			max=score[0];
			sum=score[0];
			for (int i=1;i<=6;i++)
			{
				cin>>score[i];
				sum+=score[i];
				if (score[i]<min) min=score[i];
				if (score[i]>max) max=score[i];
			}
			sum-=(min+max);
		}
	private:
		int score[7];
		int min,max;
};

void swap(mark &a,mark &b)
{
	mark temp;
	temp.sum=a.sum; a.sum=b.sum; b.sum=temp.sum;
	temp.name=a.name; a.name=b.name; b.name=temp.name;
}
int main()
{
	int n;
	cin>>n;
	mark x[n];
    for (int i=0;i<=n-1;i++)
    {
    	x[i].get();
	}
	for (int i=0;i<=n-1;i++)
    {
    	for (int j=i;j<=n-1;j++)
    	{
    		if (x[i].sum<x[j].sum) swap(x[i],x[j]);
		}
	}
    for (int i=0;i<=n-1;i++)
    {
    	cout<<x[i].name<<" "<<x[i].sum<<endl;
	}

  return 0;
}

