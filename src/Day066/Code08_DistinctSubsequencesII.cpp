// 不同的子序列 II
// 给定一个字符串 s，计算 s 的 不同非空子序列 的个数
// 因为结果可能很大，答案对 1000000007 取模
// 字符串的 子序列 是经由原字符串删除一些（也可能不删除）
// 字符但不改变剩余字符相对位置的一个新字符串
// 例如，"ace" 是 "abcde" 的一个子序列，但 "aec" 不是
// 测试链接 : https://leetcode.cn/problems/distinct-subsequences-ii/
#include <string>
#include <array>
using namespace std;

class Solution
{
public:
  int distinctSubseqII(string s)
  {
    const int MOD = 1000000007;
    array<int, 26> cnt{};
    int all = 1;
    for (char x : s)
    {
      int newAdd = (all - cnt[x - 'a'] + MOD) % MOD;
      cnt[x - 'a'] = (cnt[x - 'a'] + newAdd) % MOD;
      all = (all + newAdd) % MOD;
    }

    return (all - 1 + MOD) % MOD;
  }
};