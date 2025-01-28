#include<iostream>
using namespace std;
void GuessNumber(int magic){
	if(magic>35){
		cout<<"Wrong! Too high!"<<endl;
	}
	if(magic<35){
		cout<<"Wrong! Too low!"<<endl;
	}
	if(magic==35){
		cout<<"Right!"<<endl;
	}	
}
int main(){
	int n;
 for(int i=0;i<5;i++){
 	cin>>n;
 	GuessNumber(n);
 	if(n==35){
	 	break;
	 }
 }

return 0;
}

