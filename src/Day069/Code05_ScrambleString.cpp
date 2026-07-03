// 扰乱字符串
// 使用下面描述的算法可以扰乱字符串 s 得到字符串 t ：
// 步骤1 : 如果字符串的长度为 1 ，算法停止
// 步骤2 : 如果字符串的长度 > 1 ，执行下述步骤：
//        在一个随机下标处将字符串分割成两个非空的子字符串
//        已知字符串s，则可以将其分成两个子字符串x和y且满足s=x+y
//        可以决定是要 交换两个子字符串 还是要 保持这两个子字符串的顺序不变
//        即s可能是 s = x + y 或者 s = y + x
//        在x和y这两个子字符串上继续从步骤1开始递归执行此算法
// 给你两个 长度相等 的字符串 s1 和 s2，判断 s2 是否是 s1 的扰乱字符串
// 如果是，返回true ；否则，返回false
// 测试链接 : https://leetcode.cn/problems/scramble-string/
#include <vector>
#include <string>
using namespace std;

class Solution
{
private:
  bool f1(string &s1, int l1, int r1, string &s2, int l2, int r2)
  {
    if (l1 == r1)
    {
      return s1[l1] == s2[l2];
    }

    for (int i = l1, j = l2; i < r1; i++, j++)
    {
      if (f1(s1, l1, i, s2, l2, j) &&
          f1(s1, i + 1, r1, s2, i + 1, r2))
      {
        return true;
      }
    }

    for (int i = l1, j = r2; i < r1; i++, j--)
    {
      if (f1(s1, l1, i, s2, j, r2) &&
          f1(s1, i + 1, r1, s2, l2, j - 1))
      {
        return true;
      }
    }

    return false;
  }

  bool f2(string &s1, string &s2, int l1, int l2, int len)
  {
    if (len == 1)
    {
      return s1[l1] == s2[l2];
    }

    for (int k = 1; k < len; k++)
    {
      if (f2(s1, s2, l1, l2, k) && f2(s1, s2, l1 + k, l2 + k, len - k))
      {
        return true;
      }
    }

    for (int k = 1, i = l1 + k, j = l2 + len - k; k < len; k++, i++, j--)
    {
      if (f2(s1, s2, l1, j, k) &&
          f2(s1, s2, i, l2, len - k))
      {
        return true;
      }
    }

    return false;
  }

  bool f3(string &s1, string &s2, int l1, int l2, int len, vector<vector<vector<int>>> &memo)
  {
    if (len == 1)
    {
      return s1[l1] == s2[l2];
    }

    if (memo[l1][l2][len] != 0)
    {
      return memo[l1][l2][len] == 1;
    }

    bool ans = false;
    for (int k = 1; k < len; k++)
    {
      if (f3(s1, s2, l1, l2, k, memo) && f3(s1, s2, l1 + k, l2 + k, len - k, memo))
      {
        ans = true;
        break;
      }
    }

    if (!ans)
    {
      for (int k = 1, i = l1 + k, j = l2 + len - k; k < len; k++, i++, j--)
      {
        if (f3(s1, s2, l1, j, k, memo) &&
            f3(s1, s2, i, l2, len - k, memo))
        {
          ans = true;
          break;
        }
      }
    }

    memo[l1][l2][len] = ans ? 1 : -1;
    return ans;
  }

public:
  bool isScramble1(string s1, string s2)
  {
    int n = s1.size();
    return f1(s1, 0, n - 1, s2, 0, n - 1);
  }

  bool isScramble2(string s1, string s2)
  {
    int n = s1.size();
    return f2(s1, s2, 0, 0, n);
  }

  bool isScramble3(string s1, string s2)
  {
    int n = s1.size();
    vector<vector<vector<int>>> memo(
        n, vector<vector<int>>(n, vector<int>(n + 1, 0)));
    return f3(s1, s2, 0, 0, n, memo);
  }

  bool isScramble4(string s1, string s2)
  {
    int n = s1.size();
    vector<vector<vector<bool>>> dp(
        n, vector<vector<bool>>(n, vector<bool>(n + 1, false)));

    for (int l1 = 0; l1 < n; l1++)
    {
      for (int l2 = 0; l2 < n; l2++)
      {
        dp[l1][l2][1] = (s1[l1] == s2[l2]);
      }
    }

    for (int len = 2; len <= n; len++)
    {
      for (int l1 = 0; l1 <= n - len; l1++)
      {
        for (int l2 = 0; l2 <= n - len; l2++)
        {
          for (int k = 1; k < len; k++)
          {
            if (dp[l1][l2][k] && dp[l1 + k][l2 + k][len - k])
            {
              dp[l1][l2][len] = true;
              break;
            }
          }

          if (!dp[l1][l2][len])
          {
            for (int k = 1, i = l1 + k, j = l2 + len - k; k < len; k++, i++, j--)
            {
              if (dp[l1][j][k] && dp[i][l2][len - k])
              {
                dp[l1][l2][len] = true;
                break;
              }
            }
          }
        }
      }
    }

    return dp[0][0][n];
  }
};