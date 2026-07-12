// 从树中删除边的最小分数
// 存在一棵无向连通树，树中有编号从0到n-1的n个节点，以及n-1条边
// 给你一个下标从0开始的整数数组nums长度为n，其中nums[i]表示第i个节点的值
// 另给你一个二维整数数组edges长度为n-1
// 其中 edges[i] = [ai, bi] 表示树中存在一条位于节点 ai 和 bi 之间的边
// 删除树中两条不同的边以形成三个连通组件，对于一种删除边方案，定义如下步骤以计算其分数：
// 分别获取三个组件每个组件中所有节点值的异或值
// 最大 异或值和 最小 异或值的 差值 就是这种删除边方案的分数
// 返回可能的最小分数
// 测试链接 : https://leetcode.cn/problems/minimum-score-after-removals-on-a-tree/
#include <vector>
#include <array>
#include <limits>
#include <algorithm>
using namespace std;

class Solution
{
public:
  static constexpr int MAXN = 1010;

  // 下标为原始节点编号
  array<int, MAXN> dfn;

  // 下标为dfn序号
  array<int, MAXN> xors;

  // 下标为dfn序号
  array<int, MAXN> sz;

  int cnt;

  int minimumScore(vector<int> &nums, vector<vector<int>> &edges)
  {
    int n = static_cast<int>(nums.size());
    vector<vector<int>> graph(n);

    for (const auto &e : edges)
    {
      graph[e[0]].push_back(e[1]);
      graph[e[1]].push_back(e[0]);
    }

    fill(dfn.begin(), dfn.begin() + n, 0);
    cnt = 0;
    dfs(nums, graph, 0);
    int m = static_cast<int>(edges.size());
    int ans = numeric_limits<int>::max();
    for (int i = 0, a, b, pre, pos, sum1, sum2, sum3; i < m; i++)
    {
      a = max(dfn[edges[i][0]], dfn[edges[i][1]]);
      for (int j = i + 1; j < m; j++)
      {
        b = max(dfn[edges[j][0]], dfn[edges[j][1]]);
        if (a < b)
        {
          pre = a;
          pos = b;
        }
        else
        {
          pre = b;
          pos = a;
        }

        sum1 = xors[pos];
        if (pos < pre + sz[pre])
        {
          sum2 = xors[pre] ^ xors[pos];
          sum3 = xors[1] ^ xors[pre];
        }
        else
        {
          sum2 = xors[pre];
          sum3 = xors[1] ^ sum1 ^ sum2;
        }

        ans = min(ans, (max({sum1, sum2, sum3}) - min({sum1, sum2, sum3})));
      }
    }

    return ans;
  }

  void dfs(vector<int> &nums, vector<vector<int>> &graph, int u)
  {
    int i = ++cnt;
    dfn[u] = i;
    xors[i] = nums[u];
    sz[i] = 1;
    for (int v : graph[u])
    {
      if (dfn[v] == 0)
      {
        dfs(nums, graph, v);
        xors[i] ^= xors[dfn[v]];
        sz[i] += sz[dfn[v]];
      }
    }
  }
};