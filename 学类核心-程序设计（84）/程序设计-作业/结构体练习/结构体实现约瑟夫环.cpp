#include <iostream>
using namespace std;
struct Jose
{
	int code;
	Jose *next;
};
int main()
{
	int n,m;
	cin>>n>>m;
	Jose *head,*tail;
	head=new Jose;
	head->code=1;
	head->next=NULL;
	tail=head;
	for(int i=2;i<=n;i++){
		Jose *p=new Jose;
		p->code=i;
		tail->next=p;
		tail=p;
		if(i==n)
			p->next=head;	
	}
	Jose *Sta;
	Sta=head;
	tail=Sta->next;
	int q=1;
	while(Sta->next!=Sta)
	{
		tail=tail->next;
		q++;
		if(q==m)
		{
			Sta->next=tail;
			q=0;
		}
		else
			Sta=Sta->next;
	}
	cout<<Sta->code;
	
	return 0;
}

