// 牛牛和他的朋友们约定了一套接头密匙系统，用于确认彼此身份
// 密匙由一组数字序列表示，两个密匙被认为是一致的，如果满足以下条件：
// 密匙 b 的长度不超过密匙 a 的长度。
// 对于任意 0 <= i < length(b)，有b[i+1] - b[i] == a[i+1] - a[i]
// 现在给定了m个密匙 b 的数组，以及n个密匙 a 的数组
// 请你返回一个长度为 m 的结果数组 ans，表示每个密匙b都有多少一致的密匙
// 数组 a 和数组 b 中的元素个数均不超过 10^5
// 1 <= m, n <= 1000
// 测试链接 : https://www.nowcoder.com/practice/c552d3b4dfda49ccb883a6371d9a6932
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
  vector<int> countConsistentKeys(vector<vector<int>> &b, vector<vector<int>> &a)
  {
    build();
    string s;
    for (auto &nums : a)
    {
      s.clear();
      for (int i = 1; i < nums.size(); i++)
      {
        s += to_string(nums[i] - nums[i - 1]) + '#';
      }

      insert(s);
    }

    vector<int> ans(b.size());
    for (int i = 0; i < b.size(); i++)
    {
      s.clear();
      auto &nums = b[i];
      for (int j = 1; j < nums.size(); j++)
      {
        s += to_string(nums[j] - nums[j - 1]) + "#";
      }

      ans[i] = count(s);
    }

    return ans;
  }

  static constexpr int MAXN = 2E6 + 1;

  int tree[MAXN][12];

  int pass[MAXN];

  int cnt;

  void build()
  {
    cnt = 1;
  }

  int path(char c)
  {
    if (c == '#')
    {
      return 10;
    }
    else if (c == '-')
    {
      return 11;
    }
    else
    {
      return c - '0';
    }
  }

  void insert(string &s)
  {
    int cur{1};
    pass[cur]++;
    for (int i = 0, p; i < s.size(); i++)
    {
      p = path(s[i]);
      if (!tree[cur][p])
      {
        tree[cur][p] = ++cnt;
      }

      cur = tree[cur][p];
      pass[cur]++;
    }
  }

  int count(string &s)
  {
    int cur{1};
    for (int i = 0, p; i < s.size(); i++)
    {
      p = path(s[i]);
      if (!tree[cur][p])
      {
        return 0;
      }

      cur = tree[cur][p];
    }

    return pass[cur];
  }

  void clear()
  {
    for (int i = 1; i <= cnt; i++)
    {
      pass[i] = 0;
      memset(tree[i], 0, sizeof(tree[i]));
    }
  }
};