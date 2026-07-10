// 二叉树的直径
// 给你一棵二叉树的根节点，返回该树的直径
// 二叉树的 直径 是指树中任意两个节点之间最长路径的长度
// 这条路径可能经过也可能不经过根节点 root
// 两节点之间路径的 长度 由它们之间边数表示
// 测试链接 : https://leetcode.cn/problems/diameter-of-binary-tree/
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

    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right)
        : val(x), left(left), right(right) {}
  };

  int diameterOfBinaryTree(TreeNode *root)
  {
    return dfs(root).diameter;
  }

  struct Info
  {
    int diameter;
    int height;

    Info(int a, int b)
        : diameter{a}, height{b}
    {
    }
  };

  Info dfs(TreeNode *x)
  {
    if (x == nullptr)
    {
      return Info(0, 0);
    }

    Info l = dfs(x->left), r = dfs(x->right);
    int height = max(l.height, r.height) + 1;
    int diameter = max(l.diameter, r.diameter);
    diameter = max(diameter, l.height + r.height);

    return Info(height, diameter);
  }
};
