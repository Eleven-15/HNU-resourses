#include<bits/stdc++.h>
#include<cstring>
#include<string>
using namespace std;

// CREATE_Proc pid load
// DESTROY_Thread tid
// CREATE_Thread pid tid load
// SCHEDULE_OPT

map<int,int> tidref;

struct pnode
{
    int pid;
    int load;
    map<int,int> threadlist;
};

map<int,pnode> plist;

int main()
{
    int n;
    cin>>n;

    getchar();
    while (n--)
    {
        string str;
        getline(cin,str);
        stringstream ss;
        ss << str;
        string op;
        vector<string> envlist;
        ss >> op;
        string temp;
        while(ss >> temp)
        {
            envlist.push_back(temp);
        }
        
        if (op == "CREATE_Proc")
        {
            // CREATE_Proc pid load
            int pid = stoi(envlist[0]);
            int load = stoi(envlist[1]);

            if (plist.find(pid) != plist.end()) continue;
            pnode newnode;
            newnode.pid = pid;
            newnode.load = load;
            newnode.threadlist.insert(make_pair(pid,load));
            tidref.insert(make_pair(pid,pid));
            plist.insert(make_pair(pid,newnode));
        }
        else if (op == "CREATE_Thread")
        {
            // CREATE_Thread pid tid load
            int pid = stoi(envlist[0]);
            int tid = stoi(envlist[1]);
            int load = stoi(envlist[2]);
            
            if (plist.find(tid) != plist.end()) continue;
            auto pos = plist.find(pid);
            if (pos != plist.end())
            {
                pos->second.threadlist.insert(make_pair(tid,load));
                tidref.insert(make_pair(tid,pid));
            }
        }
        else if (op == "DESTROY_Thread")
        {
            // DESTROY_Thread tid
            int tid = stoi(envlist[0]);

            if (tidref.find(tid) == tidref.end()) continue;
            int pid = tidref[tid]; 
            plist[pid].threadlist.erase(tid);
            tidref.erase(tid);
            if (plist[pid].threadlist.empty())
            {
                plist.erase(pid);
            }
        }
        else if (op == "SCHEDULE_OPT")
        {
            // SCHEDULE_OPT
            for (auto x : plist)
            {
                for (auto y : x.second.threadlist)
                {
                    cout<<"Process (PID): "<<x.first<<" Thread(Tid): "<<y.first<<" Load: "<<y.second<<endl;
                }
            }
            cout<<"Contention Cost: 0"<<endl;
        }
    }
    return 0;
}