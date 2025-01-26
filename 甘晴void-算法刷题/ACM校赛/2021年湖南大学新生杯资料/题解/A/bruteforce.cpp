#include<bits/stdc++.h>
using namespace std;
const int mod=1e9+7;
int main() {
	int n;
	cin>>n;
	assert(1<=n&&n<=1000000);
	int res=1;
	for(int i=0;i<n;i++) res=res*2%mod;
	cout<<res-1;
	return 0;
}