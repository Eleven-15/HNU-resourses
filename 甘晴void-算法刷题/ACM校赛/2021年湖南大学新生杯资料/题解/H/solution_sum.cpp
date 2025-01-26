#include<iostream>

using namespace std;

signed main(){
	int t;
	scanf("%d",&t);
	while(t--){
		int n;
		scanf("%d",&n);
		int x;
        long long ans=0;
		while(n--){
			scanf("%d",&x);
			ans+=x;
		}
		printf(ans&1?"Alice\n":"Bob\n");
	}
	return EOF+1;
}