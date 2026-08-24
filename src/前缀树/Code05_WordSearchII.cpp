// 在二维字符数组中搜索可能的单词
// 给定一个 m x n 二维字符网格 board 和一个单词（字符串）列表 words
// 返回所有二维网格上的单词。单词必须按照字母顺序，通过 相邻的单元格 内的字母构成
// 其中“相邻”单元格是那些水平相邻或垂直相邻的单元格
// 同一个单元格内的字母在一个单词中不允许被重复使用
// 1 <= m, n <= 12
// 1 <= words.length <= 3 * 10^4
// 1 <= words[i].length <= 10
// 测试链接 : https://leetcode.cn/problems/word-search-ii/
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
  static constexpr int MAXN = 10001;

  int tree[MAXN][26];

  int pass[MAXN];

  string end[MAXN];

  int cnt;

  vector<string> findWords(vector<vector<char>> &board, vector<string> &words)
  {
    build(words);
    vector<string> ans;
    for (int i = 0; i < board.size(); i++)
    {
      for (int j = 0; j < board[0].size(); j++)
      {
        dfs(board, i, j, 1, ans);
      }
    }

    clear();
    return ans;
  }

  // board : 二维网格
  // i,j : 此时来到的格子位置，i行、j列
  // t : 前缀树的编号
  // vector<string>& ans : 收集到了哪些字符串，都放入ans
  // 返回值 : 收集到了几个字符串
  int dfs(vector<vector<char>> &board, int i,
          int j, int t, vector<string> &ans)
  {
    if (i < 0 || i == board.size() || j < 0 || j == board[0].size() ||
        board[i][j] == 0)
    {
      return 0;
    }

    char c = board[i][j];
    int road = c - 'a';
    t = tree[t][road];
    if (!pass[t])
    {
      return 0;
    }

    int fix{};
    if (!end[t].empty())
    {
      fix++;
      ans.push_back(end[t]);
      end[t].clear();
    }

    board[i][j] = 0;
    fix += dfs(board, i - 1, j, t, ans);
    fix += dfs(board, i + 1, j, t, ans);
    fix += dfs(board, i, j - 1, t, ans);
    fix += dfs(board, i, j + 1, t, ans);
    pass[t] -= fix;
    board[i][j] = c;
    return fix;
  }

  void build(vector<string> &words)
  {
    cnt = 1;
    for (auto &s : words)
    {
      int cur = 1;
      pass[cur]++;
      for (int i = 0, path; i < s.size(); i++)
      {
        path = s[i] - 'a';
        if (!tree[cur][path])
        {
          tree[cur][path] = ++cnt;
        }

        cur = tree[cur][path];
        pass[cur]++;
      }

      end[cur] = s;
    }
  }

  void clear()
  {
    for (int i = 1; i <= cnt; i++)
    {
      memset(tree[i], 0, sizeof(tree[i]));
      pass[i] = 0;
      end[i].clear();
    }
  }
};