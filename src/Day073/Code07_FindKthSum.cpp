// 找出数组的第K大和
// 给定一个数组nums和正数k
// 可以选择数组的任何子序列并对其元素求和
// 希望找到第k大的子序列和，子序列和允许出现重复
// 空子序列的和视作0，数组中的值可正、可负、可0
// 测试链接 : https://leetcode.cn/problems/find-the-k-sum-of-an-array/description/
//
// 转化逻辑如下 :
// 1，先把所有正数加起来，得到sum，这是nums第1大子序列和
// 2，nums第2大子序列和，要么sum中去掉一个最小的正数，要么sum + (选剩下的非正数字，拼出最大的累加和)
// 3，nums第2大子序列和 = (sum - 最小的正数) 或者 (sum - 选剩下的非正数字，拼出最小的绝对值)
// 4，原始数组记为nums，把每个数转成绝对值的数组记为a
// 5，nums第1大子序列和 = sum = sum - 0，其中0表示数组a取空集的累加和，认为是a的第1小子序列和
// 6，nums第1大子序列和 = sum - a的第1小子序列和
// 7，nums第2大子序列和 = sum - a的第2小子序列和
// 8，nums第k大子序列和 = sum - a的第k小子序列和
// 9，求a的第k小子序列和即可，注意，a的第1小子序列和，是空集的情况
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
  using ll = long long;

  struct Node
  {
    int idx;
    ll val;

    Node(int i, ll v)
        : idx{i}, val{v} {}
  };

  struct cmp
  {
    // 为了使 priority_queue 表现为最小堆（按 val，然后按 idx），
    // comparator 返回 true 当 a 应该排在 b 之后（即 a 大于 b）
    bool operator()(Node &a, Node &b)
    {
      if (a.val != b.val)
      {
        return a.val > b.val;
      }

      return a.idx > b.idx;
    }
  };

  long long kSum(vector<int> &nums, int k)
  {
    int n = nums.size();
    ll sum{};
    for (int i = 0; i < n; i++)
    {
      if (nums[i] > 0)
      {
        sum += nums[i];
      }
      else
      {
        nums[i] = -nums[i];
      }
    }

    sort(nums.begin(), nums.end());
    priority_queue<Node, vector<Node>, cmp> heap;
    // 空集，下标为-1，累加和为0，这是a的第1小子序列和
    heap.emplace(-1, 0ll);
    // 弹出前 k-1 个最小子序列和
    for (int i = 1; i < k; i++)
    {
      Node cur = heap.top();
      heap.pop();
      int idx = cur.idx;
      ll val = cur.val;
      if (idx + 1 < n)
      {
        heap.emplace(idx + 1, val + nums[idx + 1]);
        if (idx >= 0)
        {
          heap.emplace(idx + 1, val + nums[idx + 1] - nums[idx]);
        }
      }
    }

    // sum - a 的第 k 小子序列和
    return sum - heap.top().val;
  }
};