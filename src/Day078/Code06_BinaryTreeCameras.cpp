// 监控二叉树
// 给定一个二叉树，我们在树的节点上安装摄像头
// 节点上的每个摄影头都可以监视其父对象、自身及其直接子对象
// 计算监控树的所有节点所需的最小摄像头数量
// 测试链接 : https://leetcode.cn/problems/binary-tree-cameras/
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

  int minCameraCover(TreeNode *root)
  {
    ans = 0;
    if (dfs(root) == State::UNCOVERED)
    {
      ++ans;
    }

    return ans;
  }

  // 使用强类型枚举表示节点状态（替代原来的 int 返回值：0/1/2）
  // 返回值含义（与原实现语义一致）：
  // UNCOVERED (原 0): x 是无覆盖的状态，x 下方的节点都已经被覆盖
  // COVERED_NO_CAMERA (原 1): x 是覆盖状态，x 上没摄像头，x 下方的节点都已经被覆盖
  // HAS_CAMERA (原 2): x 是覆盖状态，x 上有摄像头，x 下方的节点都已经被覆盖
  enum State
  {
    UNCOVERED = 0,
    COVERED_NO_CAMERA = 1,
    HAS_CAMERA = 2
  };

  // 递归含义
  // 假设 x 上方一定有父亲的情况下，这个假设很重要
  // x 为头的整棵树，最终想都覆盖，
  // 并且想使用最少的摄像头，x 应该是什么样的状态
  State dfs(TreeNode *x)
  {
    if (x == nullptr)
    {
      return State::COVERED_NO_CAMERA;
    }

    State l = dfs(x->left), r = dfs(x->right);
    if (l == State::UNCOVERED || r == State::UNCOVERED)
    {
      ans++;
      return State::HAS_CAMERA;
    }

    if (l == State::COVERED_NO_CAMERA &&
        r == State::COVERED_NO_CAMERA)
    {
      return State::UNCOVERED;
    }

    return State::COVERED_NO_CAMERA;
  }
};