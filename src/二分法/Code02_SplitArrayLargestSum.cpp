// 分割数组的最大值(画匠问题)
// 给定一个非负整数数组 nums 和一个整数 m
// 你需要将这个数组分成 m 个非空的连续子数组。
// 设计一个算法使得这 m 个子数组各自和的最大值最小。
// 测试链接 : https://leetcode.cn/problems/split-array-largest-sum/
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

class Solution
{
public:
  int splitArray(vector<int> &nums, int k)
  {
    ll sum = accumulate(nums.begin(), nums.end(), 0);
    ll ans = 0;
    for (ll l = 0, r = sum, m, need; l <= r;)
    {
      m = l + ((r - l) >> 1);
      // 必须让数组每一部分的累加和 <= m，请问至少划分成几个部分才够!
      need = f(nums, m);
      if (need <= k)
      {
        ans = m;
        r = m - 1;
      }
      else
      {
        l = m + 1;
      }
    }

    return ans;
  }

  int f(vector<int> &v, ll limit)
  {
    int parts = 1;
    int sum = 0;
    for (int num : v)
    {
      if (num > limit)
      {
        return INT_MAX;
      }

      if (sum + num > limit)
      {
        parts++;
        sum = num;
      }
      else
      {
        sum += num;
      }
    }

    return parts;
  }
};