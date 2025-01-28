#include <iostream>
#include <string>
using namespace std;
struct Race{
	string team;
	string name;
	int number;
	int times=0;
	int time;
};
int main()
{
	int n;
	string zhu,ke;
	cin>>zhu>>ke;
	cin>>n;
	Race people[n];
	int t,m;
	string p,wh; 
	for(int i=0;i<n;i++){
		cin>>t>>p>>m>>wh;
		if(p=="a"){
			people[i].team=ke;
			people[i].time=t;
			people[i].number=m;
			if(wh=="y"){
				people[i].times++;
			}
			else
				people[i].times=2;
		}
		else{
			people[i].team=zhu;
			people[i].time=t;
			people[i].number=m;
			if(wh=="y"){
				people[i].times++;
			}
			else
				people[i].times=2;
		}
	}
	int flag=0;
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			if(people[i].number==people[j].number&&people[i].team==people[j].team){
				if(i>j){
					people[i].times=2;
					flag++;
				}
			}
		}
	}
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			if(i!=j){
				if(people[i].times==2&&people[i].team==people[j].team&&people[i].time==people[j].time){
					if(i>j){
					if(people[i].number>people[j].number)
					{
						Race temp;
						temp=people[i];
						people[i]=people[j];
						people[j]=temp;
					}
				}
				}
			}
		}
	}
	for(int i=0;i<n;i++)
		if(people[i].times==2){
				cout<<people[i].team<<" "<<people[i].number<<" "<<people[i].time<<endl;
				flag++;
			}
	if(flag==0)
		cout<<"No Red Card";
	return 0;
}

