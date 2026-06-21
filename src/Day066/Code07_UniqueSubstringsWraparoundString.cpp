// 环绕字符串中唯一的子字符串
// 定义字符串 base 为一个 "abcdefghijklmnopqrstuvwxyz" 无限环绕的字符串
// 所以 base 看起来是这样的：
// "..zabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcd.."
// 给你一个字符串 s ，请你统计并返回 s 中有多少 不同非空子串 也在 base 中出现
// 测试链接 : https://leetcode.cn/problems/unique-substrings-in-wraparound-string/
#include <vector>
#include <string>
using namespace std;

class Solution
{
public:
  int findSubstringInWraproundString(string s)
  {
    int n = s.size();
    if (n == 0)
      return 0;

    vector<int> dp(26, 0);
    dp[s[0] - 'a'] = 1;
    int len = 1;

    for (int i = 1; i < n; i++)
    {
      int cur = s[i] - 'a';
      int pre = s[i - 1] - 'a';

      if ((pre == 25 && cur == 0) || (cur == pre + 1))
        ++len;
      else
        len = 1;

      dp[cur] = max(dp[cur], len);
    }

    int ans = 0;
    for (int cnt : dp)
    {
      ans += cnt;
    }

    return ans;
  }
};