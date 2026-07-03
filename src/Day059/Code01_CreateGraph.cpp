#include <vector>
#include <array>
#include <iostream>
using namespace std;

// 点的最大数量
constexpr int MAXN = 11;
// 边的最大数量（链式前向星需要）
constexpr int MAXM = 21;

// 邻接矩阵
int graph1[MAXN][MAXN];

// 邻接表: graph2[u] 存放 pair<邻居, 权重>
vector<vector<pair<int, int>>> graph2;

// 链式前向星
int head[MAXN];
int nextArr[MAXM];
int to[MAXM];
int weight[MAXM];
int cnt;

// 初始化/清空结构，节点编号按 1..n 使用
void build(int n)
{
  // 邻接矩阵清空
  for (int i = 1; i <= n; i++)
  {
    for (int j = 1; j <= n; j++)
    {
      graph1[i][j] = 0;
    }
  }

  // 邻接表清空并准备 n+1 个列表（0 下标保留但不用）
  graph2.clear();
  graph2.resize(n + 1);

  // 链式前向星清空
  cnt = 1;
  fill(head + 1, head + n + 1, 0);
}

// 链式前向星加边 u -> v，权重 w
void addEdge(int u, int v, int w)
{
  nextArr[cnt] = head[u];
  to[cnt] = v;
  weight[cnt] = w;
  head[u] = cnt++;
}

// 有向带权图三种方式建图，edges 每一项是 {u, v, w}
void directGraph(const vector<array<int, 3>> &edges)
{
  // 邻接矩阵
  for (const auto &e : edges)
  {
    graph1[e[0]][e[1]] = e[2];
  }

  // 邻接表
  for (const auto &e : edges)
  {
    graph2[e[0]].push_back({e[1], e[2]});
  }

  // 链式前向星
  for (const auto &e : edges)
  {
    addEdge(e[0], e[1], e[2]);
  }
}

// 无向带权图三种方式建图
void undirectGraph(const vector<array<int, 3>> &edges)
{
  // 邻接矩阵
  for (const auto &e : edges)
  {
    graph1[e[0]][e[1]] = e[2];
    graph1[e[1]][e[0]] = e[2];
  }

  // 邻接表
  for (const auto &e : edges)
  {
    graph2[e[0]].push_back({e[1], e[2]});
    graph2[e[1]].push_back({e[0], e[2]});
  }

  // 链式前向星（每条无向边加入两条有向边）
  for (const auto &e : edges)
  {
    addEdge(e[0], e[1], e[2]);
    addEdge(e[1], e[0], e[2]);
  }
}

// 打印三种结构
void traversal(int n)
{
  cout << "邻接矩阵遍历 :" << endl;
  for (int i = 1; i <= n; i++)
  {
    for (int j = 1; j <= n; j++)
    {
      cout << graph1[i][j] << " ";
    }

    cout << '\n';
  }

  cout << "邻接表遍历 :" << endl;
  for (int i = 1; i <= n; i++)
  {
    cout << i << "(邻居、边权) : ";
    for (const auto &p : graph2[i])
    {
      cout << "(" << p.first << "," << p.second << ") ";
    }

    cout << '\n';
  }

  cout << "链式前向星 :" << endl;
  for (int i = 1; i <= n; i++)
  {
    cout << i << "(邻居、边权) : ";
    for (int ei = head[i]; ei > 0; ei = nextArr[ei])
    {
      cout << "(" << to[ei] << "," << weight[ei] << ") ";
    }

    cout << '\n';
  }
}

int main()
{
  // 示例1：有向带权图
  int n1 = 4;
  vector<array<int, 3>> edges1 = {
      array<int, 3>{1, 3, 6},
      array<int, 3>{4, 3, 4},
      array<int, 3>{2, 4, 2},
      array<int, 3>{1, 2, 7},
      array<int, 3>{2, 3, 5},
      array<int, 3>{3, 1, 1}};
  build(n1);
  directGraph(edges1);
  traversal(n1);

  cout << "==============================" << endl;

  // 示例2：无向带权图
  int n2 = 5;
  vector<array<int, 3>> edges2 = {
      array<int, 3>{3, 5, 4},
      array<int, 3>{4, 1, 1},
      array<int, 3>{3, 4, 2},
      array<int, 3>{5, 2, 4},
      array<int, 3>{2, 3, 7},
      array<int, 3>{1, 5, 5},
      array<int, 3>{4, 2, 6}};
  build(n2);
  undirectGraph(edges2);
  traversal(n2);

  return 0;
}