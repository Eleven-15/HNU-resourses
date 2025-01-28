#include<bits/stdc++.h>
using namespace std;
int main()
{
    double n;
    cin>>n;
    if (n/3.0+50<n/1.2) cout<<"Bike";
    if (n/3.0+50==n/1.2) cout<<"All";
    if (n/3.0+50>n/1.2) cout<<"Walk";



  return 0;
}

