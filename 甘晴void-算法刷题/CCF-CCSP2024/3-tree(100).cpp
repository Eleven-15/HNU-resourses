#include<iostream>
#include<vector>
#include<set>
#include<algorithm>
using namespace std;

struct node
{
    int data;
    int parent;
    vector<int> child;
};

int findnum(vector<node> &list, int u, int v)
{
    int ret = 0;
    if (list[u].child.empty())
    {
        if (list[u].data > v) ret = 1;
        return ret;
    }
    else{
        for(int i=0; i<list[u].child.size(); i++)
        {
            ret += findnum(list,list[u].child[i],v);
        }
        if (list[u].data > v) ret += 1;
        return ret;
    }
}

int findmax(vector<node> &list, int u)
{
    int maxnum = 0;
    if (list[u].child.empty())
    {
        maxnum = max(list[u].data, maxnum); 
        return maxnum;
    }
    else{
        for(int i=0; i<list[u].child.size(); i++)
        {
            maxnum = max(maxnum, findmax(list,list[u].child[i]));
        }
        return max(maxnum, list[u].data);
    }
}

void findmin(vector<node> &list, int u, int& minvalue, int& minnum)
{
    if (!list[u].child.empty())
    {
        for(int i=0; i<list[u].child.size(); i++)
        {
            findmin(list, list[u].child[i], minvalue, minnum);
        }
    }
    if (list[u].data < minvalue)
    {
        minnum = u;
        minvalue = list[u].data;
    }
    else if (list[u].data == minvalue && u<minnum)
    {
        minnum = u;
        minvalue = list[u].data;
    }
    return;
}

void rotate(vector<node> &list, int u)
{
    if (list[u].parent == -1) return;
    rotate(list, list[u].parent);
    int parentnum = list[u].parent;
    auto childpos = find(list[parentnum].child.begin(), list[parentnum].child.end(), u);
    list[parentnum].child.erase(childpos);
    list[parentnum].parent = u;
    list[u].parent = -1;
    list[u].child.push_back(parentnum);
    return;
}

int main()
{
	int n,m;
    cin>>n;
    vector<node> list;
    for (int i=0;i<n; i++)
    {
        node newnode;
        newnode.parent = -1;
        list.push_back(newnode);
    }
    for (int i=0;i<n-1;i++)
    {
        int u,v;
        cin>>u>>v;
        u--;
        v--;
        list[u].child.push_back(v);
        list[v].parent = u;
    }
    for (int i=0; i<n; i++)
    {
        int temp;
        cin>>temp;
        list[i].data = temp;
    }

    cin>>m;
    int last = 0;
    while(m--)
    {
        int DEBUG =0;
        if (DEBUG)
        {
            cout<<endl;
            for (int i=0; i<list.size(); i++)
            {
                cout<<"index = "<<i<<" value = "<<list[i].data<<" | ";
                for (int j=0; j<list[i].child.size(); j++) cout<<list[i].child[j]<<" ";
                cout<<endl;
            }
        }
        int op;
        cin>>op;
        if (op == 1)
        {
            int u,v;
            cin>>u>>v;
            u ^= last;
            v ^= last;
            u--;
            last = findnum(list,u,v);
            cout<<last<<endl;
        }
        else if (op == 2)
        {
            int u,v;
            cin>>u>>v;
            u ^= last;
            v ^= last;
            u--;
            list[u].data = v;
        }
        else if (op == 3)
        {
            int u,v;
            cin>>u>>v;
            u ^= last;
            v ^= last;
            u--;
            int now = list.size();
            node newnode;
            list.push_back(newnode);
            list[now].data = v;
            list[u].child.push_back(now);
            list[now].parent = u;
        }
        else if (op == 4)
        {
            int u,v;
            cin>>u;
            u ^= last;
            u--;
            int parent = list[u].parent;
            list[parent].child.erase(find(list[parent].child.begin(),list[parent].child.end(),u));
            list[u].parent = -1;
            last = findmax(list,u);
            cout<<last<<endl;
        }
        else if (op == 5)
        {
            int u,v;
            cin>>u;
            u ^= last;
            u--;
            int minvalue = 9999999;
            int minnum = 99999;
            findmin(list, u, minvalue, minnum);
            last = minnum + 1;
            cout<<last<<endl;
        }
        else if (op == 6)
        {
            int u,v;
            cin>>u;
            u ^= last;
            u--;
            rotate(list,u);
        }

    }
    
    return 0;
}