// 最长递增子序列和最长不下降子序列
// 给定一个整数数组nums
// 找到其中最长严格递增子序列长度、最长不下降子序列长度
// 测试链接 : https://leetcode.cn/problems/longest-increasing-subsequence/
#include <vector>
#include <algorithm>
using namespace std;

class Solution
{
public:
  // 普通解法的动态规划
  // 时间复杂度O(n^2)，数组稍大就会超时
  int lengthOfLIS1(vector<int> &nums)
  {
    int n = static_cast<int>(nums.size());
    vector<int> dp(n);
    int ans{};
    for (int i = 0; i < n; i++)
    {
      dp[i] = 1;
      for (int j = 0; j < i; j++)
      {
        if (nums[j] < nums[i])
        {
          dp[i] = max(dp[i], dp[j] + 1);
        }
      }

      ans = max(ans, dp[i]);
    }

    return ans;
  }

  // 最优解
  // 时间复杂度O(n * logn)
  int lengthOfLIS2(vector<int> &nums)
  {
    int n = static_cast<int>(nums.size());
    vector<int> ends(n);
    // len表示ends数组目前的有效区长度
    // ends[0...len-1]是有效区，有效区内的数字一定严格升序
    int len{};
    for (int i = 0; i < n; i++)
    {
      // "最长递增子序列"使用如下二分搜索 :
      // ends[0...len-1]是严格升序的，找到>=num的最左位置
      auto it = lower_bound(ends.begin(), ends.begin() + len, nums[i]);
      // 如果求最长不下降子序列，那么使用如下的二分搜索 :
      // ends[0...len-1]是不降序的
      // 在其中找到>num的最左位置
      // auto it = upper_bound(ends.begin(), ends.begin() + len, nums[i]);
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