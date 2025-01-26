#include<iostream>
#include<vector>
#include<set>
#include<algorithm>
#include<cstring>
#include<map>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
	int n,m;
    cin>>n>>m;
    vector<int> v;
    for (int i=0;i<n;i++)
    {
        int temp;
        cin>>temp;
        v.push_back(temp);
    }
    if (n<=10000 && m<=10000)
    {
        while(m--)
        {
            int op,a,b;
            cin>>op>>a>>b;
            if (op==1)
            {
                int sum = 0;
                // set<int> s;
                // for (int i=a-1; i<=b-1; i++)
                // {
                //     int now = v[i];
                //     if (s.find(now) == s.end())
                //     {
                //         sum++;
                //         s.insert(now);
                //     }
                // }
                bool ntemp[20000];
                memset(ntemp,0,sizeof(ntemp));
                for (int i=a-1; i<=b-1; i++)
                {
                    int now = v[i];
                    if (ntemp[now] == 0)
                    {
                        sum++;
                        ntemp[now] = 1;
                    }
                }
                cout<<sum<<endl;
            }
            else if (op==2)
            {
                v[a-1] = b;
            }
            else
            {
                v.insert(v.begin()+a, b);
            }
        }
    }
    else{
        map<int,vector<int>> mp;
        bool ntemp[200000];
        memset(ntemp,0,sizeof(ntemp));
        for (int i=0; i<n; i++)
        {
            if (ntemp[v[i]] == 0)
            {
                ntemp[v[i]] = 1;
            }
            else{
                vector<int> temp;
                for (int j=0; j<mp[v[i]].size(); j++) {
                temp.push_back(mp[v[i]][j]);
                mp[v[i]].push_back(mp[v[i]][j]);}
                for (auto x : temp) mp[x].push_back(v[i]);
            }
        }
        while(m--)
        {
            int op,a,b;
            cin>>op>>a>>b;
            if (op==1)
            {
                int sum = 0;
                for (auto x : mp)
                {
                    int count = 0;
                    if (x.first>=a && x.first<=b)
                    {
                        for (auto y : x.second)
                        {
                            if (y>=a && y<=b) count++;
                        }
                    }
                    count /= 2;
                    count --;
                    sum+=count;
                }
                cout<<b-a+1-sum<<endl;
            }
            else if (op==2)
            {
                v[a-1] = b;
            }
            else
            {
                v.insert(v.begin()+a, b);
            }
        }
    }
    return 0;
}

// 6 5 1 1 2 3 4 1 1 1 6 2 1 5 1 1 3 3 1 1 1 1 3
