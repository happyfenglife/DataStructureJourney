// 拓扑排序模版（ACM Style）
// 邻接表建图（动态方式）
// 测试链接 : https://www.nowcoder.com/practice/88f7e156ca7d43a1a535f619cd3f495c
#include <iostream>
#include <vector>
using namespace std;

int main()
{
  int n, m;

  // 支持多组输入直到 EOF
  while ((cin >> n >> m))
  {
    vector<vector<int>> graph(n + 1);
    vector<int> indegree(n + 1, 0);

    for (int i = 0; i < m; i++)
    {
      int from, to;
      cin >> from >> to;
      graph[from].push_back(to);
      ++indegree[to];
    }

    // 用 vector 作为队列，head 指针模拟出队，避免频繁 pop_front
    vector<int> q;
    q.reserve(n);
    for (int i = 0; i <= n; i++)
    {
      if (indegree[i] == 0)
      {
        q.push_back(i);
      }
    }

    vector<int> ans;
    ans.reserve(n);
    size_t head = 0;
    while (head < q.size())
    {
      int cur = q[head++];
      ans.push_back(cur);
      for (int nxt : graph[cur])
      {
        if (--indegree[nxt] == 0)
        {
          q.push_back(nxt);
        }
      }
    }

    if ((int)ans.size() != n)
    {
      cout << -1 << '\n';
    }
    else
    {
      for (int i = 0; i < n; i++)
      {
        if (i)
          cout << ' ';

        cout << ans[i];
      }

      cout << '\n';
    }
  }

  return 0;
}