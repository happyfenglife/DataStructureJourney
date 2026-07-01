// 删除至少几个字符可以变成另一个字符串的子串
// 给定两个字符串s1和s2
// 返回s1至少删除多少字符可以成为s2的子串
// 对数器验证
#include <string>
#include <algorithm>
#include <vector>
#include <ctime>
#include <iostream>
using namespace std;

void generateSubsequences(const string &s, int idx, string path, vector<string> &list)
{
  if (idx == s.size())
  {
    list.push_back(path);
    return;
  }

  generateSubsequences(s, idx + 1, path, list);
  generateSubsequences(s, idx + 1, path + s[idx], list);
}

int minDelete1(const string &s1, const string &s2)
{
  vector<string> subseqs;
  generateSubsequences(s1, 0, "", subseqs);
  sort(subseqs.begin(), subseqs.end(), [](const string &a, const string &b)
       { return a.size() > b.size(); });

  for (const string &sub : subseqs)
  {
    if (s2.find(sub) != string::npos)
    {
      return s1.size() - sub.size();
    }
  }

  return s1.size();
}

int minDelete2(const string &str1, const string &str2)
{
  int n = str1.size(), m = str2.size();
  // dp[i][j] : s1前i个字符至少删除多少个，能变成s2前j个字符的某个后缀串
  vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
  for (int i = 1; i <= n; i++)
  {
    dp[i][0] = i;
    for (int j = 1; j <= m; j++)
    {
      if (str1[i - 1] == str2[j - 1])
      {
        dp[i][j] = dp[i - 1][j - 1];
      }
      else
      {
        dp[i][j] = dp[i - 1][j] + 1;
      }
    }
  }

  int ans = INT_MAX;
  for (int j = 0; j <= m; j++)
  {
    ans = min(ans, dp[n][j]);
  }

  return ans;
}

string randomString(int len, int varNum)
{
  string ans;
  ans.reserve(len);
  for (int i = 0; i < len; ++i)
  {
    ans.push_back(static_cast<char>('a' + rand() % varNum));
  }
  return ans;
}

int main()
{
  srand(static_cast<unsigned>(time(nullptr)));

  int maxLen = 12;
  int varNum = 3;
  int testTimes = 20000;
  cout << "测试开始" << endl;

  for (int i = 0; i < testTimes; ++i)
  {
    int len1 = rand() % maxLen + 1;
    int len2 = rand() % maxLen + 1;
    string s1 = randomString(len1, varNum);
    string s2 = randomString(len2, varNum);

    int ans1 = minDelete1(s1, s2);
    int ans2 = minDelete2(s1, s2);

    if (ans1 != ans2)
    {
      cout << "出错了！" << endl;
      cout << "s1 = " << s1 << ", s2 = " << s2 << endl;
      cout << "ans1 = " << ans1 << ", ans2 = " << ans2 << endl;
      break;
    }
  }
  cout << "测试结束" << endl;

  return 0;
}