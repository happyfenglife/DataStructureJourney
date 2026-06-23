// 矩阵中的最长递增路径
// 给定一个 m x n 整数矩阵 matrix ，找出其中 最长递增路径 的长度
// 对于每个单元格，你可以往上，下，左，右四个方向移动
// 你 不能 在 对角线 方向上移动或移动到 边界外（即不允许环绕）
// 测试链接 : https://leetcode.cn/problems/longest-increasing-path-in-a-matrix/
#include <vector>
using namespace std;

class Solution
{
private:
  int dfs1(const vector<vector<int>> &grid, int i, int j)
  {
    int next = 0;
    int n = grid.size(), m = grid[0].size();
    if (i > 0 && grid[i][j] < grid[i - 1][j])
      next = max(next, dfs1(grid, i - 1, j));

    if (i + 1 < n && grid[i][j] < grid[i + 1][j])
      next = max(next, dfs1(grid, i + 1, j));

    if (j > 0 && grid[i][j] < grid[i][j - 1])
      next = max(next, dfs1(grid, i, j - 1));

    if (j + 1 < m && grid[i][j] < grid[i][j + 1])
      next = max(next, dfs1(grid, i, j + 1));

    return next + 1;
  }

  int dfs2(const vector<vector<int>> &grid, int i, int j, vector<vector<int>> &dp)
  {
    if (dp[i][j] != 0)
    {
      return dp[i][j];
    }

    int next = 0;
    int n = grid.size(), m = grid[0].size();

    if (i > 0 && grid[i][j] < grid[i - 1][j])
      next = max(next, dfs2(grid, i - 1, j, dp));

    if (i + 1 < n && grid[i][j] < grid[i + 1][j])
      next = max(next, dfs2(grid, i + 1, j, dp));

    if (j > 0 && grid[i][j] < grid[i][j - 1])
      next = max(next, dfs2(grid, i, j - 1, dp));

    if (j + 1 < m && grid[i][j] < grid[i][j + 1])
      next = max(next, dfs2(grid, i, j + 1, dp));

    dp[i][j] = next + 1;
    return next + 1;
  }

public:
  // 1. 暴力递归
  int longestIncreasingPath1(vector<vector<int>> &grid)
  {
    int n = grid.size(), m = grid[0].size();
    int ans = 0;
    for (int i = 0; i < n; i++)
      for (int j = 0; j < m; j++)
        ans = max(ans, dfs1(grid, i, j));

    return ans;
  }

  // 2. 记忆化搜索
  int longestIncreasingPath2(vector<vector<int>> &grid)
  {
    int n = grid.size(), m = grid[0].size();
    int ans = 0;
    vector<vector<int>> dp(n, vector<int>(m, 0));
    for (int i = 0; i < n; i++)
      for (int j = 0; j < m; j++)
        ans = max(ans, dfs2(grid, i, j, dp));

    return ans;
  }
};