#include<bits/stdc++.h>
using namespace std;
int main()
{
	int k;
	cin>>k;
	int sum[k+1];
	for (int i=1;i<=k+1;i++)
	{
		sum[i]=0;
	}
	for (int i=1;i<=k;i++)
	{
		string s;
		double w,r,hg,hc,p;
		cin>>s>>w>>r>>hg>>hc>>p;
		if (w<4 || w>10) sum[i]++;
		if (r<3.5 || r>5.5) sum[i]++;
		if (s=="male" && (hg<120 || hg>160)) sum[i]++;
		else if (s=="female" && (hg<110 || hg>150)) sum[i]++;
		if (s=="male" && (hc<42 || hc>48)) sum[i]++;
		else if (s=="female" && (hc<36 || hc>40)) sum[i]++;
		if (p<100 || p>300) sum[i]++;
	}
    for (int i=1;i<=k;i++)
    {
    	if (sum[i]==0) cout<<"normal"<<endl;
    	else cout<<sum[i]<<endl;
	}

  return 0;
}

