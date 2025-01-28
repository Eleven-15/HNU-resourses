#include<iostream>
using namespace std;

struct Jose {
      int code;
      Jose* next;
    };
    
int main()
{
    int n,m;
    cin>>n>>m;
    struct Jose *head=new Jose;
    struct Jose *temp;
    struct Jose *w;
    head->code=1;
    head->next=NULL;
    temp=head; 
    for (int i=2;i<=n;i++)
    {
	    	w=new Jose;
    	w->code=i;
    	w->next=temp;
    	temp=w;
	}
    head->next=temp;
//    temp=head;
    //构建环状链表 
//  temp->next=head;注意是错误的 
  /*      for (int i=1;i<=n;i++)
    {
    	cout<<temp->code<<" ";
    	temp=temp->next;
	}*/
    while (temp->next != temp)
    {
    	for (int i=1;i<m-1;i++)
    	{
    		cout<<temp->code<<" ";
    		temp=temp->next;
		}
		cout<<"delete"<<temp->next->code<<" ";
		temp->next=temp->next->next->next;
		cout<<endl;
	}
  return 0;
}

