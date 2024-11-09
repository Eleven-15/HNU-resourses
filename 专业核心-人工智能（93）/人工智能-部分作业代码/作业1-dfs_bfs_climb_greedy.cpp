#include <algorithm>
#include <iostream>
#include <memory.h>
#include <queue>
#include <stack>
#include <vector>
#define N 6
#define S 0
#define A 1
#define B 2
#define C 3
#define D 4
#define G 5

using namespace std;

int h[20] = {11, 8, 9, 10, 5, 0};

struct node
{
    int name;
    char cname;
    int h;
    node(int name, int h)
    {
        this->name = name;
        this->h = h;
        switch (name)
        {
        case 0:
        {
            cname = 'S';
            break;
        }
        case 1:
        {
            cname = 'A';
            break;
        }
        case 2:
        {
            cname = 'B';
            break;
        }
        case 3:
        {
            cname = 'C';
            break;
        }
        case 4:
        {
            cname = 'D';
            break;
        }
        case 5:
        {
            cname = 'G';
            break;
        }
        }
    };
};

class Graph
{
public:
    Graph()
    {
        memset(graph, -1, sizeof(graph));
    }
    int getEdge(int from, int to)
    {
        return graph[from][to];
    }
    void addEdge(int from, int to, int cost)
    {
        if (from >= N || from < 0 || to >= N || to < 0)
            return;
        graph[from][to] = cost;
    }

    void init()
    {
        addEdge(S, A, 1);
        addEdge(A, S, 1);
        addEdge(S, B, 1);
        addEdge(B, S, 1);
        addEdge(A, B, 1);
        addEdge(B, A, 1);
        addEdge(A, D, 1);
        addEdge(D, A, 1);
        addEdge(B, D, 1);
        addEdge(D, B, 1);
        addEdge(D, G, 1);
        addEdge(G, D, 1);
        addEdge(B, C, 1);
        addEdge(C, B, 1);
    }

private:
    int graph[N][N];
};

bool dfs_visited[N] = {0};
void dfs(int goal, node &src, Graph &graph)
{
    if (src.name == goal)
    {
        cout << src.cname << endl;
        return;
    }
    dfs_visited[src.name] = 1;
    cout << src.cname << " -> ";
    for (int i = 0; i < N; i++)
    {
        if (graph.getEdge(src.name, i) == 1 && !dfs_visited[i])
        {
            node des(i, 0);
            dfs(goal, des, graph);
        }
    }
}

void bfs(int goal, node &src, Graph &graph)
{
    bool bfs_visited[N] = {0};
    queue<node> q;
    q.push(src);
    while (!q.empty())
    {
        node src = q.front();
        q.pop();
        bfs_visited[src.name] = 1;
        if (src.name == goal)
        {
            cout << src.cname << endl;
            break;
        }
        cout << src.cname << " -> ";
        for (int i = 0; i < N; i++)
        {
            if (graph.getEdge(src.name, i) == 1 && !bfs_visited[i])
            {
                node des(i, 0);
                bfs_visited[i] = 1;
                q.push(des);
                // cout << "extend" << i << endl;
            }
        }
    }
    return;
}

bool cm_visited[N] = {0};
const int MAXNUM = 99999;
void climb_mountain(int goal, node &src, Graph &graph)
{
    if (src.name == goal)
    {
        cout << src.cname << endl;
        return;
    }
    cm_visited[src.name] = 1;
    cout << src.cname << " -> ";
    int h_best = MAXNUM;
    int next_visit = 0;
    for (int i = 0; i < N; i++)
    {
        if (graph.getEdge(src.name, i) == 1 && !cm_visited[i])
        {
            if (h[i] < h_best)
            {
                h_best = h[i];
                next_visit = i;
            }
        }
    }
    node des(next_visit, h_best);
    climb_mountain(goal, des, graph);
}

bool greedy_visited[N] = {0};
void greedy_best_first(int goal, node &src, Graph &graph)
{
    if (src.name == goal)
    {
        cout << src.cname << endl;
        return;
    }
    greedy_visited[src.name] = 1;
    cout << src.cname << " -> ";
    int h_best = MAXNUM;
    int next_visit = 0;
    for (int i = 0; i < N; i++)
    {
        if (graph.getEdge(src.name, i) == 1 && !greedy_visited[i])
        {
            if (h[i] < h_best)
            {
                h_best = h[i];
                next_visit = i;
            }
        }
    }
    node des(next_visit, h_best);
    greedy_best_first(goal, des, graph);
}

int main()
{
    Graph graph;
    graph.init();
    node src(S, h[S]);
    cout << "dfs:  ";
    dfs(G, src, graph);
    cout << "bfs:  ";
    bfs(G, src, graph);
    cout << "climb mountain:  ";
    climb_mountain(G, src, graph);
    cout << "greedy_best_first:  ";
    greedy_best_first(G, src, graph);
}
