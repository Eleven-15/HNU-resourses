#include <iostream>
using namespace std;
struct Frog{
	int dir;
	int len;
	int num;
	int mark; 
};
struct Mosq{
	int dir,weight;
	string wh;
};
int main()
{
	int n,m;
	cin>>n>>m;
	Frog indi[n],p1[n];
	for(int i=0;i<n;i++){
		cin>>indi[i].dir>>indi[i].len;
		indi[i].num=0;
		indi[i].mark=i;
		p1[i]=indi[i];
	}
	Mosq cang[m];
	for(int i=0;i<m;i++){
		cin>>cang[i].dir>>cang[i].weight;
		cang[i].wh="N";
	}
	for(int i=1;i<n;i++){
		for(int j=0;j<n-i;j++){
			if(indi[j].dir>indi[j+1].dir){
				Frog temp;
				temp=indi[j];
				indi[j]=indi[j+1];
				indi[j+1]=temp;
			}
		}
	} 
	int s=0;
	for(int i=0;s<m;i++){
		int flag=0;
		for(int j=0;j<n;j++){
			if(cang[i].dir-indi[j].dir>=0&&cang[i].dir-indi[j].dir<=indi[j].len){
				if(cang[i].wh=="N"){
					indi[j].len=indi[j].len+cang[i].weight;
					indi[j].num++;
					cang[i].wh="Y";
					s=-1;
					flag++;
					break;
				}
			}
		}
		s++;
		if(flag!=0){
			i=-1;
		}
	}
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			if(indi[i].mark==p1[j].mark){
				p1[j]=indi[i];
			}
		}
	}
	for(int i=0;i<n;i++){
		cout<<p1[i].num<<" "<<p1[i].len<<endl;
	}
	return 0;
}

