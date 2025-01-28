#include <iostream>
using namespace std;
class Quality
{
	public:
	char name[100];
	int ti;
	int zhi;
	int wu;	
} ;
int main()
{
	Quality person[23];
	int i=0;
	cin>>person[i].name;
	while(person[i].name[0]!='#')
	{
		cin>>person[i].ti>>person[i].wu>>person[i].zhi;
		i++;
		cin>>person[i].name;
	}
	int p;
	cin>>p;
	if(p==1)
	{
		for(int j=1;j<i;j++){
			for(int m=0;m<i-j;m++){
				Quality temp;
				if(person[m].ti<person[m+1].ti)
				{
					temp=person[m];
					person[m]=person[m+1];
					person[m+1]=temp;
				}
			}
		}
	}
	else if(p==2){
		for(int j=1;j<i;j++){
			for(int m=0;m<i-j;m++){
				Quality temp;
				if(person[m].wu<person[m+1].wu)
				{
					temp=person[m];
					person[m]=person[m+1];
					person[m+1]=temp;
				}
			}
		}
	}
	else{
		for(int j=1;j<i;j++){
			for(int m=0;m<i-j;m++){
				Quality temp;
				if(person[m].zhi<person[m+1].zhi)
				{
					temp=person[m];
					person[m]=person[m+1];
					person[m+1]=temp;
				}
			}
		}
	}
	for(int l=0;l<i;l++){
		cout<<person[l].name<<" "<<person[l].ti<<" "<<person[l].wu<<" "<<person[l].zhi<<endl;
	}
	return 0;
}

