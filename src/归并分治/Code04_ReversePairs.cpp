// 翻转对数量
// 测试链接 : https://leetcode.cn/problems/reverse-pairs/
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
  using ll = long long;

  static constexpr int MAXN = 5E4 + 1;

  int help[MAXN];

  int reversePairs(vector<int> &v)
  {
    return counts(v, 0, v.size() - 1);
  }

  // 统计l...r范围上，翻转对的数量，同时l...r范围统计完后变有序
  // 时间复杂度O(n * logn)
  int counts(vector<int> &v, int l, int r)
  {
    if (l == r)
    {
      return 0;
    }

    int m = (l + r) / 2;
    return counts(v, l, m) + counts(v, m + 1, r) + merge(v, l, m, r);
  }

  int merge(vector<int> &v, int l, int m, int r)
  {
    // 统计部分
    int ans{};
    for (int i = l, j = m + 1; i <= m; i++)
    {
      while (j <= r && (ll)v[i] > (ll)v[j] * 2)
      {
        j++;
      }

      ans += j - m - 1;
    }

    // 正常merge
    int i = l, a = l, b = m + 1;
    while (a <= m && b <= r)
    {
      help[i++] = v[a] <= v[b] ? v[a++] : v[b++];
    }

    while (a <= m)
    {
      help[i++] = v[a++];
    }
    while (b <= r)
    {
      help[i++] = v[b++];
    }

    for (i = l; i <= r; i++)
    {
      v[i] = help[i];
    }

    return ans;
  }
};