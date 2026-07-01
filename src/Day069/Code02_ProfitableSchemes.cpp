// 盈利计划(多维费用背包)
// 集团里有 n 名员工，他们可以完成各种各样的工作创造利润
// 第 i 种工作会产生 profit[i] 的利润，它要求 group[i] 名成员共同参与
// 如果成员参与了其中一项工作，就不能参与另一项工作
// 工作的任何至少产生 minProfit 利润的子集称为 盈利计划
// 并且工作的成员总数最多为 n
// 有多少种计划可以选择？因为答案很大，答案对 1000000007 取模
// 测试链接 : https://leetcode.cn/problems/profitable-schemes/
#include <vector>
using namespace std;

class Solution
{
private:
  static constexpr int MOD = 1000000007;

  int dfs1(const vector<int> &group, const vector<int> &profit,
           int idx, int people, int minProfit)
  {
    if (people <= 0)
    {
      return minProfit <= 0 ? 1 : 0;
    }

    if (idx == static_cast<int>(group.size()))
    {
      return minProfit <= 0 ? 1 : 0;
    }

    int p1 = dfs1(group, profit, idx + 1, people, minProfit);
    int p2 = 0;
    if (group[idx] <= people)
    {
      p2 = dfs1(group, profit, idx + 1,
                people - group[idx], minProfit - profit[idx]);
    }

    return p1 + p2;
  }

  int dfs2(const vector<int> &group, const vector<int> &profit,
           int idx, int people, int minProfit,
           vector<vector<vector<int>>> &memo)
  {
    if (people <= 0)
    {
      return minProfit == 0 ? 1 : 0;
    }

    if (idx == static_cast<int>(group.size()))
    {
      return minProfit == 0 ? 1 : 0;
    }

    if (memo[idx][people][minProfit] != -1)
    {
      return memo[idx][people][minProfit];
    }

    int p1 = dfs2(group, profit, idx + 1, people, minProfit, memo);
    int p2 = 0;
    if (group[idx] <= people)
    {
      p2 = dfs2(group, profit, idx + 1,
                people - group[idx],
                max(0, minProfit - profit[idx]), memo);
    }

    int ans = (p1 + p2) % MOD;
    memo[idx][people][minProfit] = ans;
    return ans;
  }

public:
  // ========== 方法1：暴力递归 ==========
  int profitableSchemes1(int n, int minProfit, vector<int> &group, vector<int> &profit)
  {
    return dfs1(group, profit, 0, n, minProfit);
  }

  // ========== 方法2：记忆化搜索 ==========
  int profitableSchemes2(int n, int minProfit,
                         const vector<int> &group,
                         const vector<int> &profit)
  {
    int m = group.size();
    vector<vector<vector<int>>> memo(
        m, vector<vector<int>>(n + 1,
                                         vector<int>(minProfit + 1, -1)));
    return dfs2(group, profit, 0, n, minProfit, memo);
  }

  // ========== 方法3：三维DP（从后往前递推） ==========
  int profitableSchemes3(int n, int minProfit,
                         const vector<int> &group,
                         const vector<int> &profit)
  {
    int m = group.size();
    vector<vector<vector<int>>> dp(
        m + 1, vector<vector<int>>(n + 1,
                                             vector<int>(minProfit + 1, 0)));

    for (int p = 0; p <= n; p++)
    {
      dp[m][p][0] = 1;
    }

    for (int i = m - 1; i >= 0; i--)
    {
      for (int p = 0; p <= n; p++)
      {
        for (int s = 0; s <= minProfit; s++)
        {
          int p1 = dp[i + 1][p][s];
          int p2 = 0;
          if (group[i] <= p)
          {
            int remainProfit = max(0, s - profit[i]);
            p2 = dp[i + 1][p - group[i]][remainProfit];
          }

          dp[i][p][s] = (p1 + p2) % MOD;
        }
      }
    }

    return dp[0][n][minProfit];
  }

  // ========== 方法4：空间压缩（二维DP，推荐） ==========
  int profitableSchemes4(int n, int minProfit,
                         const vector<int> &group,
                         const vector<int> &profit)
  {
    vector<vector<int>> dp(n + 1,
                                     vector<int>(minProfit + 1, 0));
    for (int p = 0; p <= n; p++)
    {
      dp[p][0] = 1;
    }

    int m = group.size();
    for (int i = m - 1; i >= 0; i--)
    {
      for (int r = n; r >= 0; r--)
      {
        for (int s = minProfit; s >= 0; s--)
        {
          int p1 = dp[r][s];
          int p2 = group[i] <= r ? dp[r - group[i]][max(0, s - profit[i])] : 0;
          dp[r][s] = (p1 + p2) % MOD;
        }
      }
    }

    return dp[n][minProfit];
  }
};