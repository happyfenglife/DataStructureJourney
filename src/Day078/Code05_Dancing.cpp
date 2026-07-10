// 没有上司的舞会
// 某大学有n个职员，编号为1...n
// 他们之间有从属关系，也就是说他们的关系就像一棵以校长为根的树
// 父结点就是子结点的直接上司
// 现在有个周年庆宴会，宴会每邀请来一个职员都会增加一定的快乐指数
// 但是如果某个职员的直接上司来参加舞会了
// 那么这个职员就无论如何也不肯来参加舞会了
// 所以请你编程计算邀请哪些职员可以使快乐指数最大
// 返回最大的快乐指数。
// 测试链接 : https://www.luogu.com.cn/problem/P1352
#include <iostream>
#include <array>
using namespace std;

constexpr int MAXN = 6010;

array<bool, MAXN> boss;
array<int, MAXN> nums;

array<int, MAXN> head;
array<int, MAXN> nxt;
array<int, MAXN> to;

int cnt;
// no[i] : i为头的整棵树，在i不来的情况下，整棵树能得到的最大快乐值
array<int, MAXN> no;
// yes[i] : i为头的整棵树，在i来的情况下，整棵树能得到的最大快乐值
array<int, MAXN> yes;

int n, h;

void build(int n)
{
  fill(boss.begin() + 1, boss.begin() + 1 + n, true);
  fill(head.begin() + 1, head.begin() + 1 + n, 0);
  cnt = 1;
}

void addEdge(int u, int v)
{
  nxt[cnt] = head[u];
  to[cnt] = v;
  head[u] = cnt++;
}

void dfs(int u)
{
  no[u] = 0;
  yes[u] = nums[u];
  for (int ei = head[u], v; ei > 0; ei = nxt[ei])
  {
    v = to[ei];
    dfs(v);
    no[u] += max(no[v], yes[v]);
    yes[u] += no[v];
  }
}

int main()
{
  while (cin >> n)
  {
    build(n);
    for (int i = 1; i <= n; i++)
    {
      cin >> nums[i];
    }

    for (int i = 1, u, v; i < n; i++)
    {
      cin >> u >> v;
      addEdge(v, u);
      boss[u] = false;
    }

    for (int i = 1; i <= n; i++)
    {
      if (boss[i])
      {
        h = i;
        break;
      }
    }

    dfs(h);
    cout << max(no[h], yes[h]) << '\n';
  }

  return 0;
}