// 节点数为n高度不大于m的二叉树个数
// 现在有n个节点，计算出有多少个不同结构的二叉树
// 满足节点个数为n且树的高度不超过m的方案
// 因为答案很大，所以答案需要模上1000000007后输出
// 测试链接 : https://www.nowcoder.com/practice/aaefe5896cce4204b276e213e725f3ea
#include <vector>
#include <iostream>
#include <cstring>
using namespace std;

const int MAXN = 55;
const int MOD = 1e9 + 7;

long long dp1[MAXN][MAXN];
long long dp2[MAXN][MAXN];
long long dp3[MAXN];

// 记忆化搜索
long long compute1(int n, int m)
{
  if (n == 0)
  {
    return 1;
  }

  if (m == 0)
  {
    return 0;
  }

  if (dp1[n][m] != -1)
  {
    return dp1[n][m];
  }

  long long ans = 0;
  for (int k = 0; k < n; k++)
  {
    ans = (ans + compute1(k, m - 1) * compute1(n - 1 - k, m - 1)) % MOD;
  }

  dp1[n][m] = ans;
  return ans;
}

// 严格位置依赖的动态规划
int compute2(int n, int m)
{
  for (int j = 0; j <= m; j++)
  {
    dp2[0][j] = 1;
  }

  for (int i = 1; i <= n; i++)
  {
    for (int j = 1; j <= m; j++)
    {
      dp2[i][j] = 0;
      for (int k = 0; k < i; k++)
      {
        dp2[i][j] = (dp2[i][j] + dp2[k][j - 1] * dp2[i - 1 - k][j - 1]) % MOD;
      }
    }
  }

  return dp2[n][m];
}

int compute3(int n, int m)
{
  memset(dp3, 0, sizeof(dp3));
  dp3[0] = 1;
  for (int j = 1; j <= m; j++)
  {
    for (int i = n; i >= 1; i--)
    {
      dp3[i] = 0;
      for (int k = 0; k < i; k++)
      {
        dp3[i] = (dp3[i] + dp3[k] * dp3[i - 1 - k]) % MOD;
      }
    }
  }

  return (int)dp3[n];
}

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  for (int i = 0; i < MAXN; i++)
  {
    for (int j = 0; j < MAXN; j++)
    {
      dp1[i][j] = -1;
    }
  }

  int n, m;
  while (cin >> n >> m)
  {
    cout << compute3(n, m) << '\n';
  }

  return 0;
}
