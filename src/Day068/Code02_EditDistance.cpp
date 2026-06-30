// 编辑距离
// 给你两个单词 word1 和 word2
// 请返回将 word1 转换成 word2 所使用的最少代价
// 你可以对一个单词进行如下三种操作：
// 插入一个字符，代价a
// 删除一个字符，代价b
// 替换一个字符，代价c
// 测试链接 : https://leetcode.cn/problems/edit-distance/
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class Solution
{
private:
  // a : word1中插入1个字符的代价
  // b : word1中删除1个字符的代价
  // c : word1中替换1个字符的代价
  // 返回从word1转化成word2的最低代价
  int editDistance1(const string &word1, const string &word2, int a, int b, int c)
  {
    int n = word1.size(), m = word2.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    for (int i = 1; i <= n; i++)
    {
      dp[i][0] = i * b;
    }

    for (int j = 1; j <= m; j++)
    {
      dp[0][j] = j * a;
    }

    for (int i = 1; i <= n; i++)
    {
      for (int j = 1; j <= m; j++)
      {
        int p1 = INT_MAX;
        if (word1[i - 1] == word2[j - 1])
        {
          p1 = dp[i - 1][j - 1];
        }

        int p2 = INT_MAX;
        if (word1[i - 1] != word2[j - 1])
        {
          p2 = dp[i - 1][j - 1] + c;
        }

        int p3 = dp[i][j - 1] + a;
        int p4 = dp[i - 1][j] + b;
        dp[i][j] = min({p1, p2, p3, p4});
      }
    }

    return dp[n][m];
  }

  int editDistance2(const string &word1, const string &word2, int a, int b, int c)
  {
    int n = word1.size(), m = word2.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    for (int i = 1; i <= n; i++)
    {
      dp[i][0] = i * b;
    }

    for (int j = 1; j <= m; j++)
    {
      dp[0][j] = j * a;
    }

    for (int i = 1; i <= n; i++)
    {
      for (int j = 1; j <= m; j++)
      {
        if (word1[i - 1] == word2[j - 1])
        {
          dp[i][j] = dp[i - 1][j - 1];
        }
        else
        {
          dp[i][j] = min({dp[i - 1][j - 1] + c,
                          dp[i - 1][j] + b, dp[i][j - 1] + a});
        }
      }
    }

    return dp[n][m];
  }

  int editDistance3(const string &word1, const string &word2, int a, int b, int c)
  {
    int n = word1.size();
    int m = word2.size();
    vector<int> dp(m + 1, 0);

    for (int j = 1; j <= m; j++)
    {
      dp[j] = j * a;
    }

    for (int i = 1; i <= n; i++)
    {
      int leftUp = (i - 1) * b;
      dp[0] = i * b;
      for (int j = 1; j <= m; j++)
      {
        int backUp = dp[j];
        if (word1[i - 1] == word2[j - 1])
        {
          dp[j] = leftUp;
        }
        else
        {
          dp[j] = min({leftUp + c,
                       dp[j] + b,
                       dp[j - 1] + a});
        }

        leftUp = backUp;
      }
    }

    return dp[m];
  }

public:
  int minDistance(string word1, string word2)
  {
    return editDistance1(word1, word2, 1, 1, 1);
  }
};