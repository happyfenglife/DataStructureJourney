// 银河英雄传说
// 一共有30000搜战舰，编号1~30000，一开始每艘战舰各自成一队
// 如果若干战舰变成一队，那么队伍里的所有战舰竖直地排成一列
// 实现如下两种操作，操作一共调用t次
// M l r : 合并l号战舰所在队伍和r号战舰所在队伍
//         l号战舰的队伍，整体移动到，r号战舰所在队伍的最末尾战舰的后面
//         如果l号战舰和r号战舰已经是一队，不进行任何操作
// C l r : 如果l号战舰和r号战舰不在一个队伍，打印-1
//         如果l号战舰和r号战舰在一个队伍，打印它俩中间隔着几艘战舰
// 1 <= t <= 5 * 10^5
// 测试链接 : https://www.luogu.com.cn/problem/P1196
#include <bits/stdc++.h>
using namespace std;

constexpr int MAXN = 3E4 + 1;

int n = 30000, t;
string op;

int father[MAXN];
int dist[MAXN];
int sz[MAXN];

// 递归会爆栈，所以用迭代来寻找并查集代表节点
int st[MAXN];

void build()
{
  for (int i = 1; i <= n; i++)
  {
    father[i] = i;
    dist[i] = 0;
    sz[i] = 1;
  }
}

int find(int i)
{
  int si{};
  while (i != father[i])
  {
    st[++si] = i;
    i = father[i];
  }

  st[si + 1] = i;
  for (int j = si; j >= 1; j--)
  {
    father[st[j]] = i;
    dist[st[j]] += dist[st[j + 1]];
  }

  return i;
}

void unionSet(int l, int r)
{
  int lf = find(l), rf = find(r);
  if (lf != rf)
  {
    father[lf] = rf;
    dist[lf] += sz[rf];
    sz[rf] += sz[lf];
  }
}

int query(int l, int r)
{
  if (find(l) != find(r))
  {
    return -1;
  }

  return abs(dist[l] - dist[r]) - 1;
}

int main()
{
  build();
  while (cin >> t)
  {
    for (int i = 0, l, r; i < t; i++)
    {
      cin >> op >> l >> r;
      if (op == "M")
      {
        unionSet(l, r);
      }
      else
      {
        cout << query(l, r) << '\n';
      }
    }
  }

  return 0;
}