// 使数组K递增的最少操作次数
// 给你一个下标从0开始包含n个正整数的数组arr，和一个正整数k
// 如果对于每个满足 k <= i <= n-1 的下标 i
// 都有 arr[i-k] <= arr[i] ，那么称 arr 是K递增的
// 每一次操作中，你可以选择一个下标i并将arr[i]改成任意正整数
// 请你返回对于给定的 k ，使数组变成K递增的最少操作次数
// 测试链接 : https://leetcode.cn/problems/minimum-operations-to-make-the-array-k-increasing/
#include <vector>
#include <algorithm>
using namespace std;

class Solution
{
public:
  int kIncreasing(vector<int> &arr, int k)
  {
    int n = static_cast<int>(arr.size());
    vector<int> nums(n);

    int ans{};
    for (int i = 0, sz; i < k; i++)
    {
      sz = 0;
      // 把每一组的数字放入容器
      for (int j = i; j < n; j += k)
      {
        nums[sz++] = arr[j];
      }

      ans += sz - lenOfNoDecreasing(nums, sz);
    }

    return ans;
  }

  // nums[0...size-1]中的最长不下降子序列长度
  int lenOfNoDecreasing(vector<int> &nums, int sz)
  {
    int len{};
    vector<int> ends(sz);
    for (int i = 0; i < sz; i++)
    {
      auto it = upper_bound(ends.begin(),
                            ends.begin() + len, nums[i]);
      if (it == ends.begin() + len)
      {
        ends[len++] = nums[i];
      }
      else
      {
        *it = nums[i];
      }
    }

    return len;
  }
};