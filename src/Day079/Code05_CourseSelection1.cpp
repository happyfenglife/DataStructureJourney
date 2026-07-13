// 选课，树上01背包的普通解法
// 在大学里每个学生，为了达到一定的学分，必须从很多课程里选择一些课程来学习
// 在课程里有些课程必须在某些课程之前学习，如高等数学总是在其它课程之前学习
// 现在有 N 门功课，每门课有个学分，每门课有一门或没有直接先修课
// 若课程 a 是课程 b 的先修课即只有学完了课程 a，才能学习课程 b
// 一个学生要从这些课程里选择 M 门课程学习
// 问他能获得的最大学分是多少
// 测试链接 : https://www.luogu.com.cn/problem/P2014

// 邻接表建图 + 相对好懂的动态规划
// 时间复杂度O(n * 每个节点的孩子平均数量 * m的平方)
#include <iostream>
#include <vector>
using namespace std;

constexpr int MAXN = 301;

vector<int> nums(MAXN);
vector<vector<int>> graph(MAXN);
vector<vector<vector<int>>> dp(MAXN);

int n, m;

void build()
{
  for (int i = 0; i <= n; i++)
  {
    graph[i].clear();
  }
}

int dfs(int i, int j, int k)
{
  if (k == 0)
  {
    return 0;
  }

  if (j == 0 || k == 1)
  {
    return nums[i];
  }

  if (dp[i][j][k] != -1)
  {
    return dp[i][j][k];
  }

  int ans = dfs(i, j - 1, k);
  int v = graph[i][j - 1];
  for (int s = 1; s < k; s++)
  {
    ans = max(ans, dfs(i, j - 1, k - s) + dfs(v, static_cast<int>(graph[v].size()), s));
  }

  dp[i][j][k] = ans;
  return ans;
}

int compute()
{
  for (int i = 0; i <= n; i++)
  {
    dp[i].assign(graph[i].size() + 1, vector<int>(m + 1, -1));
  }

  return dfs(0, graph[0].size(), m);
}

int main()
{
  while (cin >> n >> m)
  {
    ++m;
    build();

    for (int i = 1, pre; i <= n; i++)
    {
      cin >> pre;
      graph[pre].push_back(i);
      cin >> nums[i];
    }

    cout << compute() << '\n';
  }

  return 0;
}