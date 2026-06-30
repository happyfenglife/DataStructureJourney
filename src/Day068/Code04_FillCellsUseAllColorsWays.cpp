// 有效涂色问题
// 给定n、m两个参数
// 一共有n个格子，每个格子可以涂上一种颜色，颜色在m种里选
// 当涂满n个格子，并且m种颜色都使用了，叫一种有效方法
// 求一共有多少种有效的涂色方法
// 1 <= n, m <= 5000
// 结果比较大请 % 1000000007 之后返回
// 对数器验证
#include <iostream>
#include <vector>
#include <chrono>
using namespace std;

const int MAXN = 5001;
const int MOD = 1e9 + 7;

int dp[MAXN][MAXN];

int dfs(vector<int> &path, vector<bool> &used, int idx, int n, int m)
{
  if (idx == n)
  {
    fill(used.begin(), used.end(), false);
    int colors = 0;
    for (int c : path)
    {
      if (!used[c])
      {
        used[c] = true;
        ++colors;
      }
    }

    return (colors == m) ? 1 : 0;
  }

  int ans = 0;
  for (int color = 1; color <= m; color++)
  {
    path[idx] = color;
    ans += dfs(path, used, idx + 1, n, m);
  }

  return ans;
}

// 暴力尝试
int ways1(int n, int m)
{
  vector<int> path(n, 0);
  vector<bool> used(m + 1, false);
  return dfs(path, used, 0, n, m);
}

// ---------- 正式动态规划方法 ----------
// dp[i][j] : 前 i 个格子涂满 j 种颜色的方法数（共有 m 种颜色）
// 时间复杂度 O(n*m)，空间 O(n*m)
int ways2(int n, int m)
{
  for (int i = 1; i <= n; i++)
  {
    dp[i][1] = m;
  }

  for (int i = 2; i <= n; i++)
  {
    for (int j = 2; j <= m; j++)
    {
      long long val = 1LL * dp[i - 1][j] * j % MOD;
      val = (val + 1LL * dp[i - 1][j - 1] * (m - j + 1)) % MOD;
      dp[i][j] = (int)val;
    }
  }

  return dp[n][m];
}

int main()
{
  int N = 4, M = 4;
  cout << "功能测试开始" << endl;
  for (int n = 1; n <= N; ++n)
  {
    for (int m = 1; m <= M; ++m)
    {
      int ans1 = ways1(n, m);
      int ans2 = ways2(n, m);
      if (ans1 != ans2)
      {
        cout << "出错了！ n=" << n << ", m=" << m
             << " ans1=" << ans1 << " ans2=" << ans2 << endl;
      }
    }
  }
  cout << "功能测试结束" << endl;

  // 性能测试
  cout << "性能测试开始" << endl;
  int n = 5000, m = 4877;
  cout << "n : " << n << endl;
  cout << "m : " << m << endl;

  auto start = chrono::high_resolution_clock::now();
  int ans = ways2(n, m);
  auto end = chrono::high_resolution_clock::now();
  auto duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();

  cout << "取模之后的结果 : " << ans << endl;
  cout << "运行时间 : " << duration << " 毫秒" << endl;
  cout << "性能测试结束" << endl;

  return 0;
}