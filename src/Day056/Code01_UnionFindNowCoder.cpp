// 并查集模版(牛客)
// 路径压缩 + 小挂大
// 测试链接 : https://www.nowcoder.com/practice/e7ed657974934a30b2010046536a5372
#include <bits/stdc++.h>
using namespace std;

constexpr int MAXN = 1E6 + 1;

int father[MAXN];
int sz[MAXN];
int st[MAXN];

int N, M, opt;

void build()
{
  for (int i = 0; i <= N; i++)
  {
    father[i] = i;
    sz[i] = 1;
  }
}

// i号节点，往上一直找，找到代表节点返回！
int find(int i)
{
  // 沿途收集了几个点
  int cnt = 0;
  while (i != father[i])
  {
    st[cnt++] = i;
    i = father[i];
  }

  // 沿途节点收集好了，i已经跳到代表节点了
  while (cnt > 0)
  {
    father[st[--cnt]] = i;
  }

  return i;
}

bool isSameSet(int x, int y)
{
  return find(x) == find(y);
}

void Union(int x, int y)
{
  int fx = find(x), fy = find(y);
  if (fx != fy)
  {
    // fx是集合的代表：拿大小
    // fy是集合的代表：拿大小
    if (sz[fx] >= sz[fy])
    {
      sz[fx] += sz[fy];
      father[fy] = fx;
    }
    else
    {
      sz[fy] += sz[fx];
      father[fx] = fy;
    }
  }
}

int main()
{
  while (cin >> N >> M)
  {
    build();
    for (int i = 0, x, y; i < M; i++)
    {
      cin >> opt >> x >> y;
      if (opt == 1)
      {
        cout << (isSameSet(x, y) ? "Yes" : "No") << endl;
      }
      else
      {
        Union(x, y);
      }
    }
  }

  return 0;
}