// 切棍子的最小成本
// 有一根长度为n个单位的木棍，棍上从0到n标记了若干位置
// 给你一个整数数组cuts，其中cuts[i]表示你需要将棍子切开的位置
// 你可以按顺序完成切割，也可以根据需要更改切割的顺序
// 每次切割的成本都是当前要切割的棍子的长度，切棍子的总成本是历次切割成本的总和
// 对棍子进行切割将会把一根木棍分成两根较小的木棍
// 这两根木棍的长度和就是切割前木棍的长度
// 返回切棍子的最小总成本
// 测试链接 : https://leetcode.cn/problems/minimum-cost-to-cut-a-stick/
#include <vector>
#include <limits>
#include <algorithm>
using namespace std;

class Solution
{
public:
  // 记忆化搜索
  int minCost1(int n, vector<int> &cuts)
  {
    int m = static_cast<int>(cuts.size());
    sort(cuts.begin(), cuts.end());
    vector<int> arr(m + 2);
    arr[0] = 0;
    arr[m + 1] = n;
    for (int i = 0; i < m; i++)
    {
      arr[i + 1] = cuts[i];
    }

    vector<vector<int>> dp(m + 2, vector<int>(m + 2, 0));
    for (int i = 1; i <= m; i++)
    {
      for (int j = 1; j <= m; j++)
      {
        dp[i][j] = -1;
      }
    }

    return f(arr, 1, m, dp);
  }

  // 严格位置依赖的动态规划
  int minCost2(int n, vector<int> &cuts)
  {
    int m = static_cast<int>(cuts.size());
    sort(cuts.begin(), cuts.end());
    vector<int> arr(m + 2);
    arr[0] = 0;
    arr[m + 1] = n;
    for (int i = 0; i < m; i++)
    {
      arr[i + 1] = cuts[i];
    }

    vector<vector<int>> dp(m + 2, vector<int>(m + 2, 0));
    for (int i = 1; i <= m; i++)
    {
      dp[i][i] = arr[i + 1] - arr[i - 1];
    }

    for (int l = m - 1, ans; l >= 1; l--)
    {
      for (int r = l + 1; r <= m; r++)
      {
        ans = numeric_limits<int>::max();
        for (int k = l; k <= r; k++)
        {
          ans = min(ans, dp[l][k - 1] + dp[k + 1][r]);
        }

        dp[l][r] += ans + arr[r + 1] - arr[l - 1];
      }
    }

    return dp[1][m];
  }

private:
  // 切点 [l....r]，决定一个顺序
  // 让切点都切完，总代价最小
  int f(const vector<int> &arr, int l, int r, vector<vector<int>> &dp)
  {
    if (l > r)
    {
      return 0;
    }

    if (l == r)
    {
      return arr[r + 1] - arr[l - 1];
    }

    if (dp[l][r] != -1)
    {
      return dp[l][r];
    }

    int ans = numeric_limits<int>::max();
    for (int k = l; k <= r; k++)
    {
      ans = min(ans, f(arr, l, k - 1, dp) + f(arr, k + 1, r, dp));
    }

    ans += arr[r + 1] - arr[l - 1];
    dp[l][r] = ans;
    return ans;
  }
};