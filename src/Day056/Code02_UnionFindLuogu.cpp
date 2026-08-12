// 并查集模版(洛谷)
// 本实现用递归函数实现路径压缩，而且省掉了小挂大的优化，一般情况下可以省略
// 测试链接 : https://www.luogu.com.cn/problem/P3367
#include <bits/stdc++.h>
using namespace std;

constexpr int MAXN = 2E5 + 1;

int father[MAXN];

int n, m, x, y, z;

void build()
{
  for (int i = 0; i <= n; i++)
  {
    father[i] = i;
  }
}

int find(int i)
{
  if (i != father[i])
  {
    father[i] = find(father[i]);
  }

  return father[i];
}

bool isSameSet(int x, int y)
{
  return find(x) == find(y);
}

void Union(int x, int y)
{
  father[find(x)] = find(y);
}

int main()
{
  while (cin >> n >> m)
  {
    build();

    for (int i = 0; i < m; i++)
    {
      cin >> z >> x >> y;
      if (z == 1)
      {
        Union(x, y);
      }
      else
      {
        cout << (isSameSet(x, y) ? 'X' : 'Y') << endl;
      }
    }
  }

  return 0;
}