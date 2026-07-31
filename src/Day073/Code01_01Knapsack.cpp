// 01背包(模版)
// 给定一个正数t，表示背包的容量
// 有m个货物，每个货物可以选择一次
// 每个货物有自己的体积costs[i]和价值values[i]
// 返回在不超过总容量的情况下，怎么挑选货物能达到价值最大
// 返回最大的价值
// 测试链接 : https://www.luogu.com.cn/problem/P1048
#include <bits/stdc++.h>
using namespace std;

constexpr int MAXM = 101;
constexpr int MAXT = 1001;

int cost[MAXM];
int val[MAXM];
int dp[MAXT];

int T, M;

// 严格位置依赖的动态规划
// n个物品编号1~n，第i号物品的花费cost[i]、价值val[i]
// cost、val数组是全局变量，已经把数据读入了
int compute1()
{
  vector<vector<int>> dp(M + 1, vector<int>(T + 1));
  for (int i = 1; i <= M; i++)
  {
    for (int j = 0; j <= T; j++)
    {
      // 不要i号物品
      dp[i][j] = dp[i - 1][j];
      if (j - cost[i] >= 0)
      {
        // 要i号物品
        dp[i][j] = max(dp[i][j], dp[i - 1][j - cost[i]] + val[i]);
      }
    }
  }

  return dp[M][T];
}

// 空间压缩
int compute2()
{
  fill(begin(dp) + 1, begin(dp) + 1 + T, 0);
  for (int i = 1; i <= M; i++)
  {
    for (int j = T; j >= cost[i]; j--)
    {
      dp[j] = max(dp[j], dp[j - cost[i]] + val[i]);
    }
  }

  return dp[T];
}

int main()
{
  while (cin >> T >> M)
  {
    for (int i = 1; i <= M; i++)
    {
      cin >> cost[i] >> val[i];
    }

    cout << compute1() << endl;
  }

  return 0;
}