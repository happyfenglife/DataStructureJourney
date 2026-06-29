// 不同的子序列
// 给你两个字符串s和t ，统计并返回在s的子序列中t出现的个数
// 答案对 1000000007 取模
// 测试链接 : https://leetcode.cn/problems/distinct-subsequences/
#include <string>
#include <vector>
using namespace std;

class Solution
{
public:
  const int MOD = 1e9 + 7;

  // 1. 二维动态规划
  int numDistinct1(string s, string t)
  {
    int n = s.size(), m = t.size();

    // s[前缀长度为i]的所有子序列中，有多少个子序列等于t[前缀长度为j]
    vector<vector<int>> dp(n + 1, vector<int>(m + 1));
    for (int i = 0; i <= n; i++)
    {
      dp[i][0] = 1;
    }

    for (int i = 1; i <= n; i++)
    {
      for (int j = 1; j <= m; j++)
      {
        dp[i][j] = dp[i - 1][j];

        if (s[i - 1] == t[j - 1])
        {
          dp[i][j] = (dp[i][j] + dp[i - 1][j - 1]) % MOD;
        }
      }
    }

    return dp[n][m];
  }

  // 2. 空间压缩
  int numDistinct2(string s, string t)
  {
    int n = s.size(), m = t.size();
    vector<int> dp(m + 1, 0);
    dp[0] = 1;
    for (int i = 1; i <= n; i++)
    {
      for (int j = m; j >= 1; j--)
      {
        if (s[i - 1] == t[j - 1])
        {
          dp[j] = (dp[j] + dp[j - 1]) % MOD;
        }
      }
    }

    return dp[m];
  }
};