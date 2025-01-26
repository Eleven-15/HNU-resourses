#include<bits/stdc++.h>
using namespace std;
const int mod=1e9+7;
int qpow(long long a,int b) {
	long long res=1;
	while(b) {
		if(b&1) {
			res=res*a%mod;
		}
		a=a*a%mod;
		b>>=1;
	}
	return res;
}
int main() {
	int n;
	cin>>n;
	cout<<qpow(2,n)-1<<'\n';
	return 0;
}