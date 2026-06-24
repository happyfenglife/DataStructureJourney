// 有重复项数组的去重全排列
// 测试链接 : https://leetcode.cn/problems/permutations-ii/
#include <vector>
#include <unordered_set>
using namespace std;

class Solution
{
private:
  void backtrack(vector<int> &nums, int idx, vector<vector<int>> &ans)
  {
    if (idx == nums.size())
    {
      ans.push_back(nums);
      return;
    }

    unordered_set<int> used;
    for (int j = idx; j < nums.size(); j++)
    {
      if (used.find(nums[j]) == used.end())
      {
        used.insert(nums[j]);
        swap(nums[idx], nums[j]);
        backtrack(nums, idx + 1, ans);
        swap(nums[idx], nums[j]);
      }
    }
  }

public:
  vector<vector<int>> permuteUnique(vector<int> &nums)
  {
    vector<vector<int>> ans;
    backtrack(nums, 0, ans);
    return ans;
  }
};