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
    node(int name, int g, int h)
    {
        this->name = name;
        this->g = g;
        this->h = h;
        this->f = g + h;
    };
    bool operator<(const node &a) const
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

bool list[20];
vector<node> openList;
bool closeList[20];
stack<int> road;
int parent[20];

void A_star(int goal, node &src, Graph &graph)
{
    openList.push_back(src);
    sort(openList.begin(), openList.end());

    while (!openList.empty())
    {
        /********** Begin **********/
        node now = openList.front();
        if (now.name == goal)
            return;
        openList.erase(openList.begin());
        closeList[now.name] = 1;
        // cout << "now= " << now.name << endl;
        // cout << "closelist: ";
        // for (int i = 0; i < 20; i++)
        //     cout << closeList[i] << " ";
        // cout << endl;
        // cout << "parent: ";
        // for (int i = 0; i < 20; i++)
        //     cout << parent[i] << " ";
        // cout << endl;
        for (int i = 0; i < 20; i++)
        {
            // cout << i << " ";
            // cout << graph.getEdge(now.name, i) << endl;
            if (graph.getEdge(now.name, i) != -1 && !closeList[i])
            {
                node expand(i, now.g + graph.getEdge(now.name, i), h[i]);
                openList.push_back(expand);
                // cout << "expand:" << expand.name << " " << expand.f << " " << expand.g << " " << expand.h << endl;
                int flag = true;
                for (unsigned int j = 0; j < openList.size(); j++)
                {
                    if (openList[j].name == expand.name && openList[j].g < expand.g)
                    {
                        flag = false;
                    }
                }
                if (flag == true)
                    parent[i] = now.name;
            }
        }
        sort(openList.begin(), openList.end());
        // cout << "an expand end" << endl;
        // system("pause");
        /********** End **********/
    }
}

void print_result(Graph &graph)
{
    // for (int i = 0; i < 20; i++)
    //     cout << parent[i] << " ";
    // cout << endl;
    int p = openList[0].name;
    int lastNodeNum;
    road.push(p);
    while (parent[p] != -1)
    {
        // cout << "p= " << p << endl;
        // cout << "parent-p= " << parent[p] << endl;
        // system("pause");
        road.push(parent[p]);
        p = parent[p];
    }
    lastNodeNum = road.top();
    int cost = 0;
    cout << "solution: ";
    while (!road.empty())
    {
        cout << road.top() << "-> ";
        if (road.top() != lastNodeNum)
        {
            cost += graph.getEdge(lastNodeNum, road.top());
            lastNodeNum = road.top();
        }
        road.pop();
    }
    cout << "end" << endl;
    cout << "cost:" << cost;
}

int main()
{
    Graph graph;
    graph.init();
    for (int i = 0; i < 20; i++)
        parent[i] = -1;
    node src(0, 0, h[0]);
    A_star(1, src, graph);
    // for (int i = 0; i < openList.size(); i++)
    //     cout << openList[i].name << " ";
    // cout << "555" << endl;
    print_result(graph);
}
