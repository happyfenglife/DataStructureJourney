// 拓扑排序模版（牛客）
// 链式前向星建图（静态方式）
// 测试链接 : https://www.nowcoder.com/practice/88f7e156ca7d43a1a535f619cd3f495c
#include <iostream>
using namespace std;

constexpr int MAXN = 200005;
constexpr int MAXM = 200005;

int head[MAXN];
int nxt[MAXM];
int to[MAXM];
int cnt;

int l, r;
int arr[MAXN];
int indegree[MAXN];
int ans[MAXN];

int n, m;

void build(int n)
{
  cnt = 1;
  // 只清理 1..n 的部分以提高效率
  fill(head + 1, head + n + 1, 0);
  fill(indegree + 1, indegree + n + 1, 0);
}

void addEdge(int f, int t)
{
  nxt[cnt] = head[f];
  to[cnt] = t;
  head[f] = cnt++;
}

bool topoSort()
{
  l = r = 0;
  for (int i = 1; i <= n; i++)
  {
    if (indegree[i] == 0)
    {
      arr[r++] = i;
    }
  }

  int fill = 0;
  while (l < r)
  {
    int cur = arr[l++];
    ans[fill++] = cur;
    for (int ei = head[cur]; ei != 0; ei = nxt[ei])
    {
      int v = to[ei];
      if (--indegree[v] == 0)
      {
        arr[r++] = v;
      }
    }
  }

  return fill == n;
}

int main()
{
  while ((cin >> n >> m))
  {
    build(n);
    for (int i = 0; i < m; i++)
    {
      int u, v;
      cin >> u >> v;
      addEdge(u, v);
      ++indegree[v];
    }

    if (!topoSort())
    {
      cout << -1 << '\n';
    }
    else
    {
      for (int i = 0; i < n; i++)
      {
        if (i)
        {
          cout << ' ';
        }
        cout << ans[i];
      }

      cout << '\n';
    }
  }

  return 0;
}