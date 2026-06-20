// 最低票价
// 在一个火车旅行很受欢迎的国度，你提前一年计划了一些火车旅行
// 在接下来的一年里，你要旅行的日子将以一个名为 days 的数组给出
// 每一项是一个从 1 到 365 的整数
// 火车票有 三种不同的销售方式
// 一张 为期1天 的通行证售价为 costs[0] 美元
// 一张 为期7天 的通行证售价为 costs[1] 美元
// 一张 为期30天 的通行证售价为 costs[2] 美元
// 通行证允许数天无限制的旅行
// 例如，如果我们在第 2 天获得一张 为期 7 天 的通行证
// 那么我们可以连着旅行 7 天(第2~8天)
// 返回 你想要完成在给定的列表 days 中列出的每一天的旅行所需要的最低消费
// 测试链接 : https://leetcode.cn/problems/minimum-cost-for-tickets/
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

class Solution
{
private:
  const int durations[3] = {1, 7, 30};

  int f1(const vector<int> &days, const vector<int> &costs, int i)
  {
    if (i == days.size())
      return 0;

    int ans = INT_MAX;
    for (int k = 0, j = i; k < 3; ++k)
    {
      while (j < days.size() && days[i] + durations[k] > days[j])
      {
        ++j;
      }

      ans = min(ans, costs[k] + f1(days, costs, j));
    }

    return ans;
  }

  int f2(const vector<int> &days, const vector<int> &costs, int i, vector<int> &dp)
  {
    if (i == days.size())
      return 0;

    if (dp[i] != INT_MAX)
      return dp[i];

    int ans = INT_MAX;
    for (int k = 0, j = i; k < 3; ++k)
    {
      while (j < days.size() && days[i] + durations[k] > days[j])
      {
        ++j;
      }

      ans = min(ans, costs[k] + f2(days, costs, j, dp));
    }

    dp[i] = ans;
    return ans;
  }

public:
  // 暴力尝试
  int mincostTickets1(vector<int> &days, vector<int> &costs)
  {
    return f1(days, costs, 0);
  }

  // 记忆化搜索
  int mincostTickets2(vector<int> &days, vector<int> &costs)
  {
    vector<int> dp(days.size(), INT_MAX);
    return f2(days, costs, 0, dp);
  }

  // 严格位置依赖的动态规划
  int mincostTickets3(vector<int> &days, vector<int> &costs)
  {
    int n = days.size();
    vector<int> dp(n + 1, INT_MAX);
    dp[n] = 0;
    for (int i = n - 1; i >= 0; i--)
    {
      for (int k = 0, j = i; k < 3; k++)
      {
        while (j < n && days[i] + durations[k] > days[j])
        {
          ++j;
        }
        
        dp[i] = min(dp[i], costs[k] + dp[j]);
      }
    }
    
    return dp[0];
  }
};