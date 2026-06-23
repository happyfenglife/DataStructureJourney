// 字符串的全部子序列
// 子序列本身是可以有重复的，只是这个题目要求去重
// 测试链接 : https://www.nowcoder.com/practice/92e6247998294f2c933906fdedbc6e6a
#include <vector>
#include <string>
#include <unordered_set>
using namespace std;

class Solution
{
private:
  void dfs1(const string &s, int idx, string &path, unordered_set<string> &set)
  {
    if (idx == s.size())
    {
      set.insert(path);
      return;
    }

    path.push_back(s[idx]);
    dfs1(s, idx + 1, path, set);
    path.pop_back();
    dfs1(s, idx + 1, path, set);
  }

  void dfs2(const string &s, int idx, vector<char> &path, int size, unordered_set<string> &set)
  {
    if (idx == s.size())
    {
      set.insert(string(path.begin(), path.begin() + s.size()));
      return;
    }

    path[size] = s[idx];
    dfs2(s, idx + 1, path, size + 1, set);
    dfs2(s, idx + 1, path, size, set);
  }

public:
  vector<string> generatePermutation1(const string &str)
  {
    unordered_set<string> set;
    string path;
    dfs1(str, 0, path, set);
    return vector<string>(set.begin(), set.end());
  }

  vector<string> generatePermutation2(const string &str)
  {
    unordered_set<string> set;
    vector<char> path(str.size());
    dfs2(str, 0, path, 0, set);
    return vector<string>(set.begin(), set.end());
  }
};