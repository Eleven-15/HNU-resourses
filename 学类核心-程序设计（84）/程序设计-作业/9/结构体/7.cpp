#include <deque> 
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <vector>
#include <bits/stdc++.h> 
using namespace std;

typedef struct T{
	int _time;
	int id;
}; 
bool cmp(T a,T b){
	if(a._time==b._time)
		return a.id<b.id;
	return a._time<b._time;
} 
set<int> Set;
vector<T> ta;
vector<T> re;
int main(){
	int n,k;
	cin>>n>>k;
	while(k--){
		int w,s,c;
		cin>>w>>s>>c;  
		int h=s+c;
		Set.insert(s);
		Set.insert(h);
		T t1;
		t1._time=s;t1.id=w;
		T r;
		r._time=h;r.id=w;
		ta.push_back(t1);
		re.push_back(r);
	}
	sort(ta.begin(),ta.end(),cmp);
	sort(re.begin(),re.end(),cmp);
	int arr[n];
	for(int i=1;i<=n;i++){
		arr[i]=i; 
	} 
	for(set<int>::iterator it=Set.begin();it!=Set.end();it++){
		for(vector<T>::iterator it1=re.begin();it1!=re.end();it1++) {
			if(it1->_time==*it){
				for(int i=1;i<=n;i++){
					if(arr[i]==0){
						arr[i]=it1->id;
						break;
					}
					
				}
			}
			else if(it1->_time>*it) break;
		}
		for(vector<T>::iterator it1=ta.begin();it1!=ta.end();it1++) {
			if(it1->_time==*it){
				for(int i=1;i<=n;i++){
					if(arr[i]==it1->id){
						arr[i]=0;
						break;
					}	
				}
			}
			else if(it1->_time>*it) break;
		}
	}
	for(int i=1;i<=n;i++)
	cout<<arr[i]<<" ";
	return 0;
}

