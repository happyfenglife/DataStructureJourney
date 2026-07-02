// 矩阵中和能被 K 整除的路径
// 给一个下标从0开始的 n * m 整数矩阵 grid 和一个整数 k
// 从起点(0,0)出发，每步只能往下或者往右，你想要到达终点(m-1, n-1)
// 请你返回路径和能被 k 整除的路径数目
// 答案对 1000000007 取模
// 测试链接 : https://leetcode.cn/problems/paths-in-matrix-whose-sum-is-divisible-by-k/
#include <vector>
using namespace std;

class Solution
{
private:
  static constexpr int MOD = 1E9 + 7;

  // 当前来到(i,j)位置，最终一定要走到右下角(n-1,m-1)
  // 从(i,j)出发，最终一定要走到右下角(n-1,m-1)，有多少条路径，累加和%k的余数是r
  int f1(vector<vector<int>> &grid, int n, int m, int k, int i, int j, int r)
  {
    if (i == n - 1 && j == m - 1)
    {
      return grid[i][j] % k == r ? 1 : 0;
    }

    int need = (k + r - (grid[i][j] % k)) % k;
    int ans = 0;
    if (i + 1 < n)
    {
      ans = f1(grid, n, m, k, i + 1, j, need);
    }

    if (j + 1 < m)
    {
      ans = (ans + f1(grid, n, m, k, i, j + 1, need)) % MOD;
    }

    return ans;
  }

  int f2(vector<vector<int>> &grid, int n, int m, int k, int i, int j, int r, vector<vector<vector<int>>> &memo)
  {
    if (i == n - 1 && j == m - 1)
    {
      return grid[i][j] % k == r ? 1 : 0;
    }

    if (memo[i][j][r] != -1)
    {
      return memo[i][j][r];
    }

    int need = (r + k - (grid[i][j] % k)) % k;
    int ans = 0;
    if (i + 1 < n)
    {
      ans = f2(grid, n, m, k, i + 1, j, need, memo);
    }

    if (j + 1 < m)
    {
      ans = (ans + f2(grid, n, m, k, i, j + 1, need, memo)) % MOD;
    }

    memo[i][j][r] = ans;
    return ans;
  }

public:
  int numberOfPaths1(vector<vector<int>> &grid, int k)
  {
    int n = grid.size(), m = grid[0].size();
    return f1(grid, n, m, k, 0, 0, 0);
  }

  int numberOfPaths2(vector<vector<int>> &grid, int k)
  {
    int n = grid.size(), m = grid[0].size();
    vector<vector<vector<int>>> memo(n, vector<vector<int>>(m, vector<int>(k, -1)));
    return f2(grid, n, m, k, 0, 0, 0, memo);
  }

  int numberOfPaths3(vector<vector<int>> &grid, int k)
  {
    int n = grid.size(), m = grid[0].size();
    vector<vector<vector<int>>> dp(n, vector<vector<int>>(m, vector<int>(k, 0)));
    dp[n - 1][m - 1][grid[n - 1][m - 1] % k] = 1;

    for (int i = n - 2; i >= 0; i--)
    {
      for (int r = 0; r < k; r++)
      {
        dp[i][m - 1][r] = dp[i + 1][m - 1][(k + r - grid[i][m - 1] % k) % k];
      }
    }

    for (int j = m - 2; j >= 0; j--)
    {
      for (int r = 0; r < k; r++)
      {
        dp[n - 1][j][r] = dp[n - 1][j + 1][(k + r - grid[n - 1][j] % k) % k];
      }
    }

    for (int i = n - 2, need; i >= 0; i--)
    {
      for (int j = m - 2; j >= 0; j--)
      {
        for (int r = 0; r < k; r++)
        {
          need = (k + r - grid[i][j] % k) % k;
          dp[i][j][r] = dp[i + 1][j][need];
          dp[i][j][r] = (dp[i][j][r] + dp[i][j + 1][need]) % MOD;
        }
      }
    }

    return dp[0][0][0];
  }
};