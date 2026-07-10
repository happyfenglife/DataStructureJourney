// 在二叉树中分配硬币
// 给你一个有 n 个结点的二叉树的根结点 root
// 其中树中每个结点 node 都对应有 node.val 枚硬币
// 整棵树上一共有 n 枚硬币
// 在一次移动中，我们可以选择两个相邻的结点，然后将一枚硬币从其中一个结点移动到另一个结点
// 移动可以是从父结点到子结点，或者从子结点移动到父结点
// 返回使每个结点上 只有 一枚硬币所需的 最少 移动次数
// 测试链接 : https://leetcode.cn/problems/distribute-coins-in-binary-tree/
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

  struct Info
  {
    int cnt;
    int sum;
    int move;

    Info(int a, int b, int c)
        : cnt{a}, sum{b}, move{c}
    {
    }
  };

  int distributeCoins(TreeNode *root)
  {
    return dfs(root).move;
  }

  Info dfs(TreeNode *x)
  {
    if (x == nullptr)
    {
      return Info(0, 0, 0);
    }

    Info l = dfs(x->left), r = dfs(x->right);
    int cnts = l.cnt + r.cnt + 1;
    int sums = l.sum + r.sum + x->val;
    int moves = l.move + r.move
    + abs(l.cnt - l.sum) + abs(r.cnt - r.sum);

    return Info(cnts, sums, moves);
  }
};