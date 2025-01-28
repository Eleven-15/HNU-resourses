#include<iostream>
using namespace std;
int main()
{
    int n;
    cin>>n;
    int a[n];
    for(int i=0;i<n;i++)
    {
        cin>>a[i];
    }
    int f=0;
    int b[48]={31,28,31,30,31,30,31,31,30,31,30,31,31,29,31,30,31,30,31,31,30,31,30,31,31,28,31,30,31,30,31,31,30,31,30,31,31,28,31,30,31,30,31,31,30,31,30,31};
    for(int i=0;i<48;i++)
    {
        if(a[0]==b[i])
        {
            int t=0;
            for(int j=i;j<i+n;j++)
            {
                if(a[t]!=b[j]) {f=0;break;}
                else f=1;
                t++;
            }
        }
        if(f==1) {break;}
    }
    if(f==1) cout<<"Yes"<<endl;
    else cout<<"No"<<endl;
    return 0;
}


