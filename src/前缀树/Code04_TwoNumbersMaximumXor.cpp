// 数组中两个数的最大异或值
// 给你一个整数数组 nums ，返回 nums[i] XOR nums[j] 的最大运算结果，其中 0<=i<=j<=n
// 1 <= nums.length <= 2 * 10^5
// 0 <= nums[i] <= 2^31 - 1
// 测试链接 : https://leetcode.cn/problems/maximum-xor-of-two-numbers-in-an-array/
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
  static constexpr int MAXN = 3000001;

  int tree[MAXN][2];

  int cnt;

  int high;

  // 前缀树的做法
  int findMaximumXOR1(vector<int> &nums)
  {
    build(nums);
    int ans{};
    for (int num : nums)
    {
      ans = max(ans, maxXor(num));
    }

    clear();
    return ans;
  }

  // 用哈希表的做法
  int findMaximumXOR2(vector<int> &nums)
  {
    int maxv = INT_MIN;
    for (int num : nums)
    {
      maxv = max(num, maxv);
    }

    int ans{};
    unordered_set<int> set;
    for (int i = 31 - __builtin_clz(maxv | 1); i >= 0; i--)
    {
      int better = ans | (1 << i);
      set.clear();
      for (int num : nums)
      {
        // num : 31.....i 这些状态保留，剩下全成0
        num = (num >> i) << i;
        set.insert(num);
        // num ^ 某状态 是否能 达成better目标，就在set中找 某状态 : better ^ num
        if (set.count(better ^ num))
        {
          ans = better;
          break;
        }
      }
    }

    return ans;
  }

  void insert(int num)
  {
    int cur{1};
    for (int i = high, path; i >= 0; i--)
    {
      path = (num >> i) & 1;
      if (!tree[cur][path])
      {
        tree[cur][path] = ++cnt;
      }

      cur = tree[cur][path];
    }
  }

  void build(vector<int> &nums)
  {
    cnt = 1;
    int maxv = INT_MIN;
    for (int num : nums)
    {
      maxv = max(num, maxv);
    }

    // 计算数组最大值的二进制状态，有多少个前缀的0
    // 可以忽略这些前置的0，从left位开始考虑
    high = 31 - __builtin_clz(maxv | 1);
    for (int num : nums)
    {
      insert(num);
    }
  }

  void clear()
  {
    for (int i = 1; i <= cnt; i++)
    {
      memset(tree[i], 0, sizeof(tree[i]));
    }
  }

  int maxXor(int num)
  {
    int ans{};
    int cur{1};
    for (int i = high, status, want; i >= 0; i--)
    {
      status = (num >> i) & 1;
      // want : num第i位希望遇到的状态
      want = status ^ 1;
      if (!tree[cur][want])
      {
        want ^= 1;
      }

      ans |= (status ^ want) << i;
      cur = tree[cur][want];
    }

    return ans;
  }
};