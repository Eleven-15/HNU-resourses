#include<iostream>
using namespace std;

struct Jose{
	int code;
	Jose* next;
}; 

int main()
{
	Jose* head = new Jose;
	Jose* tmp = head;
	Jose* trans=NULL;
	tmp -> next = tmp;
	head -> code = 1;
	int n,m;
	cin >> n >> m;
	for(int i = 2; i <= n; i ++ )
	{
	    tmp->next = new Jose;
		tmp = tmp -> next;
		tmp->code = i;
		
	
	}
	tmp -> next = head;
	tmp = head;
    for ( int i=1 ; tmp -> next != tmp ; i++ , tmp = tmp -> next ) 
    {
    	if ( i == m-1 )
    	{
    		i = 0;
    		trans = tmp -> next;
    		tmp -> next = trans -> next;
    		delete (trans);
		}
	}
	cout<<tmp -> code;
}
