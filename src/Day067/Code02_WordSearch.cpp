// 单词搜索（无法改成动态规划）
// 给定一个 m x n 二维字符网格 board 和一个字符串单词 word
// 如果 word 存在于网格中，返回 true ；否则，返回 false 。
// 单词必须按照字母顺序，通过相邻的单元格内的字母构成
// 其中"相邻"单元格是那些水平相邻或垂直相邻的单元格
// 同一个单元格内的字母不允许被重复使用
// 测试链接 : https://leetcode.cn/problems/word-search/
#include <vector>
#include <string>
using namespace std;

class Solution
{
private:
  // 从 (i,j) 出发，匹配 word[k...]
  bool dfs(vector<vector<char>> &board, int i, int j, const string &word, int k)
  {
    if (k == word.size())
      return true;

    int n = board.size(), m = board[0].size();
    if (i < 0 || i >= n || j < 0 || j >= m || board[i][j] != word[k])
      return false;

    char tmp = board[i][j];
    board[i][j] = 0;

    bool ans = dfs(board, i + 1, j, word, k + 1) ||
               dfs(board, i - 1, j, word, k + 1) ||
               dfs(board, i, j + 1, word, k + 1) ||
               dfs(board, i, j - 1, word, k + 1);

    board[i][j] = tmp;
    return ans;
  }

public:
  bool exist(vector<vector<char>> &board, string word)
  {
    int n = board.size(), m = board[0].size();
    for (int i = 0; i < n; i++)
      for (int j = 0; j < m; j++)
        if (dfs(board, i, j, word, 0))
          return true;
  }
};