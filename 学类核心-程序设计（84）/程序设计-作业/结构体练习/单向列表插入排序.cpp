#include <iostream>
#include <string>
#include <stdio.h>
using namespace std;
struct Student
{
	int id;
	int age;
	string sex;
	string name;
	Student *next;
};
Student *head;
Student* list(Student a[],int n)
{
	head = new Student;
	Student *tail = head;
	tail->next = NULL;
	for(int i = 0 ; i < n; i++){
		Student* PE=new Student;
		PE->age=a[i].age;
		PE->id=a[i].id;
		PE->name=a[i].name;
		PE->sex=a[i].sex;
		tail->next=PE;
		PE->next=NULL;
		tail=PE;
	}
	return head;	 
}
ostream &operator<<(ostream &s,Student &c)
{
	s<<"("<<c.id<<"|"<<c.age<<"|"<<c.name<<"|"<<c.sex<<")";
	return s;
}
int main()
{
	Student a[10];
	for(int i = 0;i<10;i++){
		cin>>a[i].name>>a[i].id>>a[i].sex>>a[i].age;
	}
	cout<<"Before ordering(id|age|name|sex)\n";
	Student*node=list(a,10);
	node=node->next;
	while(node!=NULL)
	{
		cout<<"("<<node->id<<"|"<<node->age<<"|"<<node->name<<"|"<<node->sex<<")\n";
		node=node->next;
	}
	cout<<"After ordering(id|age|name|sex)\n";
	for(int i=1;i<10;i++){
		for(int j=0;j<10-i;j++)
		{
			if(a[j].id>a[j+1].id){
				Student temp;
				temp=a[j];
				a[j]=a[j+1];
				a[j+1]=temp;
			}
		}
	}
	node=list(a,10);
	node=node->next;
	while(node!=NULL)
	{
		cout<<"("<<node->id<<"|"<<node->age<<"|"<<node->name<<"|"<<node->sex<<")\n";
		node=node->next;
	}
	return 0;
}

