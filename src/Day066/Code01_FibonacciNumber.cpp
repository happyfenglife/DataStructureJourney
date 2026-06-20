// 斐波那契数
// 斐波那契数 （通常用 F(n) 表示）形成的序列称为 斐波那契数列
// 该数列由 0 和 1 开始，后面的每一项数字都是前面两项数字的和。
// 也就是：F(0) = 0，F(1) = 1
// F(n) = F(n - 1) + F(n - 2)，其中 n > 1
// 给定 n ，请计算 F(n)
// 测试链接 : https://leetcode.cn/problems/fibonacci-number/
#include <vector>
using namespace std;

class Solution
{
public:
  // 1. 暴力递归
  int fib1(int n) {
    return f1(n);
  }

  int f1(int i) {
    if (i == 0) return 0;
    if (i == 1) return 1;
    return f1(i - 1) + f1(i - 2);
  }

  // 2. 记忆化搜索
  int fib2(int n) {
    vector<int> dp(n + 1, -1);
    return f2(n, dp);
  }

  int f2(int i, vector<int>& dp) {
    if (i == 0) return 0;
    if (i == 1) return 1;
    if (dp[i] != -1) return dp[i];

    int ans = f2(i - 1, dp) + f2(i - 2, dp);
    dp[i] = ans;
    return dp[i];
  }

  // 3. 动态规划
  int fib3(int n) {
    if (n == 0) return 0;
    if (n == 1) return 1;
    vector<int> dp(n + 1, 0);
    dp[1] = 1;
    for (int i = 2; i <= n; i++) {
      dp[i] = dp[i - 1] + dp[i - 2];
    }

    return dp[n];
  }

  // 4. 空间优化动态规划
  int fib4(int n) {
    if (n == 0) return 0;
    if (n == 1) return 1;

    int lastLast = 0, last = 1;
    for (int i = 2, cur; i <= n; i++) {
      cur = lastLast + last;
      lastLast = last;
      last = cur;
    }

    return last;
  }
};
