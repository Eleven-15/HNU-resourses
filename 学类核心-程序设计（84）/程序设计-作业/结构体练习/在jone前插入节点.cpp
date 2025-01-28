#include  <iostream>
using  namespace  std;
struct  Student{
        string  name;
        Student*  next;
};
void  addStudent(Student*  head,  Student*  s)  {
        Student *p=new Student;
		p=head;
		head=head->next;
		int flag=0;
		for(int i=0;i<5;i++){
 			if(head->name=="jone"){
 				p->next=s;
 				s->next=head;
 				flag++;
 			}
 			p=head;
 			head=head->next;
 		}
 		head=p;
		if(flag==0){
			head->next=s;
		}
}
int  main(){
        Student*  head  =  new  Student;
        head->next  =  nullptr;
        head->name  =  "";
        Student*  pre  =  head;
        for  (int  i  =  0;  i  <  5;  i++)  {
                Student*  s  =  new  Student;
                string  temp;
                cin  >>  temp;
                s->name  =  temp;
                s->next  =  nullptr;
                pre->next  =  s;
                pre  =  s;
        }
        string  name;
        cin  >>  name;
        Student*  s  =  new  Student;
        s->name  =  name;
        s->next  =  nullptr;
        addStudent(head,s);
        for(Student*  p  =  head->next;  p;  p  =  p->next)    {        //    Ñ­»·Êä³ö
                cout<<  p->name  <<  "  ";
        }
        return  0;
}
