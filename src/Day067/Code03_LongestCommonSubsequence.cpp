// 最长公共子序列
// 给定两个字符串text1和text2
// 返回这两个字符串的最长 公共子序列 的长度
// 如果不存在公共子序列，返回0
// 两个字符串的 公共子序列 是这两个字符串所共同拥有的子序列
// 测试链接 : https://leetcode.cn/problems/longest-common-subsequence/
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class Solution
{
private:
  int f1(const string &s1, const string &s2, int i1, int i2)
  {
    if (i1 < 0 || i2 < 0)
      return 0;

    int p1 = f1(s1, s2, i1 - 1, i2 - 1);
    int p2 = f1(s1, s2, i1 - 1, i2);
    int p3 = f1(s1, s2, i1, i2 - 1);
    int p4 = (s1[i1] == s2[i2]) ? (p1 + 1) : 0;
    return max({p1, p2, p3, p4});
  }

  int f2(const string &s1, const string &s2, int len1, int len2)
  {
    if (len1 == 0 || len2 == 0)
      return 0;

    if (s1[len1 - 1] == s2[len2 - 1])
    {
      return f2(s1, s2, len1 - 1, len2 - 1) + 1;
    }
    else
    {
      return max(f2(s1, s2, len1 - 1, len2),
                 f2(s1, s2, len1, len2 - 1));
    }
  }

  int f3(const string &s1, const string &s2, int len1, int len2, vector<vector<int>> &dp)
  {
    if (len1 == 0 || len2 == 0)
    {
      return 0;
    }

    if (dp[len1][len2] != -1)
    {
      return dp[len1][len2];
    }

    int ans;
    if (s1[len1 - 1] == s2[len2 - 1])
    {
      ans = f3(s1, s2, len1 - 1, len2 - 1, dp) + 1;
    }
    else
    {
      ans = max(f3(s1, s2, len1 - 1, len2, dp),
                f3(s1, s2, len1, len2 - 1, dp));
    }

    dp[len1][len2] = ans;
    return ans;
  }

public:
  // 1. 暴力递归（下标）
  int longestCommonSubsequence1(string str1, string str2)
  {
    int n = str1.size(), m = str2.size();
    return f1(str1, str2, n - 1, m - 1);
  }

  // 2. 暴力递归（长度）
  int longestCommonSubsequence2(string str1, string str2)
  {
    int n = str1.size(), m = str2.size();
    return f2(str1, str2, n, m);
  }

  // 3. 记忆化搜索
  int longestCommonSubsequence3(string str1, string str2)
  {
    int n = str1.size(), m = str2.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, -1));
    return f3(str1, str2, n, m, dp);
  }

  // 4. 严格位置依赖的动态规划
  int longestCommonSubsequence4(string str1, string str2)
  {
    int n = str1.size(), m = str2.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    for (int len1 = 1; len1 <= n; len1++)
    {
      for (int len2 = 1; len2 <= m; len2++)
      {
        if (str1[len1 - 1] == str2[len2 - 1])
        {
          dp[len1][len2] = dp[len1 - 1][len2 - 1] + 1;
        }
        else
        {
          dp[len1][len2] = max(dp[len1 - 1][len2],
                               dp[len1][len2 - 1]);
        }
      }
    }

    return dp[n][m];
  }

  // 5. 严格位置依赖的动态规划 + 空间压缩（优化：让较长的串作为行）
  int longestCommonSubsequence5(string str1, string str2)
  {
    if (str1.size() < str2.size())
    {
      swap(str1, str2);
    }

    int n = str1.size(), m = str2.size();
    vector<int> dp(m + 1, 0);
    for (int len1 = 1; len1 <= n; len1++)
    {
      int leftUp = 0;
      for (int len2 = 1; len2 <= m; len2++)
      {
        int backup = dp[len2];
        if (str1[len1 - 1] == str2[len2 - 1])
        {
          dp[len2] = leftUp + 1;
        }
        else
        {
          dp[len2] = max(dp[len2 - 1], dp[len2]);
        }

        leftUp = backup;
      }
    }

    return dp[m];
  }
};