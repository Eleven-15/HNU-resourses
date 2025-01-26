#include <stdio.h>
char ss[2][10]={"light","heavy"};
int main(){
	char s[5];
	int b3[4]={1,3,9,27},i,rs,f;
	while(scanf("%s",s)!=EOF){
		for(i=rs=0,f=1;i<4;++i)
		    if(s[i]!='='){
		    	if(s[i]=='>')rs-=b3[i];
		    	else rs+=b3[i];
		    	f*=-1;
			}
		rs*=f;
		f=rs>0?1:0;
		if(rs<0)rs=-rs;
		printf("%d %s\n",rs,ss[f]);
	}
	return 0;
}
