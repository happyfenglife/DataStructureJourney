// 拓扑排序模版（Leetcode）
// 邻接表建图（动态方式）
// 课程表II
// 现在你总共有 numCourses 门课需要选，记为 0 到 numCourses - 1
// 给你一个数组 prerequisites ，其中 prerequisites[i] = [ai, bi]
// 表示在选修课程 ai 前 必须 先选修 bi
// 例如，想要学习课程 0 ，你需要先完成课程 1 ，我们用一个匹配来表示：[0,1]
// 返回你为了学完所有课程所安排的学习顺序。可能会有多个正确的顺序
// 你只要返回 任意一种 就可以了。如果不可能完成所有课程，返回 一个空数组
// 测试链接 : https://leetcode.cn/problems/course-schedule-ii/
#include <vector>
using namespace std;

class Solution
{
public:
  vector<int> findOrder(int numCourses, vector<vector<int>> &prerequisites)
  {
    if (numCourses <= 0)
    {
      return {};
    }

    // 邻接表（动态构建）
    vector<vector<int>> graph(numCourses);
    vector<int> indegree(numCourses, 0);

    for (const auto &edge : prerequisites)
    {
      if (edge.size() < 2)
      {
        continue;
      }

      int a = edge[0];
      int b = edge[1];
      graph[b].push_back(a);
      ++indegree[a];
    }

    // 使用 vector 作为环形队列
    vector<int> queue(numCourses);
    int l = 0, r = 0;
    for (int i = 0; i < numCourses; i++)
    {
      if (indegree[i] == 0)
      {
        queue[r++] = i;
      }
    }

    int cnt = 0;
    while (l < r)
    {
      int cur = queue[l++];
      ++cnt;
      for (int nxt : graph[cur])
      {
        if (--indegree[nxt] == 0)
        {
          queue[r++] = nxt;
        }
      }
    }

    if (cnt == numCourses)
    {
      // 返回前 r 个元素（此时 r == numCourses）
      return vector<int>(queue.begin(), queue.begin() + r);
    }
    else
    {
      return {};
    }
  }
};