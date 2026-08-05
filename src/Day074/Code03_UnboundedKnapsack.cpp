// 完全背包(模版)
// 给定一个正数t，表示背包的容量
// 有m种货物，每种货物可以选择任意个
// 每种货物都有体积costs[i]和价值values[i]
// 返回在不超过总容量的情况下，怎么挑选货物能达到价值最大
// 返回最大的价值
// 测试链接 : https://www.luogu.com.cn/problem/P1616
#include <bits/stdc++.h>
using namespace std;

constexpr int MAXM = 10001;
constexpr int MAXT = 10000001;

using ll = long long;

int cost[MAXM];
int val[MAXM];
ll dp[MAXT];

int t, m;

// 严格位置依赖的动态规划
// 会空间不够，导致无法通过全部测试用例
ll compute1()
{
  int dp[m + 1][t + 1];
  for (int i = 1; i <= m; i++)
  {
    for (int j = 0; j <= t; j++)
    {
      dp[i][j] = dp[i - 1][j];
      if (j - cost[i] >= 0)
      {
        dp[i][j] = max(dp[i][j],
                       dp[i][j - cost[i]] + val[i]);
      }
    }
  }

  return dp[m][t];
}

// 空间压缩
// 可以通过全部测试用例
ll compute2()
{
  fill(begin(dp) + 1, begin(dp) + 1 + t, 0);
  for (int i = 1; i <= m; i++)
  {
    for (int j = cost[i]; j <= t; j++)
    {
      dp[j] = max(dp[j], dp[j - cost[i]] + val[i]);
    }
  }

  return dp[t];
}

int main()
{
  while (cin >> t >> m)
  {
    for (int i = 1; i <= m; i++)
    {
      cin >> cost[i] >> val[i];
    }

    cout << compute2() << endl;
  }

  return 0;
}