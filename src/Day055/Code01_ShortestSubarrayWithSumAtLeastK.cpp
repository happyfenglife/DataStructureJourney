// 和至少为K的最短子数组
// 给定一个数组arr，其中的值有可能正、负、0
// 给定一个正数k
// 返回累加和>=k的所有子数组中，最短的子数组长度
// 测试链接 : https://leetcode.cn/problems/shortest-subarray-with-sum-at-least-k/
#include <vector>
#include <array>
#include <limits>
using namespace std;

class Solution
{
public:
  static constexpr int MAXN = 100001;

  // sum[0] : 前0个数的前缀和
  // sum[i] : 前i个数的前缀和
  array<long long, MAXN> sum;

  array<int, MAXN> deque;

  int h, t;

  int shortestSubarray(vector<int> &nums, int k)
  {
    int n = static_cast<int>(nums.size());
    for (int i = 0; i < n; i++)
    {
      sum[i + 1] = sum[i] + nums[i];
    }

    h = t = 0;
    int ans = numeric_limits<int>::max();
    for (int i = 0; i <= n; i++)
    {
      // 前0个数前缀和
      // 前1个数前缀和
      // 前2个数前缀和
      // ...
      // 前n个数前缀和
      while (h != t && sum[i] - sum[deque[h]] >= k)
      {
        // 如果当前的前缀和 - 头前缀和，达标！
        ans = min(ans, i - deque[h++]);
      }

      // 前i个数前缀和，从尾部加入
      // 小 大
      while (h != t && sum[deque[t - 1]] >= sum[i])
      {
        --t;
      }

      deque[t++] = i;
    }

    return ans != numeric_limits<int>::max() ? ans : -1;
  }
};