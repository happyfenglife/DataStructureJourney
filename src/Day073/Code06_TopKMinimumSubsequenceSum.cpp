// 非负数组前k个最小的子序列累加和
// 给定一个数组nums，含有n个数字，都是非负数
// 给定一个正数k，返回所有子序列中累加和最小的前k个累加和
// 子序列是包含空集的
// 1 <= n <= 10^5
// 1 <= nums[i] <= 10^6
// 1 <= k <= 10^5
// 注意这个数据量，用01背包的解法是不行的，时间复杂度太高了
// 对数器验证
#include <bits/stdc++.h>
using namespace std;

void dfs1(vector<int> &nums, int i, int sum, vector<int> &ans)
{
  if (i == nums.size())
  {
    ans.push_back(sum);
  }
  else
  {
    dfs1(nums, i + 1, sum, ans);
    dfs1(nums, i + 1, sum + nums[i], ans);
  }
}

// 暴力方法
// 为了验证
vector<int> topKSum1(vector<int> &nums, int k)
{
  vector<int> allSubsequences;
  dfs1(nums, 0, 0, allSubsequences);
  sort(allSubsequences.begin(), allSubsequences.end());
  return vector(allSubsequences.begin(), allSubsequences.begin() + k);
}

// 01背包来实现
// 这种方法此时不是最优解
// 因为n很大，数值也很大，那么可能的累加和就更大
// 时间复杂度太差
vector<int> topKSum2(vector<int> &nums, int k)
{
  int sum{accumulate(nums.begin(), nums.end(), 0)};

  // dp[j] 表示和为 j 的子序列个数
  vector<int> dp(sum + 1);
  dp[0] = 1;
  for (int num : nums)
  {
    for (int j = sum; j >= num; j--)
    {
      dp[j] += dp[j - num];
    }
  }

  vector<int> ans(k);
  int index{};
  for (int j = 0; j <= sum && index < k; j++)
  {
    for (int i = 0; i < dp[j] && index < k; i++)
    {
      ans[index++] = j;
    }
  }

  return ans;
}

vector<int> topKSum3(vector<int> nums, int k)
{
  sort(nums.begin(), nums.end());
  // (子序列的最右下标，子序列的累加和)
  auto cmp = [](pair<int, int> &p1, pair<int, int> &p2)
  {
    return p1.second > p2.second;
  };
  priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> heap(cmp);
  heap.push({0, nums[0]});
  vector<int> ans(k);
  for (int i = 1; i < k; i++)
  {
    auto cur = heap.top();
    heap.pop();
    int right = cur.first;
    int sum = cur.second;
    ans[i] = sum;
    if (right + 1 < nums.size())
    {
      heap.push({right + 1, sum + nums[right + 1]});
      heap.push({right + 1, sum - nums[right] + nums[right + 1]});
    }
  }

  return ans;
}

vector<int> randomArray(int len, int val)
{
  vector<int> v(len);
  for (int i = 0; i < len; i++)
  {
    v[i] = rand() % val;
  }

  return v;
}

bool equals(vector<int> &v1, vector<int> &v2)
{
  return v1 == v2;
}

int main()
{
  srand(time(nullptr));
  int n = 15;
  int v = 40;
  int testTime = 5000;
  cout << "测试开始" << '\n';
  for (int i = 0; i < testTime; i++)
  {
    int len = (int)(rand() % n) + 1;
    vector<int> nums = randomArray(len, v);
    int maxK = (1 << len) - 1;
    int k = (int)(rand() % maxK) + 1;
    vector<int> ans1 = topKSum1(nums, k);
    vector<int> ans2 = topKSum2(nums, k);
    vector<int> ans3 = topKSum3(nums, k);
    if (!equals(ans1, ans2) || !equals(ans1, ans3))
    {
      cout << "出错了！" << '\n';
    }
  }

  cout << "测试结束" << '\n';
  return 0;
}