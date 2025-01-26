#include<iostream>

using namespace std;

signed main(){
	int t;
	scanf("%d",&t);
	while(t--){
		int n;
		scanf("%d",&n);
		int x,ans=0;
		while(n--){
			scanf("%d",&x);
			if(x&1) {
				ans++;
			}
		}
		printf(ans&1?"Alice\n":"Bob\n");
	}
	return EOF+1;
}