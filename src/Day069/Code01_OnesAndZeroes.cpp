// 一和零(多维费用背包)
// 给你一个二进制字符串数组 strs 和两个整数 m 和 n
// 请你找出并返回 strs 的最大子集的长度
// 该子集中 最多 有 m 个 0 和 n 个 1
// 如果 x 的所有元素也是 y 的元素，集合 x 是集合 y 的 子集
// 测试链接 : https://leetcode.cn/problems/ones-and-zeroes/
#include <vector>
#include <string>
using namespace std;

class Solution
{
private:
  pair<int, int> countZerosOnes(const string &str)
  {
    int zeros = 0, ones = 0;
    for (char c : str)
    {
      if (c == '0')
      {
        ++zeros;
      }
      else
      {
        ++ones;
      }
    }

    return {zeros, ones};
  }

  int dfs1(const vector<string> &strs, int idx, int z, int o)
  {
    if (idx == strs.size())
    {
      return 0;
    }

    int p1 = dfs1(strs, idx + 1, z, o);
    int p2 = 0;
    auto [zeros, ones] = countZerosOnes(strs[idx]);
    if (zeros <= z && ones <= o)
    {
      p2 = 1 + dfs1(strs, idx + 1, z - zeros, o - ones);
    }

    return max(p1, p2);
  }

  int dfs2(const vector<string> &strs, int idx, int z, int o,
           vector<vector<vector<int>>> &memo)
  {
    if (idx == strs.size())
    {
      return 0;
    }

    if (memo[idx][z][o] != -1)
    {
      return memo[idx][z][o];
    }

    int p1 = dfs2(strs, idx + 1, z, o, memo);
    int p2 = 0;
    auto [zeros, ones] = countZerosOnes(strs[idx]);
    if (zeros <= z && ones <= o)
    {
      p2 = 1 + dfs2(strs, idx + 1, z - zeros, o - ones, memo);
    }
    int ans = max(p1, p2);
    memo[idx][z][o] = ans;

    return ans;
  }

public:
  // ========== 方法1：暴力递归接口 ==========
  int findMaxForm1(vector<string> &strs, int m, int n)
  {
    return dfs1(strs, 0, m, n);
  }

  // ========== 方法2：记忆化搜索 ==========
  int findMaxForm2(const vector<string> &strs, int m, int n)
  {
    int len = strs.size();
    vector<vector<vector<int>>> memo(len, vector<vector<int>>(m + 1, vector<int>(n + 1, -1)));

    return dfs2(strs, 0, m, n, memo);
  }

  // ========== 方法3：三维DP（从后往前递推） ==========
  int findMaxForm3(const vector<string> &strs, int m, int n)
  {
    int len = strs.size();
    vector<vector<vector<int>>> dp(
        len + 1, vector<vector<int>>(m + 1, vector<int>(n + 1, 0)));

    for (int i = len - 1; i >= 0; i--)
    {
      auto [zeros, ones] = countZerosOnes(strs[i]);
      for (int z = 0; z <= m; z++)
      {
        for (int o = 0; o <= n; o++)
        {
          int p1 = dp[i + 1][z][o];
          int p2 = 0;
          if (zeros <= z && ones <= o)
          {
            p2 = 1 + dp[i + 1][z - zeros][o - ones];
          }

          dp[i][z][o] = max(p1, p2);
        }
      }
    }

    return dp[0][m][n];
  }

  // ========== 方法4：空间压缩（二维DP，推荐） ==========
  int findMaxForm4(const vector<string> &strs, int m, int n)
  {
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    for (const string &s : strs)
    {
      auto [zeros, ones] = countZerosOnes(s);

      for (int z = m; z >= zeros; z--)
      {
        for (int o = n; o >= ones; o--)
        {
          dp[z][o] = max(dp[z][o], 1 + dp[z - zeros][o - ones]);
        }
      }
    }

    return dp[m][n];
  }
};