// 滑动窗口最大值（单调队列经典用法模版）
// 给你一个整数数组 nums，有一个大小为 k 的滑动窗口从数组的最左侧移动到数组的最右侧
// 你只可以看到在滑动窗口内的 k 个数字。滑动窗口每次只向右移动一位。
// 返回 滑动窗口中的最大值 。
// 测试链接 : https://leetcode.cn/problems/sliding-window-maximum/
#include <vector>
using namespace std;

class Solution
{
public:
  vector<int> maxSlidingWindow(vector<int> &nums, int k)
  {
    int h{}, t{};
    int n = static_cast<int>(nums.size());
    vector<int> deque(n);

    // 先形成长度为k-1的窗口
    for (int i = 0; i < k - 1; i++)
    {
      // 大 -> 小
      while (h < t && nums[deque[t - 1]] <= nums[i])
      {
        --t;
      }

      deque[t++] = i;
    }

    int m = n - k + 1;
    vector<int> ans(m);
    // 当前窗口k-1长度
    for (int l = 0, r = k - 1; l < m; l++, r++)
    {
      // 少一个，要让r位置的数进来
      while (h < t && nums[deque[t - 1]] <= nums[r])
      {
        --t;
      }

      deque[t++] = r;
      // 收集答案
      ans[l] = nums[deque[h]];
      if (deque[h] == l)
      {
        h++;
      }
    }

    return ans;
  }
};