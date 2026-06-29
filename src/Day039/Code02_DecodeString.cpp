// 含有嵌套的字符串解码
// 测试链接 : https://leetcode.cn/problems/decode-string/
#include <string>
#include <cctype>
using namespace std;

class Solution
{
private:
  string dfs(const string &s, int i)
  {
    string path;
    int cnt = 0;

    while (i < s.size() && s[i] != ']')
    {
      if (isalpha(s[i]))
      {
        path += s[i++];
      }
      else if (isdigit(s[i]))
      {
        cnt = cnt * 10 + (s[i++] - '0');
      }
      else
      {
        string inner = dfs(s, i + 1);
        i = where + 1;

        while (cnt-- > 0)
        {
          path += inner;
        }

        cnt = 0;
      }
    }

    where = i;
    return path;
  }

public:
  int where;

  string decodeString(string s)
  {
    where = 0;
    return dfs(s, 0);
  }
};
