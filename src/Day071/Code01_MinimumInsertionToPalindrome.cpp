// 让字符串成为回文串的最少插入次数
// 给你一个字符串 s
// 每一次操作你都可以在字符串的任意位置插入任意字符
// 请你返回让 s 成为回文串的最少操作次数
// 测试链接 : https://leetcode.cn/problems/minimum-insertion-steps-to-make-a-string-palindrome/
#include <vector>
#include <string>
using namespace std;

class Solution
{
public:
  // 暴力尝试
  int minInsertions1(const string &str)
  {
    int n = static_cast<int>(str.size());
    if (n < 2)
    {
      return 0;
    }

    return f1(str, 0, n - 1);
  }

  // 记忆化搜索
  int minInsertions2(const string &str)
  {
    int n = static_cast<int>(str.size());
    if (n < 2)
    {
      return 0;
    }

    vector<vector<int>> dp(n, vector<int>(n, -1));
    return f2(str, 0, n - 1, dp);
  }

  // 严格位置依赖的动态规划
  int minInsertions3(const string &str)
  {
    int n = static_cast<int>(str.size());
    if (n < 2)
    {
      return 0;
    }

    vector<vector<int>> dp(n, vector<int>(n, 0));
    for (int l = 0; l < n - 1; l++)
    {
      dp[l][l + 1] = str[l] == str[l + 1] ? 0 : 1;
    }

    for (int l = n - 3; l >= 0; l--)
    {
      for (int r = l + 2; r < n; r++)
      {
        if (str[l] == str[r])
        {
          dp[l][r] = dp[l + 1][r - 1];
        }
        else
        {
          dp[l][r] = min(dp[l + 1][r], dp[l][r - 1]) + 1;
        }
      }
    }

    return dp[0][n - 1];
  }

  // 空间压缩
  int minInsertions4(const string &str)
  {
    int n = static_cast<int>(str.size());
    if (n < 2)
    {
      return 0;
    }

    vector<int> dp(n, 0);
    dp[n - 1] = str[n - 2] == str[n - 1] ? 0 : 1;

    for (int l = n - 3, leftDown, backUp; l >= 0; l--)
    {
      leftDown = dp[l + 1];
      dp[l + 1] = str[l] == str[l + 1] ? 0 : 1;
      for (int r = l + 2; r < n; r++)
      {
        backUp = dp[r];
        if (str[l] == str[r])
        {
          dp[r] = leftDown;
        }
        else
        {
          dp[r] = min(dp[r], dp[r - 1]) + 1;
        }

        leftDown = backUp;
      }
    }

    return dp[n - 1];
  }

private:
  // s[l....r]这个范围上的字符串，整体都变成回文串
  // 返回至少插入几个字符（暴力递归）
  int f1(const string &s, int l, int r)
  {
    if (l == r)
    {
      return 0;
    }

    if (l == r - 1)
    {
      return s[l] == s[r] ? 0 : 1;
    }

    if (s[l] == s[r])
    {
      return f1(s, l + 1, r - 1);
    }
    else
    {
      return min(f1(s, l + 1, r), f1(s, l, r - 1)) + 1;
    }
  }

  int f2(const string &s, int l, int r, vector<vector<int>> &dp)
  {
    if (dp[l][r] != -1)
    {
      return dp[l][r];
    }

    int ans = 0;
    if (l == r)
    {
      ans = 0;
    }
    else if (l == r - 1)
    {
      ans = s[l] == s[r] ? 0 : 1;
    }
    else
    {
      if (s[l] == s[r])
      {
        ans = f2(s, l + 1, r - 1, dp);
      }
      else
      {
        ans = min(f2(s, l + 1, r, dp), f2(s, l, r - 1, dp)) + 1;
      }
    }

    dp[l][r] = ans;
    return ans;
  }
};