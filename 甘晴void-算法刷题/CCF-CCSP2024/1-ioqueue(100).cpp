#include<iostream>
#include<queue>
#include<algorithm>
using namespace std;

int main()
{
	int n;
    priority_queue<int, vector<int>, greater<int>> q;
    cin>>n;
    for (int i=0;i<n;i++)
    {
        int temp;
        cin>>temp;
        q.push(temp);
    }
    int t1=0,t2=0;
    bool flag1,flag2;
    while(!q.empty())
    {
        // cout<<q.top();
        // q.pop();
        int now = q.top();
        q.pop();
        if (t2<t1)
        {
            if (now > t2) t2=now+10;
            else t2+=10;
        }
        else{
            if (now > t1) t1=now+10;
            else t1+=10;
        }
    }
    if (t1>t2) swap(t1,t2);
    cout<<t1<<" "<<t2<<endl;
    return 0;
}
