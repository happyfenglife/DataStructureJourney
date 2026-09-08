// 狡猾的商人，带权并查集模版题2
// 有n个月的收入，下标1 ~ n，但是并不知道每个月收入是多少
// 操作 l r v，代表从第l个月到第r个月，总收入为v
// 一共给你m个操作，请判断给定的数据是自洽还是自相矛盾
// 自洽打印true，自相矛盾打印false
// 1 <= n <= 100    1 <= m <= 1000
// 总收入不会超过int类型范围
// 测试链接 : https://www.luogu.com.cn/problem/P2294
#include <bits/stdc++.h>
using namespace std;

constexpr int MAXN = 102;

int father[MAXN];
int dist[MAXN];

bool ans;
int t, n, m;

void build()
{
  ans = true;
  for (int i = 1; i <= n; i++)
  {
    father[i] = i;
    dist[i] = 0;
  }
}

int find(int i)
{
  if (i != father[i])
  {
    int tmp = father[i];
    father[i] = find(tmp);
    dist[i] += dist[tmp];
  }

  return father[i];
}

void unionSet(int l, int r, int v)
{
  int lf = find(l), rf = find(r);
  if (lf != rf)
  {
    father[lf] = rf;
    dist[lf] = v + dist[r] - dist[l];
  }
}

bool check(int l, int r, int v)
{
  if (find(l) == find(r))
  {
    if ((dist[l] - dist[r]) != v)
    {
      return false;
    }
  }

  return true;
}

int main()
{
  while (cin >> t)
  {
    for (int i = 0; i < t; i++)
    {
      cin >> n >> m;
      n++;
      build();

      for (int j = 0, l, r, v; j < m; j++)
      {
        cin >> l >> r >> v;
        r++;
        if (!check(l, r, v))
        {
          ans = false;
        }
        else
        {
          unionSet(l, r, v);
        }
      }

      cout << (ans ? "true" : "false") << '\n';
    }
  }

  return 0;
}