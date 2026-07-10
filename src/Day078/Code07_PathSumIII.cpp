// 路径总和 III
// 给定一个二叉树的根节点 root ，和一个整数 targetSum
// 求该二叉树里节点值之和等于 targetSum 的 路径 的数目
// 路径 不需要从根节点开始，也不需要在叶子节点结束
// 但是路径方向必须是向下的（只能从父节点到子节点）
// 测试链接 : https://leetcode.cn/problems/path-sum-iii/
#include <unordered_map>
using namespace std;

class Solution
{
public:
  struct TreeNode
  {
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right)
        : val(x), left(left), right(right) {}
  };

  int ans;

  int pathSum(TreeNode *root, int sum)
  {
    unordered_map<long long, int> pre;
    pre[0LL] = 1;
    ans = 0;
    dfs(root, sum, 0LL, pre);
    return ans;
  }

  // sum : 从头节点出发，来到x的时候，上方累加和是多少
  // 路径必须以x作为结尾，路径累加和是target的路径数量，累加到全局变量ans上
  void dfs(TreeNode *x, int target, long long sum, unordered_map<long long, int> &pre)
  {
    if (x != nullptr)
    {
      sum += x->val; // 从头节点出发一路走到x的整体累加和

      ans += pre[target - sum];
      pre[sum] += 1;
      dfs(x->left, target, sum, pre);
      dfs(x->right, target, sum, pre);

      // 回溯：将当前前缀和的计数减一
      pre[sum] -= 1;
    }
  }
};