// 火星词典
// 现有一种使用英语字母的火星语言
// 这门语言的字母顺序对你来说是未知的。
// 给你一个来自这种外星语言字典的字符串列表 words
// words 中的字符串已经 按这门新语言的字母顺序进行了排序 。
// 如果这种说法是错误的，并且给出的 words 不能对应任何字母的顺序，则返回 ""
// 否则，返回一个按新语言规则的 字典递增顺序 排序的独特字符串
// 如果有多个解决方案，则返回其中任意一个
// words中的单词一定都是小写英文字母组成的
// 测试链接(不需要会员) : https://leetcode.cn/problems/Jf1JuT/
#include <string>
#include <vector>
#include <array>
#include <queue>
#include <unordered_set>
using namespace std;

class Solution
{
public:
  string alienOrder(vector<string> &words)
  {
    array<int, 26> indegree;
    // -1 表示该字符未出现过
    indegree.fill(-1);

    // 标记出现过的字符，入度初始化为 0
    for (const auto &w : words)
    {
      for (char ch : w)
      {
        indegree[ch - 'a'] = 0;
      }
    }

    // 用集合避免重复边
    vector<unordered_set<int>> graph(26);

    // 构建有向边（来自相邻单词的第一个不同字符）
    for (size_t i = 0; i + 1 < words.size(); i++)
    {
      string &cur = words[i];
      string &nxt = words[i + 1];

      size_t len = min(cur.size(),
                       nxt.size());
      size_t j = 0;
      for (; j < len; j++)
      {
        if (cur[j] != nxt[j])
        {
          int u = cur[j] - 'a';
          int v = nxt[j] - 'a';

          // 如果插入成功（即之前没有这条边），才增加入度
          if (graph[u].insert(v).second)
          {
            ++indegree[v];
          }

          break;
        }
      }

      // 如果 next 是 cur 的前缀且比 cur 短，则不可能有合法顺序
      if (j == nxt.size() && cur.size() > nxt.size())
      {
        return "";
      }
    }

    // 拓扑排序（BFS）
    queue<int> q;
    int kinds = 0; // 出现过的字母种类数
    for (size_t i = 0; i < 26; i++)
    {
      if (indegree[i] != -1)
      {
        ++kinds;
      }

      if (indegree[i] == 0)
      {
        q.push(i);
      }
    }

    string ans;
    ans.reserve(kinds);
    while (!q.empty())
    {
      int u = q.front();
      q.pop();
      ans.push_back(static_cast<char>('a' + u));

      for (int v : graph[u])
      {
        --indegree[v];
        if (indegree[v] == 0)
        {
          q.push(v);
        }
      }
    }

    return ans.size() == static_cast<size_t>(kinds) ? ans : "";
  }
};