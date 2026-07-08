// 最大食物链计数
// a -> b，代表a在食物链中被b捕食
// 给定一个有向无环图，返回
// 这个图中从最初级动物到最顶级捕食者的食物链有几条
// 测试链接 : https://www.luogu.com.cn/problem/P4017
#include <iostream>
#include <array>
#include <algorithm>
using namespace std;

constexpr int MOD = 80112002;
constexpr int MAXN = 5010;
constexpr int MAXM = 500010;

array<int, MAXN> head;
array<int, MAXM> nxt;
array<int, MAXM> to;

array<int, MAXN> indegree;
array<int, MAXN> lines;
array<int, MAXN> q;

int cnt;
int n, m;

void build(int n)
{
  cnt = 1;
  fill(head.begin() + 1, head.begin() + 1 + n, 0);
  fill(indegree.begin() + 1, indegree.begin() + 1 + n, 0);
  fill(lines.begin() + 1, lines.begin() + 1 + n, 0);
}

void addEdge(int u, int v)
{
  nxt[cnt] = head[u];
  to[cnt] = v;
  indegree[v]++;
  head[u] = cnt++;
}

int ways()
{
  int l = 0, r = 0;
  for (int i = 1; i <= n; i++)
  {
    if (indegree[i] == 0)
    {
      q[r++] = i;
      lines[i] = 1;
    }
  }

  int ans = 0;
  while (l < r)
  {
    int u = q[l++];
    if (head[u] == 0)
    {
      // 当前的u节点不再有后续邻居了
      ans = (ans + lines[u]) % MOD;
    }
    else
    {
      for (int ei = head[u], v; ei != 0; ei = nxt[ei])
      {
        v = to[ei];
        lines[v] = (lines[v] + lines[u]) % MOD;
        if (--indegree[v] == 0)
        {
          q[r++] = v;
        }
      }
    }
  }

  return ans;
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

    cout << ways() << '\n';
  }

  return 0;
}