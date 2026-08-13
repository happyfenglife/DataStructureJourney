// 移除最多的同行或同列石头
// n 块石头放置在二维平面中的一些整数坐标点上。每个坐标点上最多只能有一块石头
// 如果一块石头的 同行或者同列 上有其他石头存在，那么就可以移除这块石头
// 给你一个长度为 n 的数组 stones ，其中 stones[i] = [xi, yi] 表示第 i 块石头的位置
// 返回 可以移除的石子 的最大数量。
// 测试链接 : https://leetcode.cn/problems/most-stones-removed-with-same-row-or-column/
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
  static constexpr int MAXN = 1001;

  unordered_map<int, int> rowFirst;

  unordered_map<int, int> colFirst;

  int father[MAXN];

  int sets;

  int removeStones(vector<vector<int>> &stones)
  {
    int n = stones.size();
    build(n);
    for (int i = 0; i < n; i++)
    {
      int row = stones[i][0];
      int col = stones[i][1];
      if (!rowFirst.count(row))
      {
        rowFirst[row] = i;
      }
      else
      {
        unionSet(i, rowFirst[row]);
      }

      if (!colFirst.count(col))
      {
        colFirst[col] = i;
      }
      else
      {
        unionSet(i, colFirst[col]);
      }
    }

    return n - sets;
  }

  void build(int n)
  {
    rowFirst.clear();
    colFirst.clear();
    for (int i = 0; i < n; i++)
    {
      father[i] = i;
    }

    sets = n;
  }

  int find(int i)
  {
    if (i != father[i])
    {
      father[i] = find(father[i]);
    }

    return father[i];
  }

  void unionSet(int x, int y)
  {
    int fx = find(x), fy = find(y);
    if (fx != fy)
    {
      father[fx] = fy;
      --sets;
    }
  }
};