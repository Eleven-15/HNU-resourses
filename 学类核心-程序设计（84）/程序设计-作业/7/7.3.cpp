#include<iostream>
using namespace std;

int main()
{
    struct person
	{
		string name,sex;
		int id,age;
		person* next; 
	 } ;
	person* head=new person;
	person* tail=head;
	for (int i=1;i<=10;i++)
	{
		cin>>tail->name>>tail->id>>tail->sex>>tail->age;
		person* tmp=new person;
		tail->next=tmp;
		tail=tmp;
	}
	tail->next=NULL;
	
	cout<<"Before ordering(id|age|name|sex)"<<endl;
	tail=head;
	for (int i=1;i<=10;i++)
	{
		cout<<"("<<tail->id<<"|"<<tail->age<<"|"<<tail->name<<"|"<<tail->sex<<")"<<endl;
		tail=tail->next;
	}
	
	person* tmp=head;
	person* t=head;
	for (;tmp!=NULL;){
		tail=head;
		while (tmp->id>tail->id&&tail->next!=NULL){
			t=tail;
			tail=tail->next;
		}
		if (tmp->id<=tmp->id){
			if (tail==head){
				head=tmp;
				head->next=tail;
			}
			else{
				t->next=tmp;
				tmp->next=tail;
			}

		}
		else{
			tail->next=tmp;
			tmp->next=NULL;
		}
		tmp=tmp->next;

	}
	cout<<"After ordering(id|age|name|sex)"<<endl;
    for (int i=1;i<=10;i++)
	{
		cout<<"("<<tail->id<<"|"<<tail->age<<"|"<<tail->name<<"|"<<tail->sex<<")"<<endl;
		tail=tail->next;
	}

    return 0;
}

