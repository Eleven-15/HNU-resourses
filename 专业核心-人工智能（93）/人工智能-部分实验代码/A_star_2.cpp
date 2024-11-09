#include <algorithm>
#include <iostream>
#include <memory.h>
#include <stack>
#include <vector>
#define A 0
#define B 1
#define C 2
#define D 3
#define E 4
#define F 5
#define G 6
#define H 7
#define I 8
#define L 9
#define M 10
#define N 11
#define O 12
#define P 13
#define R 14
#define S 15
#define T 16
#define U 17
#define V 18
#define Z 19

using namespace std;

int h[20] =
    {366, 0, 160, 242, 161,
     178, 77, 151, 226, 244,
     241, 234, 380, 98, 193,
     253, 329, 80, 199, 374};

struct node
{
    int g;
    int h;
    int f;
    int name;
    node *parent;
    node() {}
    node(int name, int g, int h, node *parent)
    {
        this->name = name;
        this->g = g;
        this->h = h;
        this->f = g + h;
        this->parent = parent;
    };
    bool operator<(const node a) const
    {
        return f < a.f;
    }
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
        if (from >= 20 || from < 0 || to >= 20 || to < 0)
            return;
        graph[from][to] = cost;
    }

    void init()
    {
        addEdge(O, Z, 71);
        addEdge(Z, O, 71);

        addEdge(O, S, 151);
        addEdge(S, O, 151);

        addEdge(Z, A, 75);
        addEdge(A, Z, 75);

        addEdge(A, S, 140);
        addEdge(S, A, 140);

        addEdge(A, T, 118);
        addEdge(T, A, 118);

        addEdge(T, L, 111);
        addEdge(L, T, 111);

        addEdge(L, M, 70);
        addEdge(M, L, 70);

        addEdge(M, D, 75);
        addEdge(D, M, 75);

        addEdge(D, C, 120);
        addEdge(C, D, 120);

        addEdge(C, R, 146);
        addEdge(R, C, 146);

        addEdge(S, R, 80);
        addEdge(R, S, 80);

        addEdge(S, F, 99);
        addEdge(F, S, 99);

        addEdge(F, B, 211);
        addEdge(B, F, 211);

        addEdge(P, C, 138);
        addEdge(C, P, 138);

        addEdge(R, P, 97);
        addEdge(P, R, 97);

        addEdge(P, B, 101);
        addEdge(B, P, 101);

        addEdge(B, G, 90);
        addEdge(G, B, 90);

        addEdge(B, U, 85);
        addEdge(U, B, 85);

        addEdge(U, H, 98);
        addEdge(H, U, 98);

        addEdge(H, E, 86);
        addEdge(E, H, 86);

        addEdge(U, V, 142);
        addEdge(V, U, 142);

        addEdge(I, V, 92);
        addEdge(V, I, 92);

        addEdge(I, N, 87);
        addEdge(N, I, 87);
    }

private:
    int graph[20][20];
};

vector<node *> openList;
node *des;
bool visited[20];

bool cmp(node *a, node *b) { return a->f < b->f; }
void A_star(int goal, node *src, Graph &graph)
{
    openList.push_back(src);
    sort(openList.begin(), openList.end(), cmp);

    while (!openList.empty())
    {
        node *now = new node;
        now = openList.front();
        openList.erase(openList.begin());
        visited[now->name] = 1;
        // cout << now->name << endl;
        // system("pause");
        if (now->name == goal)
        {
            des = now;
            return;
        }
        for (int i = 0; i < 20; i++)
        {
            if (graph.getEdge(now->name, i) != -1 && !visited[i])
            {
                node *expand = new node(i, now->g + graph.getEdge(now->name, i), h[i], now);
                openList.push_back(expand);
                // cout << "expand: " << expand->name << endl;
            }
        }
        sort(openList.begin(), openList.end(), cmp);
    }
}

void print_result(Graph &graph)
{
    cout << "solution: ";
    stack<int> ans;
    node *now = des;
    while (now != NULL)
    {
        ans.push(now->name);
        // cout << now->name << endl;
        now = now->parent;
    }
    while (!ans.empty())
    {
        cout << ans.top() << "-> ";
        ans.pop();
    }
    cout << "end" << endl;
    cout << "cost:" << des->g << endl;
}

int main()
{
    Graph graph;
    graph.init();
    memset(visited, 0, sizeof(visited));
    node *src = new node(0, 0, h[0], NULL);
    A_star(1, src, graph);
    print_result(graph);
}
