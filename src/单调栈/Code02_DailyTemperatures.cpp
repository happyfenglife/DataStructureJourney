// 每日温度
// 给定一个整数数组 temperatures ，表示每天的温度，返回一个数组 answer
// 其中 answer[i] 是指对于第 i 天，下一个更高温度出现在几天后
// 如果气温在这之后都不会升高，请在该位置用 0 来代替。
// 测试链接 : https://leetcode.cn/problems/daily-temperatures/
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
  static constexpr int MAXN = 1E5 + 1;

  int st[MAXN];

  int r;

  vector<int> dailyTemperatures(vector<int> &v)
  {
    int n = v.size();
    vector<int> ans(n);
    r = 0;

    for (int i = 0, cur; i < n; i++)
    {
      // 相等时候的处理，相等也加入单调栈
      while (r > 0 && v[st[r - 1]] < v[i])
      {
        cur = st[--r];
        ans[cur] = i - cur;
      }

      st[r++] = i;
    }

    return ans;
  }
};