// 错误答案数量，带权并查集模版题3
// 有n个数字，下标1 ~ n，但是并不知道每个数字是多少
// 操作 l r v，代表l~r范围上累加和为v
// 一共m个操作，如果某个操作和之前的操作信息自相矛盾，认为当前操作是错误的，不进行这个操作
// 最后打印错误操作的数量
// 1 <= n <= 200000    1 <= m <= 40000
// 累加和不会超过int类型范围
// 测试链接 : https://acm.hdu.edu.cn/showproblem.php?pid=3038
// 测试链接 : https://vjudge.net/problem/HDU-3038
#include <bits/stdc++.h>
using namespace std;

constexpr int MAXN = 200002;

int father[MAXN];
int dist[MAXN];

int n, m, ans;

void build()
{
  ans = 0;
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
  while (cin >> n >> m)
  {
    n++;
    build();
    for (int i = 0, l, r, v; i < m; i++)
    {
      cin >> l >> r >> v;
      r++;
      if (!check(l, r, v))
      {
        ans++;
      }
      else
      {
        unionSet(l, r, v);
      }
    }

    cout << ans << '\n';
  }

  return 0;
}