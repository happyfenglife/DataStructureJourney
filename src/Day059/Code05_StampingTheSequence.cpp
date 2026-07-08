// 戳印序列
// 你想最终得到"abcbc"，认为初始序列为"?????"。印章是"abc"
// 那么可以先用印章盖出"??abc"的状态，
// 然后用印章最左字符和序列的0位置对齐，就盖出了"abcbc"
// 这个过程中，"??abc"中的a字符，被印章中的c字符覆盖了
// 每次盖章的时候，印章必须完全盖在序列内
// 给定一个字符串target是最终的目标，长度为n，认为初始序列为n个'?'
// 给定一个印章字符串stamp，目标是最终盖出target
// 但是印章的使用次数必须在10*n次以内
// 返回一个数组，该数组由每个回合中被印下的最左边字母的索引组成
// 上面的例子返回[2,0]，表示印章最左字符依次和序列2位置、序列0位置对齐盖下去，就得到了target
// 如果不能在10*n次内印出序列，就返回一个空数组
// 测试链接 : https://leetcode.cn/problems/stamping-the-sequence/
#include <vector>
#include <array>
#include <string>
#include <algorithm>
using namespace std;

class Solution
{
public:
  vector<int> movesToStamp(string stamp, string target)
  {
    int m = static_cast<int>(stamp.size());
    int n = static_cast<int>(target.size());
    if (m > n)
    {
      return {};
    }

    // indegree[i] 表示以 i 为起点的窗口中，需要匹配的字符数量（初始为 m）
    vector<int> indegree(n - m + 1, m);
    // graph[pos] 存储：如果 target[pos] 不匹配 stamp 中相应字符，
    // 则这些以某些起点 i 开始的窗口依赖于该 pos（即 pos -> i 边）
    vector<vector<int>> graph(n);
    vector<int> q;
    q.reserve(n - m + 1);

    // 初始化 indegree 和 graph（O(n * m)）
    for (int i = 0; i <= n - m; i++)
    {
      for (int j = 0; j < m; j++)
      {
        if (target[i + j] == stamp[j])
        {
          if (--indegree[i] == 0)
          {
            q.push_back(i);
          }
        }
        else
        {
          graph[i + j].push_back(i);
        }
      }
    }

    vector<char> visited(n, 0); // 标记 target 的位置是否已“解除”（已被某次盖章覆盖）
    vector<int> path;
    path.reserve(n - m + 1);

    // 使用队列模拟拓扑 / BFS 过程
    size_t qi = 0;
    while (qi < q.size())
    {
      int cur = q[qi++];
      path.push_back(cur);

      for (int j = 0; j < m; j++)
      {
        int pos = cur + j;
        if (!visited[pos])
        {
          visited[pos] = 1;
          for (int nxt : graph[pos])
          {
            if (--indegree[nxt] == 0)
            {
              q.push_back(nxt);
            }
          }
        }
      }
    }

    // 若没有覆盖所有窗口，说明无法成功构造 target
    if (static_cast<int>(path.size()) != n - m + 1)
    {
      return {};
    }

    // 需要将顺序反转（从最后一次盖章到最先一次）
    reverse(path.begin(), path.end());
    return path;
  }
};