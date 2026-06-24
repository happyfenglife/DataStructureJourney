// 没有重复项数字的全排列
// 测试链接 : https://leetcode.cn/problems/permutations/
#include <vector>
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

    for (int j = idx; j < nums.size(); j++)
    {
      swap(nums[idx], nums[j]);
      backtrack(nums, idx + 1, ans);
      swap(nums[idx], nums[j]);
    }
  }

public:
  vector<vector<int>> permute(vector<int> &nums)
  {
    vector<vector<int>> ans;
    backtrack(nums, 0, ans);
    return ans;
  }
};