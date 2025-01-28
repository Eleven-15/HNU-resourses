#include<iostream>
#include<string>
using namespace std;

int max(int a,int b)
{
	if (a>b) return a;
	else return b;
}

int main()
{
	 string str1,str2;
     getline(cin,str1);
     getline(cin,str2);
     bool flag=0;
     unsigned int p1=0,p2=0;
    
	 //cout<<str1.length()<<" "<<str2.length()<<endl;
     while (p1<=str1.length() && p2<=str2.length())
     {
     	if (str1[p1]==' ') p1++;
     	else if (str2[p2]==' ') p2++;
     	else 
     	{
     		if (str1[p1]>='A' && str1[p1]<='Z') str1[p1]=str1[p1]-'A'+'a';
     		if (str2[p2]>='A' && str2[p2]<='Z') str2[p2]=str2[p2]-'A'+'a';
     		if (str1[p1]!=str2[p2]) 
     		{
     			flag=1;
     			break; 
			 }
     	else 
     	{
     		p1++; p2++;
		 }
		 if (p1==str1.length() && p2==str2.length()) break;
		 }
     	//cout<<p1<<" "<<p2<<" "<<flag<<endl;
	 }
	 //p1--;p2--;
	 //cout<<p1<<" "<<p2;
	 if (p1!=str1.length() || p2!=str2.length()) flag=1;
     if (flag==1) cout<<0;
     else cout<<1;




  return 0;
}

