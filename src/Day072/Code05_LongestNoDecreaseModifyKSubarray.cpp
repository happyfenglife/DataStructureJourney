// 有一次修改机会的最长不下降子序列
// 给定一个长度为n的数组arr，和一个整数k
// 只有一次机会可以将其中连续的k个数全修改成任意一个值
// 这次机会你可以用也可以不用，请返回最长不下降子序列长度
// 1 <= k, n <= 10^5
// 1 <= arr[i] <= 10^6
// 测试链接 : https://www.luogu.com.cn/problem/P8776
#include <bits/stdc++.h>
using namespace std;

constexpr int MAXN = 100001;

int arr[MAXN];
int tails[MAXN];
int rights[MAXN];

int N, K;

// 求最长不上升子序列长度的二分
// tails[0...len-1]是降序的，找到<num的最左位置
// 不存在返回-1
int bs1(int len, int num)
{
  int l = 0, r = len - 1, m, ans = -1;
  while (l <= r)
  {
    m = l + (r - l) / 2;
    if (tails[m] < num)
    {
      ans = m;
      r = m - 1;
    }
    else
    {
      l = m + 1;
    }
  }

  return ans;
}

// 求最长不下降子序列长度的二分
// tails[0...len-1]是升序的，找到>num的最左位置
// 不存在返回-1
int bs2(int len, int num)
{
  int l = 0, r = len - 1, m, ans = -1;
  while (l <= r)
  {
    m = l + (r - l) / 2;
    if (tails[m] > num)
    {
      ans = m;
      r = m - 1;
    }
    else
    {
      l = m + 1;
    }
  }

  return ans;
}

// 生成辅助数组right
// right[j] :
// 一定以arr[j]做开头的情况下，arr[j...]上最长不下降子序列长度是多少
// 关键逻辑 :
// 一定以arr[i]做开头的情况下，arr[i...]上最长不下降子序列
// 就是！从n-1出发来看(从右往左遍历)，以arr[i]做结尾的情况下的最长不上升子序列
void process()
{
  int len = 0;
  for (int i = N - 1, pos; i >= 0; i--)
  {
    pos = bs1(len, arr[i]);
    if (pos == -1)
    {
      tails[len++] = arr[i];
      rights[i] = len;
    }
    else
    {
      tails[pos] = arr[i];
      rights[i] = pos + 1;
    }
  }
}

int compute()
{
  process();
  int len = 0;
  int ans = 0;
  for (int i = 0, pos, l, j = K; j < N; i++, j++)
  {
    pos = bs2(len, arr[j]);
    l = (pos == -1) ? len : pos;
    ans = max(ans, l + K + rights[j]);
    pos = bs2(len, arr[i]);
    if (pos == -1)
    {
      tails[len++] = arr[i];
    }
    else
    {
      tails[pos] = arr[i];
    }
  }

  ans = max(ans, len + K);
  return ans;
}

int main()
{
  while (cin >> N >> K)
  {
    for (int i = 0; i < N; i++)
    {
      cin >> arr[i];
    }

    if (K >= N)
    {
      cout << K << '\n';
    }
    else
    {
      cout << compute() << '\n';
    }
  }

  return 0;
}