// 子数组的最小值之和
// 给定一个整数数组 arr，找到 min(b) 的总和，其中 b 的范围为 arr 的每个（连续）子数组。
// 由于答案可能很大，答案对 1000000007 取模
// 测试链接 : https://leetcode.cn/problems/sum-of-subarray-minimums/
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
  using ll = long long;

  static constexpr int MOD = 1000000007;

  static constexpr int MAXN = 30001;

  int st[MAXN];

  int r;

  int sumSubarrayMins(vector<int> &arr)
  {
    ll ans{};
    r = 0;
    for (int i = 0; i < arr.size(); i++)
    {
      while (r > 0 && arr[st[r - 1]] >= arr[i])
      {
        int cur = st[--r];
        int l = !r ? -1 : st[r - 1];
        ans = (ans + (ll)(cur - l) * (i - cur) * arr[cur]) % MOD;
      }

      st[r++] = i;
    }

    while (r > 0)
    {
      int cur = st[--r];
      int l = !r ? -1 : st[r - 1];
      ans = (ans + (ll)(cur - l) * (arr.size() - cur) * arr[cur]) % MOD;
    }

    return ans;
  }
};