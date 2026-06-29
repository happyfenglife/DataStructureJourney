// 含有嵌套的分子式求原子数量
// 测试链接 : https://leetcode.cn/problems/number-of-atoms/
#include <string>
#include <map>
using namespace std;

class Solution
{
private:
  map<string, int> dfs(const string &s, int i)
  {
    map<string, int> ans;
    string name;
    map<string, int> pre;
    bool hasPre = false;
    int cnt = 0;

    while (i < s.size() && s[i] != ')')
    {
      if (isupper(s[i]) || s[i] == '(')
      {
        fill(ans, name, pre, hasPre, cnt);
        name.clear();
        pre.clear();
        hasPre = false;
        cnt = 0;

        if (isupper(s[i]))
        {
          name.push_back(s[i++]);
        }
        else
        {
          pre = dfs(s, i + 1);
          i = where + 1;
          hasPre = true;
        }
      }
      else if (islower(s[i]))
      {
        name.push_back(s[i++]);
      }
      else
      {
        cnt = cnt * 10 + (s[i++] - '0');
      }
    }
  }

  void fill(map<string, int> &ans, string &name, map<string, int> &pre, bool hasPre, int cnt)
  {
    if (name.empty() && !hasPre)
    {
      return;
    }

    if (cnt == 0)
    {
      cnt = 1;
    }

    if (!name.empty())
    {
      ans[name] += cnt;
    }
    else if (hasPre)
    {
      for (auto &[atom, num] : pre)
      {
        ans[atom] += num * cnt;
      }
    }
  }

public:
  int where;
  string countOfAtoms(string formula)
  {
    where = 0;
    map<string, int> result = dfs(formula, 0);

    string ans;
    for (auto &[atom, count] : result)
    {
      ans += atom;
      if (count > 1)
      {
        ans += to_string(count);
      }
    }

    return ans;
  }
};