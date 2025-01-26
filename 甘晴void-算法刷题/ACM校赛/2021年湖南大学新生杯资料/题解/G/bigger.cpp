#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define all(x) x.begin(),x.end()
int to(char ch){
    if(ch <= '9' && ch >= '0') return ch-'0';
    else if(ch <= 'F' && ch >= 'A') return ch-'A'+10;
    else assert(0); return 0;
}
bool f(string x, string y){
    reverse(all(x)); reverse(all(y));
    vector<int> a(x.size()), b(y.size());
    for(int i = 0; i < x.size(); ++i) a[i] = to(x[i]), a[i] *= 2;
    for(int i = 0; i < y.size(); ++i) b[i] = to(y[i]), b[i] *= 3;
    a[0] += 10; b[0] += 5;
    for(int i = 0; i < a.size(); ++i){
        int z = a[i]/16; a[i] %= 16;
        if(z){
            if(i+1 == a.size()) a.pb(0);
            a[i+1] += z;
        }
    }
    for(int i = 0; i < b.size(); ++i){
        int z = b[i]/16; b[i] %= 16;
        if(z){
            if(i+1 == b.size()) b.pb(0);
            b[i+1] += z;
        }
    }
    if(a.size() > b.size()) return true;
    else if(a.size() < b.size()) return false;
    else{
        for(int i = (int)a.size()-1; i >= 0; --i) if(a[i] != b[i]) return a[i] > b[i];
        return false;
    }
}
void sol(){
    int T; cin>>T;
    while(T--){
        string x, y;
        cin>>x>>y;
        if(f(x, y)) cout<<"Yes"<<'\n';
        else cout<<"No"<<'\n';
    }
    return;
}
int main(){
    sol();
    // int T = 20;
    // char inp[50], otp[50];
    // for(int i = 1; i <= 20; ++i){
    //     sprintf(inp, "%d.in", i);
    //     sprintf(otp, "%d.out", i);
    //     freopen(inp, "r", stdin);
    //     freopen(otp, "w", stdout);
    //     sol();
    // }
    return 0;
}