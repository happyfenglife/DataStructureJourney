// 二叉搜索子树的最大键值和
// 给你一棵以 root 为根的二叉树
// 请你返回 任意 二叉搜索子树的最大键值和
// 二叉搜索树的定义如下：
// 任意节点的左子树中的键值都 小于 此节点的键值
// 任意节点的右子树中的键值都 大于 此节点的键值
// 任意节点的左子树和右子树都是二叉搜索树
// 测试链接 : https://leetcode.cn/problems/maximum-sum-bst-in-binary-tree/
#include <limits>
#include <algorithm>
using namespace std;

class Solution
{
public:
  struct TreeNode
  {
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int v = 0, TreeNode *l = nullptr,
             TreeNode *r = nullptr)
        : val{v}, left{l}, right{r}
    {
    }
  };

  int maxSumBST(TreeNode *root)
  {
    return dfs(root).maxBstSum;
  }

  struct Info
  {
    int max;
    int min;
    int sum;
    bool isBst;
    int maxBstSum;

    Info(int a, int b, int c, bool d, int e)
        : max{a}, min{b}, sum{c}, isBst{d}, maxBstSum{e}
    {
    }
  };

  Info dfs(TreeNode *x)
  {
    if (x == nullptr)
    {
      return Info(
          numeric_limits<int>::min(),
          numeric_limits<int>::max(),
          0, true, 0);
    }

    Info l = dfs(x->left);
    Info r = dfs(x->right);
    int maxv = max({x->val, l.max, r.max});
    int minv = min({x->val, l.min, r.min});
    int sum = l.sum + r.sum + x->val;
    bool isBst = l.isBst && r.isBst && (x->val > l.max && x->val < r.min);
    int maxBstSum = max(l.maxBstSum, r.maxBstSum);
    if (isBst)
    {
      maxBstSum = max(maxBstSum, sum);
    }

    return Info(maxv, minv, sum, isBst, maxBstSum);
  }
};
