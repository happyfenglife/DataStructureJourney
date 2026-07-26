// 乘积最大子数组
// 给你一个整数数组 nums
// 请你找出数组中乘积最大的非空连续子数组
// 并返回该子数组所对应的乘积
// 测试链接 : https://leetcode.cn/problems/maximum-product-subarray/
#include <vector>
#include <algorithm>
using namespace std;

class Solution
{
public:
  int maxProduct(vector<int> &nums)
  {
    double ans{nums[0]}, minProd{nums[0]}, maxProd{nums[0]};
    double curmin, curmax;
    for (int i = 1; i < nums.size(); i++)
    {
      curmin = min({1.0 * nums[i], nums[i] * minProd, nums[i] * maxProd});
      curmax = max({1.0 * nums[i], nums[i] * minProd, nums[i] * maxProd});
      minProd = curmin;
      maxProd = curmax;
      ans = max(ans, curmax);
    }

    return static_cast<int>(ans);
  }
};