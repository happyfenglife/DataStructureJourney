// 归并排序，填函数练习风格
// 测试链接 : https://leetcode.cn/problems/sort-an-array/
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
  vector<int> sortArray(vector<int> &nums)
  {
    if (nums.size() > 1)
    {
      mergeSort1(nums);
    }

    return nums;
  }

  static constexpr int MAXN = 5E4 + 1;

  int help[MAXN];

  void mergeSort1(vector<int> &v)
  {
    sort(v, 0, v.size() - 1);
  }

  void mergeSort2(vector<int> &v)
  {
    int n = v.size();
    for (int step = 1, l, m, r; step < n; step <<= 1)
    {
      l = 0;
      while (l < n)
      {
        m = l + step - 1;
        if (m + 1 >= n)
        {
          break;
        }

        r = min(l + (step << 1) - 1, n - 1);
        merge(v, l, m, r);
        l = r + 1;
      }
    }
  }

  void sort(vector<int> &v, int l, int r)
  {
    if (l == r)
    {
      return;
    }

    int m = (l + r) / 2;
    sort(v, l, m);
    sort(v, m + 1, r);
    merge(v, l, m, r);
  }

  void merge(vector<int> &v, int l, int m, int r)
  {
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
  }
};