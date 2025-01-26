#include<bits/stdc++.h>
#define my_leecher pos->second.leecher
#define my_seeder pos->second.seeder
using namespace std;
const int DEBUG = 0;

struct usernode
{
    string peer_id;
    string ip;
    string port;
    int uploaded;
    int downloaded;
    usernode(string peer_id, string ip, string port, int uploaded, int downloaded)
    {
        this->peer_id = peer_id;
        this->ip = ip;
        this->port = port;
        this->uploaded = uploaded;
        this->downloaded = downloaded;
    }
};

struct seednode
{
    string info_hash;
    string status;
    map<string,usernode> seeder;
    map<string,usernode> leecher;
    int complete;
    int incomplete;
};

map<string,seednode> seedlist;


bool cmp_seeder(usernode& a, usernode& b)
{
    if (a.uploaded > b.uploaded) return true;
    else if (a.uploaded < b.uploaded) return false;
    else{
        return a.peer_id < b.peer_id;
    }
}

bool cmp_leecher(usernode& a, usernode& b)
{
    if (a.downloaded > b.downloaded) return true;
    else if (a.downloaded < b.downloaded) return false;
    else{
        return a.peer_id < b.peer_id;
    }
}

string add(map<string,seednode>& seedlist, vector<string>& envlist)
{
    string info_hash = envlist[0].substr(10,20);
    if (seedlist.find(info_hash) == seedlist.end())
    {
        seednode newseed;
        newseed.info_hash = info_hash;
        seedlist.insert({info_hash,newseed});
        return "OK";
    }
    else{
        return "ERROR: Torrent already exists";
    }
}

string del(map<string,seednode>& seedlist, vector<string>& envlist)
{
    string info_hash = envlist[0].substr(10,20);
    map<string,seednode>::iterator now = seedlist.find(info_hash);
    if (now != seedlist.end())
    {
        // TODO
        // if () in use
        if (now->second.status == "FROZEN") return "FROZEN";
        else{
            seedlist.erase(now);
            return "OK";
        }
    }
    else{
        return "ERROR: Invalid info_hash";
    }
    
}

