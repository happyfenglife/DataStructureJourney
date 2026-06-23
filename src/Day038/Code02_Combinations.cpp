// 给你一个整数数组 nums ，其中可能包含重复元素，请你返回该数组所有可能的组合
// 答案 不能 包含重复的组合。返回的答案中，组合可以按 任意顺序 排列
// 注意其实要求返回的不是子集，因为子集一定是不包含相同元素的，要返回的其实是不重复的组合
// 比如输入：nums = [1,2,2]
// 输出：[[],[1],[1,2],[1,2,2],[2],[2,2]]
// 测试链接 : https://leetcode.cn/problems/subsets-ii/
#include <vector>
#include <algorithm>
using namespace std;

class Solution
{
private:
  void dfs(const vector<int> &nums, int idx, vector<int> &path, vector<vector<int>> &ans)
  {
    int n = nums.size();
    if (idx == n)
    {
      ans.push_back(path);
      return;
    }

    int next = idx + 1;
    while (next < n && nums[next] == nums[idx])
    {
      ++next;
    }

    // 分支1：当前数选 0 个，直接跳到下一组
    dfs(nums, next, path, ans);

    // 分支2：当前数选 1 个、2 个、3 个... 都尝试
    for (int i = idx; i < next; i++)
    {
      path.push_back(nums[i]);
      dfs(nums, next, path, ans);
    }

    // 回溯：恢复 path 到进入本层前的状态
    for (int i = idx; i < next; i++)
    {
      path.pop_back();
    }
  }

public:
  vector<vector<int>> subsetsWithDup(vector<int> &nums)
  {
    sort(nums.begin(), nums.end());
    vector<vector<int>> ans;
    vector<int> path;
    dfs(nums, 0, path, ans);
    return ans;
  }
};