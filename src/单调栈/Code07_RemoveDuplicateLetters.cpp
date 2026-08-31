// 去除重复字母保证剩余字符串的字典序最小
// 给你一个字符串 s ，请你去除字符串中重复的字母，使得每个字母只出现一次
// 需保证 返回结果的字典序最小
// 要求不能打乱其他字符的相对位置
// 测试链接 : https://leetcode.cn/problems/remove-duplicate-letters/
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
  static constexpr int MAXN = 26;

  // 每种字符词频
  int cnts[MAXN];

  // 每种字符目前有没有进栈
  bool enter[MAXN];

  char st[MAXN];

  int r;

  string removeDuplicateLetters(string s)
  {
    r = 0;
    fill(begin(cnts), begin(cnts) + MAXN, 0);
    fill(begin(enter), begin(enter) + MAXN, false);
    for (char c : s)
    {
      cnts[c - 'a']++;
    }

    for (char c : s)
    {
      if (!enter[c - 'a'])
      {
        while (r > 0 && st[r - 1] > c && cnts[st[r - 1] - 'a'] > 0)
        {
          enter[st[r - 1] - 'a'] = false;
          r--;
        }

        st[r++] = c;
        enter[c - 'a'] = true;
      }

      cnts[c - 'a']--;
    }

    return string(begin(st), begin(st) + r);
  }
};