void annoounce(vector<string>& envlist)
{
    // announce 
    // INFO_HASH=INFO-000000000000002 
    // PEER_ID=PEER-00000000000000D 
    // IP=192.168.3.4 
    // PORT=5204 
    // UPLOADED=1200 
    // DOWNLOADED=300 
    // NUMWANT=3 
    // EVENT=completed
    string info_hash = envlist[0].substr(10,20);
    string peer_id = envlist[1].substr(8,20);
    string ip = envlist[2].substr(3);
    string port = envlist[3].substr(5);
    int uploaded = stoi(envlist[4].substr(9));
    int downloaded = stoi(envlist[5].substr(11));
    string temp = envlist[6].substr(8);
    int numwant;
    if (temp=="") numwant = 50;
    else numwant = stoi(envlist[6].substr(8));
    string event = envlist[7].substr(6);

    //if (DEBUG) cout<<"DEBUG*****"<<endl<<info_hash<<endl<<peer_id<<endl<<ip<<endl<<port<<endl<<uploaded<<endl<<downloaded<<endl<<numwant<<endl<<event<<endl<<"*****DEBUG"<<endl;

    auto pos = seedlist.find(info_hash);
    if (pos != seedlist.end())
    {
        //auto my_seeder = pos->second.seeder;
        auto seeder_pos = my_seeder.find(peer_id);
        //auto my_leecher = pos->second.leecher;
        auto leecher_pos = my_leecher.find(peer_id);
        string user_status = "";
        usernode newnode(peer_id, ip, port, uploaded, downloaded);
        if (DEBUG) cout<<"AAAAA"<<endl;
        if (DEBUG) cout<<"now info_hash:"<<info_hash<<endl;
        if (DEBUG) {cout<<"leecher:"; for (auto x : my_leecher) cout<<x.first<<" "; cout<<endl;}
        if (DEBUG) {cout<<"seed:"; for (auto x : my_seeder) cout<<x.first<<" "; cout<<endl;}

        if (event == "started")
        {
            if (seeder_pos != my_seeder.end()) my_seeder.erase(seeder_pos);
            if (leecher_pos == my_leecher.end()) my_leecher.insert({peer_id,newnode});
            else 
            {
                leecher_pos->second.downloaded = downloaded;
                leecher_pos->second.uploaded = uploaded;
            }
            user_status = "leecher";
        }
        else if (event == "completed")
        {
            if (leecher_pos != my_leecher.end()) my_leecher.erase(leecher_pos);
            if (seeder_pos == my_seeder.end()) my_seeder.insert({peer_id,newnode});
            else 
            {
                seeder_pos->second.downloaded = downloaded;
                seeder_pos->second.uploaded = uploaded;
            }
            user_status = "seeder";
        }
        else if (event == "stopped")
        {
            if (seeder_pos != my_seeder.end()) my_seeder.erase(seeder_pos);
            if (leecher_pos != my_leecher.end()) my_leecher.erase(leecher_pos);
        }
        else if (event == "empty")
        {

        }

        int complete = my_seeder.size();
        int incomplete = my_leecher.size();
        if (DEBUG) cout<<"now info_hash:"<<info_hash<<endl;
        if (DEBUG) cout<<"complete:"<<complete<<endl<<"incomplete:"<<incomplete<<endl;
        if (DEBUG) {cout<<"leecher:"; for (auto x : my_leecher) cout<<x.first<<" "; cout<<endl;}
        if (DEBUG) {cout<<"seed:"; for (auto x : my_seeder) cout<<x.first<<" "; cout<<endl;}
        
        vector<usernode> peers;
        if (user_status == "seeder")
        {
            numwant = min(numwant, incomplete);
            vector<usernode> seedervec,leechervec;
            for (auto x : my_leecher) leechervec.push_back(x.second);
            sort(leechervec.begin(),leechervec.end(),cmp_leecher);
            for(int i=0; i<numwant; i++) peers.push_back(leechervec[i]);
        }
        else if (user_status == "leecher")
        {
            vector<usernode> seedervec,leechervec;
            for (auto x : my_seeder) seedervec.push_back(x.second);
            sort(seedervec.begin(),seedervec.end(),cmp_seeder);
            int count = 0;
            for(int i=0; i<seedervec.size(); i++)
            {
                peers.push_back(seedervec[i]);
                count++;
                if (count == numwant) break;
            }
            if (count < numwant)
            {
                for (auto x : my_leecher) leechervec.push_back(x.second);
                sort(leechervec.begin(),leechervec.end(),cmp_leecher);
                for(int i=0; i<leechervec.size(); i++)
                {
                    peers.push_back(leechervec[i]);
                    count++;
                    if (count == numwant) break;
                }
            }
        }

        // return
        cout<<"OK: ";
        cout<<"COMPLETE="<<complete<<" ";
        cout<<"INCOMPLETE="<<incomplete<<" ";
        cout<<"PEERS=[";
        for (int i=0; i<peers.size(); i++)
        {
            cout<<"("<<peers[i].peer_id<<","<<peers[i].ip<<","<<peers[i].port<<")";
            if (i != peers.size()-1) cout<<",";
        }
        cout<<"]"<<endl;
        return;
    }
    else{
        cout<<"ERROR: Invalid info_hash"<<endl;
        return;
    }


}


int main()
{
    // ios::sync_with_stdio(false);
    // cin.tie(0);
    // cout.tie(0);
    string str;
    while(getline(cin,str))
    {
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
        // cout<<op<<endl;
        // for (auto x : envlist) cout<<x<<endl;
        // cout<<endl;
        if (op == "announce")
        {
            annoounce(envlist);
        }
        else if (op == "add")
        {
            cout<<add(seedlist, envlist)<<endl;
        }
        else if (op == "del")
        {
            cout<<del(seedlist, envlist)<<endl;
        }
        // 30
        else if (op == "scrape")
        {

        }
        // 50
        else if (op == "run")
        {

        }
        // 70
        else if (op == "report")
        {

        }
        // 100
    }
    return 0;
}