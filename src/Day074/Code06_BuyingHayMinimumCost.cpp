// 购买足量干草的最小花费
// 有n个提供干草的公司，每个公司都有两个信息
// cost[i]代表购买1次产品需要花的钱
// val[i]代表购买1次产品所获得的干草数量
// 每个公司的产品都可以购买任意次
// 你一定要至少购买h数量的干草，返回最少要花多少钱
// 测试链接 : https://www.luogu.com.cn/problem/P2918
#include <bits/stdc++.h>
using namespace std;

constexpr int MAXN = 101;
constexpr int MAXM = 55001;

int val[MAXN];
int cost[MAXN];
int dp[MAXM];

int n, h, m;

// dp[i][j] : 1...i里挑公司，购买严格j磅干草，需要的最少花费
// 1) dp[i-1][j]
// 2) dp[i][j-val[i]] + cost[i]
// 两种可能性中选最小
// 但是关于j需要进行一定的扩充，原因视频里讲了
int compute1()
{
  vector<vector<int>> dp(n + 1,
                         vector<int>(m + 1, INT_MAX));
  dp[0][0] = 0;
  for (int i = 1; i <= n; i++)
  {
    for (int j = 0; j <= m; j++)
    {
      dp[i][j] = dp[i - 1][j];
      if (j - val[i] >= 0 && dp[i][j - val[i]] != INT_MAX)
      {
        dp[i][j] = min(dp[i][j], dp[i][j - val[i]] + cost[i]);
      }
    }
  }

  int ans{INT_MAX};
  // >= h
  // h h+1 h+2 ... m
  for (int j = h; j <= m; j++)
  {
    ans = min(ans, dp[n][j]);
  }

  return ans;
}

// 空间压缩
int compute2()
{
  fill(begin(dp) + 1, begin(dp) + 1 + m, INT_MAX);
  for (int i = 1; i <= n; i++)
  {
    for (int j = val[i]; j <= m; j++)
    {
      if (dp[j - val[i]] != INT_MAX)
      {
        dp[j] = min(dp[j], dp[j - val[i]] + cost[i]);
      }
    }
  }

  int ans{INT_MAX};
  for (int j = h; j <= m; j++)
  {
    ans = min(ans, dp[j]);
  }

  return ans;
}

int main()
{
  while (cin >> n >> h)
  {
    int maxv{};
    for (int i = 1; i <= n; i++)
    {
      cin >> val[i] >> cost[i];
      maxv = max(maxv, val[i]);
    }

    m = h + maxv;
    cout << compute1() << endl;
  }

  return 0;
}