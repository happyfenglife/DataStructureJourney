// 最长数对链
// 给你一个由n个数对组成的数对数组pairs
// 其中 pairs[i] = [lefti, righti] 且 lefti < righti
// 现在，我们定义一种 跟随 关系，当且仅当 b < c 时
// 数对 p2 = [c, d] 才可以跟在 p1 = [a, b] 后面
// 我们用这种形式来构造 数对链
// 找出并返回能够形成的最长数对链的长度
// 测试链接 : https://leetcode.cn/problems/maximum-length-of-pair-chain/
#include <vector>
#include <algorithm>
#include <limits>
using namespace std;

class Solution
{
public:
  int findLongestChain(vector<vector<int>> &pairs)
  {
    int n = static_cast<int>(pairs.size());
    // 数对根据开始位置排序，从小到大
    // 结束位置无所谓！
    sort(pairs.begin(), pairs.end(), [](auto &a, auto &b)
         { return a[0] < b[0]; });

    vector<int> ends(n);
    int len{};
    for (auto &v : pairs)
    {
      auto it = lower_bound(ends.begin(), ends.begin() + len, v[0]);
      if (it == ends.begin() + len)
      {
        ends[len++] = v[1];
      }
      else
      {
        *it = min(*it, v[1]);
      }
    }

    return len;
  }

  int findLongestChain2(vector<vector<int>> &pairs)
  {
    sort(pairs.begin(), pairs.end(), [](auto &a, auto &b)
         { return a[1] < b[1]; });

    int ans{}, pre{numeric_limits<int>::min()};
    for (auto &v : pairs)
    {
      if (v[0] > pre)
      {
        ans++;
        pre = v[1];
      }
    }

    return ans;
  }
};