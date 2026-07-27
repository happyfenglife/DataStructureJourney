// 魔法卷轴
// 给定一个数组nums，其中可能有正、负、0
// 每个魔法卷轴可以把nums中连续的一段全变成0
// 你希望数组整体的累加和尽可能大
// 卷轴使不使用、使用多少随意，但一共只有2个魔法卷轴
// 请返回数组尽可能大的累加和
// 对数器验证
#include <iostream>
#include <vector>
#include <limits>
#include <numeric>
#include <algorithm>
#include <random>
#include <chrono>
using namespace std;

int mustOneScroll(vector<int> &nums, int l, int r)
{
  int ans = numeric_limits<int>::min();
  // l...r范围上包含a...b范围
  // 如果a...b范围上的数字都变成0
  // 返回剩下数字的累加和
  // 所以枚举所有可能的a...b范围
  // 相当暴力，但是正确
  for (int a = l; a <= r; a++)
  {
    for (int b = a; b <= r; b++)
    {
      // l...a...b...r
      int curAns{};
      for (int i = l; i < a; i++)
      {
        curAns += nums[i];
      }

      for (int i = b + 1; i <= r; i++)
      {
        curAns += nums[i];
      }

      ans = max(ans, curAns);
    }
  }

  return ans;
}

// 暴力方法
int maxSum1(vector<int> &nums)
{
  if (nums.empty())
  {
    return 0;
  }

  int p1 = accumulate(nums.begin(),
                      nums.end(), 0);
  int n = static_cast<int>(nums.size());
  int p2 = mustOneScroll(nums, 0, n - 1);
  int p3 = numeric_limits<int>::min();
  for (int i = 1; i < n; i++)
  {
    p3 = max(p3, mustOneScroll(nums, 0, i - 1) + mustOneScroll(nums, i, n - 1));
  }

  return max({p1, p2, p3});
}

// 正式方法
// 时间复杂度O(n)
int maxSum2(vector<int> &nums)
{
  if (nums.empty())
  {
    return 0;
  }

  // 情况1 : 完全不使用卷轴
  int p1 = accumulate(nums.begin(),
                      nums.end(), 0);
  int n = static_cast<int>(nums.size());
  // prefix[i] : 0~i范围上一定要用1次卷轴的情况下，0~i范围上整体最大累加和多少
  vector<int> prefix(n, 0);
  // 每一步的前缀和
  int sum{nums[0]};
  // maxPresum : 之前所有前缀和的最大值
  int maxPreSum{max(0, nums[0])};
  for (int i = 1; i < n; i++)
  {
    prefix[i] = max(prefix[i - 1] + nums[i], maxPreSum);
    sum += nums[i];
    maxPreSum = max(maxPreSum, sum);
  }

  // 情况二 : 必须用1次卷轴
  int p2{prefix[n - 1]};
  // suffix[i] : i~n-1范围上一定要用1次卷轴的情况下，i~n-1范围上整体最大累加和多少
  vector<int> suffix(n, 0);
  sum = nums[n - 1];
  maxPreSum = max(0, sum);
  for (int i = n - 2; i >= 0; i--)
  {
    suffix[i] = max(nums[i] + suffix[i + 1], maxPreSum);
    sum += nums[i];
    maxPreSum = max(maxPreSum, sum);
  }

  // 情况二 : 必须用2次卷轴
  int p3 = numeric_limits<int>::min();
  for (int i = 1; i < n; i++)
  {
    // 枚举所有的划分点i
    // 0~i-1 左
    // i~n-1 右
    p3 = max(p3, prefix[i - 1] + suffix[i]);
  }

  return max({p1, p2, p3});
}

// 为了测试
vector<int> randomArray(int n, int v)
{
  static mt19937 gen((unsigned)chrono::high_resolution_clock::now().time_since_epoch().count());
  vector<int> ans(n);
  if (n <= 0)
    return ans;

  uniform_int_distribution<int> dist(-v, v);
  for (int i = 0; i < n; i++)
  {
    ans[i] = dist(gen);
  }

  return ans;
}

// 为了测试
int main()
{
  int n = 50;
  int v = 100;
  int testTime = 10000;
  cout << "测试开始" << '\n';
  static std::mt19937 gen((unsigned)chrono::high_resolution_clock::now().time_since_epoch().count());
  uniform_int_distribution<int> lenDist(0, max(0, n - 1));
  for (int i = 0; i < testTime; i++)
  {
    int len = lenDist(gen);
    vector<int> nums = randomArray(len, v);
    int ans1 = maxSum1(nums);
    int ans2 = maxSum2(nums);
    if (ans1 != ans2)
    {
      cout << "出错了!" << '\n';
      // 可打印出错的数组以便调试
      cout << "len=" << len << " ans1=" << ans1 << " ans2=" << ans2 << '\n';
      cout << "nums: ";
      for (int x : nums)
        cout << x << " ";
      cout << '\n';
      return 0;
    }
  }

  cout << "测试结束" << '\n';
  return 0;
}