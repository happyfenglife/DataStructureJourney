// 最大BST子树
// 给定一个二叉树，找到其中最大的二叉搜索树（BST）子树，并返回该子树的大小
// 其中，最大指的是子树节点数最多的
// 二叉搜索树（BST）中的所有节点都具备以下属性：
// 左子树的值小于其父（根）节点的值
// 右子树的值大于其父（根）节点的值
// 注意：子树必须包含其所有后代
// 测试链接 : https://leetcode.cn/problems/largest-bst-subtree/
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
    TreeNode(int v = 0, TreeNode *l = nullptr, TreeNode *r = nullptr)
        : val(v), left(l), right(r) {}
  };

  int largestBSTSubtree(TreeNode *root)
  {
    return dfs(root).maxBstSize;
  }

  struct Info
  {
    long long max;
    long long min;
    bool isBst;
    int maxBstSize;

    Info(long long a, long long b, bool c, int d)
        : max{a}, min{b}, isBst{c}, maxBstSize{d}
    {
    }
  };

  Info dfs(TreeNode *x)
  {
    if (x == nullptr)
    {
      return Info(numeric_limits<long long>::min(),
                  numeric_limits<long long>::max(),
                  true, 0);
    }

    Info l = dfs(x->left), r = dfs(x->right);

    // 左 4信息
    // 右 4信息
    // x 整合出4信息返回
    long long max_val = max({static_cast<long long>(x->val), l.max, r.max});
    long long min_val = min({static_cast<long long>(x->val), l.min, r.min});
    bool isBst = l.isBst && r.isBst && (l.max < x->val && r.min > x->val);
    int maxBstSize = isBst ? (l.maxBstSize + r.maxBstSize + 1) : (max(l.maxBstSize, r.maxBstSize));

    return Info(max_val, min_val, isBst, maxBstSize);
  }
};