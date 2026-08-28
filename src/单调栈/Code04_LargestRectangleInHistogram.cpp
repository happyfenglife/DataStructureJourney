// 柱状图中最大的矩形
// 给定 n 个非负整数，用来表示柱状图中各个柱子的高度
// 每个柱子彼此相邻，且宽度为 1 。求在该柱状图中，能够勾勒出来的矩形的最大面积
// 测试链接：https://leetcode.cn/problems/largest-rectangle-in-histogram
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
  static constexpr int MAXN = 1E5 + 1;

  int st[MAXN];

  int r;

  int largestRectangleArea(vector<int> &v)
  {
    int n = v.size();
    r = 0;
    int ans{}, cur, l;
    for (int i = 0; i < n; i++)
    {
      while (r > 0 && v[st[r - 1]] >= v[i])
      {
        cur = st[--r];
        l = !r ? -1 : st[r - 1];
        ans = max(ans, v[cur] * (i - l - 1));
      }

      st[r++] = i;
    }

    while (r > 0)
    {
      cur = st[--r];
      l = !r ? -1 : st[r - 1];
      ans = max(ans, v[cur] * (n - l - 1));
    }

    return ans;
  }
};