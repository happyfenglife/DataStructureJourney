// 最大矩形
// 给定一个仅包含 0 和 1 、大小为 rows * cols 的二维二进制矩阵
// 找出只包含 1 的最大矩形，并返回其面积
// 测试链接：https://leetcode.cn/problems/maximal-rectangle/
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
  static constexpr int MAXN = 201;

  int h[MAXN];

  int st[MAXN];

  int r;

  int maximalRectangle(vector<vector<char>> &matrix)
  {
    int n = matrix.size(), m = matrix[0].size();
    fill(begin(h), begin(h) + m, 0);
    int ans{};
    for (int i = 0; i < n; i++)
    {
      // 来到i行，长方形一定要以i行做底！
      // 加工高度数组(压缩数组)
      for (int j = 0; j < m; j++)
      {
        h[j] = matrix[i][j] == '0' ? 0 : h[j] + 1;
      }

      ans = max(ans, largestRectangleArea(m));
    }

    return ans;
  }

  int largestRectangleArea(int m)
  {
    r = 0;
    int ans{}, cur, l;
    for (int i = 0; i < m; i++)
    {
      while (r > 0 && h[st[r - 1]] >= h[i])
      {
        cur = st[--r];
        l = !r ? -1 : st[r - 1];
        ans = max(ans, h[cur] * (i - l - 1));
      }

      st[r++] = i;
    }

    while (r > 0)
    {
      cur = st[--r];
      l = !r ? -1 : st[r - 1];
      ans = max(ans, h[cur] * (m - l - 1));
    }

    return ans;
  }
};