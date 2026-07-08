// 字典序最小的拓扑排序
// 要求返回所有正确的拓扑排序中 字典序最小 的结果
// 建图请使用链式前向星方式，因为比赛平台用其他建图方式会卡空间
// 测试链接 : https://www.luogu.com.cn/problem/U107394
#include <iostream>
#include <algorithm>
#include <array>
#include <queue>
using namespace std;

constexpr int MAXN = 1e5 + 1;
constexpr int MAXM = 1e5 + 1;

array<int, MAXN> head;
array<int, MAXM> nxt;
array<int, MAXM> to;

array<int, MAXN> indegree;
array<int, MAXN> ans;

priority_queue<int, vector<int>,
               greater<int>>
    heap;
int cnt;

int n, m;

void build(int n)
{
  cnt = 1;
  fill(head.begin() + 1, head.begin() + 1 + n, 0);
  fill(indegree.begin() + 1, indegree.begin() + 1 + n, 0);
}

void addEdge(int u, int v)
{
  nxt[cnt] = head[u];
  to[cnt] = v;
  indegree[v]++;
  head[u] = cnt++;
}

void topoSort()
{
  for (int i = 1; i <= n; i++)
  {
    if (indegree[i] == 0)
    {
      heap.push(i);
    }
  }

  int fill = 0;
  while (!heap.empty())
  {
    int cur = heap.top();
    heap.pop();
    ans[fill++] = cur;

    for (int ei = head[cur]; ei != 0; ei = nxt[ei])
    {
      if (--indegree[to[ei]] == 0)
      {
        heap.push(to[ei]);
      }
    }
  }
}

int main()
{
  while (cin >> n >> m)
  {
    build(n);
    for (int i = 0, u, v; i < m; i++)
    {
      cin >> u >> v;
      addEdge(u, v);
    }

    topoSort();
    for (int i = 0; i < n - 1; i++)
    {
      cout << ans[i] << ' ';
    }
    cout << ans[n - 1] << '\n';
  }

  return 0;
}