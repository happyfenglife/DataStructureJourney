// 最大人工岛
// 给你一个大小为 n * n 二进制矩阵 grid 。最多 只能将一格 0 变成 1 。
// 返回执行此操作后，grid 中最大的岛屿面积是多少？
// 岛屿 由一组上、下、左、右四个方向相连的 1 形成
// 测试链接 : https://leetcode.cn/problems/making-a-large-island/
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
  int largestIsland(vector<vector<int>> &g)
  {
    int n = g.size(), m = g[0].size();
    int id{2};
    for (int i = 0; i < n; i++)
    {
      for (int j = 0; j < m; j++)
      {
        if (g[i][j] == 1)
        {
          dfs(g, n, m, i, j, id++);
        }
      }
    }

    vector<int> sizes(id);
    int ans{};
    for (int i = 0; i < n; i++)
    {
      for (int j = 0; j < m; j++)
      {
        if (g[i][j] > 1)
        {
          ans = max(ans, ++sizes[g[i][j]]);
        }
      }
    }

    // 讨论所有的0，变成1，能带来的最大岛的大小
    vector<bool> visited(id);
    int up, down, left, right, merge;
    for (int i = 0; i < n; i++)
    {
      for (int j = 0; j < m; j++)
      {
        if (g[i][j] == 0)
        {
          up = i > 0 ? g[i - 1][j] : 0;
          down = i + 1 < n ? g[i + 1][j] : 0;
          left = j > 0 ? g[i][j - 1] : 0;
          right = j + 1 < m ? g[i][j + 1] : 0;
          visited[up] = true;
          merge = 1 + sizes[up];
          if (!visited[down])
          {
            visited[down] = true;
            merge += sizes[down];
          }
          if (!visited[left])
          {
            visited[left] = true;
            merge += sizes[left];
          }
          if (!visited[right])
          {
            visited[right] = true;
            merge += sizes[right];
          }

          ans = max(ans, merge);
          visited[up] = false;
          visited[down] = false;
          visited[left] = false;
          visited[right] = false;
        }
      }
    }

    return ans;
  }

  void dfs(vector<vector<int>> &g, int n, int m, int i, int j, int id)
  {
    if (i < 0 || i == n ||
        j < 0 || j == m || g[i][j] != 1)
    {
      return;
    }

    g[i][j] = id;
    dfs(g, n, m, i - 1, j, id);
    dfs(g, n, m, i + 1, j, id);
    dfs(g, n, m, i, j - 1, id);
    dfs(g, n, m, i, j + 1, id);
  }
};