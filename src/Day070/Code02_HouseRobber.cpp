// 数组中不能选相邻元素的最大累加和
// 给定一个数组，可以随意选择数字
// 但是不能选择相邻的数字，返回能得到的最大累加和
// 测试链接 : https://leetcode.cn/problems/house-robber/
#include <vector>
using namespace std;

class Solution
{
public:
  // 动态规划
  int rob1(vector<int> &nums)
  {
    int n = static_cast<int>(nums.size());
    if (n == 1)
    {
      return nums[0];
    }

    if (n == 2)
    {
      return max(nums[0], nums[1]);
    }

    // dp[i] : nums[0...i]范围上可以随意选择数字，但是不能选相邻数，能得到的最大累加和
    vector<int> dp(n);
    dp[0] = nums[0];
    dp[1] = max(nums[0], nums[1]);
    for (int i = 2; i < n; i++)
    {
      dp[i] = max(dp[i - 1], dp[i - 2] + nums[i]);
    }

    return dp[n - 1];
  }

  // 空间压缩
  int rob2(vector<int> &nums)
  {
    int n = static_cast<int>(nums.size());
    if (n == 1)
    {
      return nums[0];
    }

    if (n == 2)
    {
      return max(nums[0], nums[1]);
    }

    int prepre = nums[0];
    int pre = max(nums[0], nums[1]);
    for (int i = 2, cur; i < n; i++)
    {
      cur = max(pre, nums[i] + prepre);
      prepre = pre;
      pre = cur;
    }
    
    return pre;
  }
};