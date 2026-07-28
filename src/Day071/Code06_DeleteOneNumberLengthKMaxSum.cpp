// 删掉1个数字后长度为k的子数组最大累加和
// 给定一个数组nums，求必须删除一个数字后的新数组中
// 长度为k的子数组最大累加和，删除哪个数字随意
// 对数器验证
#include <iostream>
#include <vector>
#include <limits>
#include <random>
#include <chrono>
using namespace std;

vector<int> deleteAt(const vector<int> &nums, int index)
{
  int n = static_cast<int>(nums.size());
  vector<int> ans(n - 1);
  for (int i = 0, j = 0; i < n; i++)
  {
    if (i != index)
    {
      ans[j++] = nums[i];
    }
  }

  return ans;
}

// 暴力方法
// 为了测试
// 枚举每一个子数组找到最大累加和
int lenKmaxSum(vector<int> &nums, int k)
{
  int n = static_cast<int>(nums.size());
  int ans = numeric_limits<int>::min();
  for (int i = 0; i <= n - k; i++)
  {
    int cur{};
    for (int j = i, cnt = 0; cnt < k; j++, cnt++)
    {
      cur += nums[j];
    }

    ans = max(ans, cur);
  }

  return ans;
}

// 暴力方法
// 为了测试
int maxSum1(const vector<int> &nums, int k)
{
  int n = static_cast<int>(nums.size());
  if (n <= k)
  {
    return 0;
  }

  int ans = numeric_limits<int>::min();
  for (int i = 0; i < n; i++)
  {
    vector<int> rest = deleteAt(nums, i);
    ans = max(ans, lenKmaxSum(rest, k));
  }

  return ans;
}

// 正式方法
// 时间复杂度O(N)
int maxSum2(vector<int> &nums, int k)
{
  int n = static_cast<int>(nums.size());
  if (n <= k)
  {
    return 0;
  }

  vector<int> window(n);
  int l{}, r{};
  long long sum{};
  int ans = numeric_limits<int>::min();
  for (int i = 0; i < n; i++)
  {
    while (l < r && nums[window[r - 1]] >= nums[i])
    {
      r--;
    }

    window[r++] = i;
    sum += nums[i];
    if (i >= k)
    {
      ans = max(ans, static_cast<int>(sum - nums[window[l]]));
      if (window[l] == i - k)
      {
        ++l;
      }

      sum -= nums[i - k];
    }
  }

  return ans;
}

// 为了测试
// 生成长度为n，值在[-v, +v]之间的随机数组
vector<int> randomArray(int n, int v)
{
  mt19937 gen(static_cast<unsigned int>(chrono::high_resolution_clock::now().time_since_epoch().count()));
  uniform_int_distribution<int> dist(-v, v);
  vector<int> ans(n);
  for (int i = 0; i < n; i++)
  {
    ans[i] = dist(gen);
  }
  return ans;
}

int main()
{
  int n = 200;
  int v = 1000;
  int testTimes = 10000;
  cout << "测试开始" << '\n';

  mt19937 gen(static_cast<unsigned int>(chrono::high_resolution_clock::now().time_since_epoch().count()));
  uniform_int_distribution<int> lenDist(1, n);
  uniform_int_distribution<int> kDist(1, n);

  for (int i = 0; i < testTimes; i++)
  {
    int len = lenDist(gen);
    vector<int> nums = randomArray(len, v);
    int k = kDist(gen);
    int ans1 = maxSum1(nums, k);
    int ans2 = maxSum2(nums, k);
    if (ans1 != ans2)
    {
      cout << "出错了!" << '\n';
      // Optional: print debugging info similar to typical 对数器 output
      cout << "len = " << len << ", k = " << k << '\n';
      cout << "nums = [";
      for (size_t t = 0; t < nums.size(); ++t)
      {
        if (t)
          cout << ", ";
        cout << nums[t];
      }
      cout << "]\n";
      cout << "ans1 = " << ans1 << ", ans2 = " << ans2 << '\n';
      return 0;
    }
  }

  cout << "测试结束" << '\n';
  return 0;
}