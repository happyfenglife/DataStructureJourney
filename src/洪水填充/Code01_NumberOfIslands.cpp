// 岛屿数量
// 给你一个由 '1'（陆地）和 '0'（水）组成的的二维网格，请你计算网格中岛屿的数量
// 岛屿总是被水包围，并且每座岛屿只能由水平方向和/或竖直方向上相邻的陆地连接形成
// 此外，你可以假设该网格的四条边均被水包围
// 测试链接 : https://leetcode.cn/problems/number-of-islands/
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
  // 洪水填充的做法
  // board : n * m
  // O(n*m)最优解！
  int numIslands(vector<vector<char>> &grid)
  {
    int n = grid.size(), m = grid[0].size();
    int islands{};
    for (int i = 0; i < n; i++)
    {
      for (int j = 0; j < m; j++)
      {
        if (grid[i][j] == '1')
        {
          islands++;
          dfs(grid, n, m, i, j);
        }
      }
    }

    return islands;
  }

  void dfs(vector<vector<char>> &g, int n, int m, int i, int j)
  {
    if (i < 0 || i == n ||
        j < 0 || j == m || g[i][j] == '0')
    {
      return;
    }

    g[i][j] = '0';
    dfs(g, n, m, i - 1, j);
    dfs(g, n, m, i + 1, j);
    dfs(g, n, m, i, j - 1);
    dfs(g, n, m, i, j + 1);
  }
};