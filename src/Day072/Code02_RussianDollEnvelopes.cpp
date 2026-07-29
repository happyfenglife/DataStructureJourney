// 俄罗斯套娃信封问题
// 给你一个二维整数数组envelopes ，其中envelopes[i]=[wi, hi]
// 表示第 i 个信封的宽度和高度
// 当另一个信封的宽度和高度都比这个信封大的时候
// 这个信封就可以放进另一个信封里，如同俄罗斯套娃一样
// 请计算 最多能有多少个信封能组成一组“俄罗斯套娃”信封
// 即可以把一个信封放到另一个信封里面，注意不允许旋转信封
// 测试链接 : https://leetcode.cn/problems/russian-doll-envelopes/
#include <vector>
#include <algorithm>
using namespace std;

class Solution
{
public:
  int maxEnvelopes(vector<vector<int>> &envelopes)
  {
    // 排序策略:
    // 宽度从小到大
    // 宽度一样，高度从大到小
    sort(envelopes.begin(), envelopes.end(), [](auto &a, auto &b){
      if (a[0] == b[0])
        return a[1] > b[1];
      
      return a[0] < b[0]; 
    });

    int n = static_cast<int>(envelopes.size());
    vector<int> ends(n);
    int len{};
    for (int i = 0, num; i < n; i++)
    {
      num = envelopes[i][1];
      auto it = lower_bound(ends.begin(), ends.begin() + len, num);
      if (it == ends.begin() + len)
      {
        ends[len++] = num;
      } else {
        *it = num;
      }
    }
    
    return len;
  }
};