#include  <iostream>
using  namespace  std;
struct  Person{
        char  name[20];
        unsigned  long  id;
        float  salary;  
};
void  bubbleSort(Person  personArr[]){
	for(int i=1;i<6;i++){
		for(int j=0;j<6-i;j++){
			if(personArr[j].salary>personArr[j+1].salary){
				Person temp;
				temp=personArr[j];
				personArr[j]=personArr[j+1];
				personArr[j+1]=temp;
			}
		}
	}
}
Person  allone[6]={
        {"jone",12345,339.0},
        {"david",13916,449.0},
        {"marit",27519,311.0},
        {"jasen",42876,623.0},
        {"peter",23987,400.0},
        {"yoke",12335,511.0}
        };

int  main(){
        bubbleSort(allone);
        for(int  k=0;  k<6;  k++)//Êä³ö
                cout<<allone[k].name<<"  "<<allone[k].id<<"  "<<allone[k].salary<<endl;
}
