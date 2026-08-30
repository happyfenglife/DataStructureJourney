// 最大宽度坡
// 给定一个整数数组 A，坡是元组 (i, j)，其中  i < j 且 A[i] <= A[j]
// 这样的坡的宽度为 j - i，找出 A 中的坡的最大宽度，如果不存在，返回 0
// 测试链接 : https://leetcode.cn/problems/maximum-width-ramp/
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
  static constexpr int MAXN = 50001;

  int st[MAXN];

  int r;

  int maxWidthRamp(vector<int> &nums)
  {
    // 令r=1相当于0位置进栈了
    // stack[0] = 0，然后栈的大小变成1
    r = 1;
    int n = nums.size();
    for (int i = 1; i < n; i++)
    {
      if (nums[st[r - 1]] > nums[i])
      {
        st[r++] = i;
      }
    }

    int ans{};
    for (int j = n - 1; j >= 0; j--)
    {
      while (r > 0 && nums[st[r - 1]] <= nums[j])
      {
        ans = max(ans, j - st[--r]);
      }
    }

    return ans;
  }
};