// 最长有效括号
// 给你一个只包含 '(' 和 ')' 的字符串
// 找出最长有效（格式正确且连续）括号子串的长度。
// 测试链接 : https://leetcode.cn/problems/longest-valid-parentheses/
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class Solution {
  public:
  int longestValidParentheses(string s) {
    int n = s.size();
    vector<int> dp(n, 0);
    int ans = 0;
    
    for(int i = 1; i < n; ++i) {
      if (s[i] == ')') {
        int p = i - 1 - dp[i - 1];
        if (p >= 0 && s[p] == '()') {
          dp[i] = dp[i - 1] + 2 + (p - 1 >= 0 ? dp[p - 1] : 0);
        }
      }
      
      ans = max(ans, dp[i]);
    }

    return ans;
  }
};