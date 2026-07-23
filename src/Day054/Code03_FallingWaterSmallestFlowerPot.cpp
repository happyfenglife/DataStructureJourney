// 接取落水的最小花盆
// 老板需要你帮忙浇花。给出 N 滴水的坐标，y 表示水滴的高度，x 表示它下落到 x 轴的位置
// 每滴水以每秒1个单位长度的速度下落。你需要把花盆放在 x 轴上的某个位置
// 使得从被花盆接着的第 1 滴水开始，到被花盆接着的最后 1 滴水结束，之间的时间差至少为 D
// 我们认为，只要水滴落到 x 轴上，与花盆的边沿对齐，就认为被接住
// 给出 N 滴水的坐标和 D 的大小，请算出最小的花盆的宽度 W
// 测试链接 : https://www.luogu.com.cn/problem/P2698
#include <iostream>
#include <vector>
#include <array>
#include <limits>
#include <algorithm>
using namespace std;

constexpr int MAXN = 100005;

vector<int> maxDeque(MAXN);
vector<int> minDeque(MAXN);

vector<array<int, 2>> arr(MAXN);

int maxh, maxt, minh, mint;

int N, D, W;

// 当前窗口 最大值 - 最小值 是不是>=d
bool ok()
{
  int maxVal = maxh < maxt ? arr[maxDeque[maxh]][1] : 0;
  int minVal = minh < mint ? arr[minDeque[minh]][1] : 0;

  return maxVal - minVal >= D;
}

void push(int r)
{
  while (maxh < maxt && arr[maxDeque[maxt - 1]][1] <= arr[r][1])
  {
    --maxt;
  }
  maxDeque[maxt++] = r;

  while (minh < mint && arr[minDeque[mint - 1]][1] >= arr[r][1])
  {
    --mint;
  }
  minDeque[mint++] = r;
}

void pop(int l)
{
  if (maxh < maxt && maxDeque[maxh] == l)
  {
    maxh++;
  }

  if (minh < mint && minDeque[minh] == l)
  {
    minh++;
  }
}

void compute()
{
  // arr[0...n-1][2]: x(0), 高度(1)
  // 所有水滴根据x排序，谁小谁在前
  sort(arr.begin(), arr.begin() + N, [](auto &a, auto &b)
       { return a[0] < b[0]; });

  for (int l = 0, r = 0; l < N; l++)
  {
    // [l,r) : 水滴的编号
    // l : 当前花盘的左边界，arr[l][0]
    while (!ok() && r < N)
    {
      push(r++);
    }

    if (ok())
    {
      W = min(W, arr[r - 1][0] - arr[l][0]);
    }
    pop(l);
  }
}

int main()
{
  while (cin >> N >> D)
  {
    for (int i = 0; i < N; i++)
    {
      cin >> arr[i][0] >> arr[i][1];
    }

    maxh = maxt = minh = mint = 0;
    W = numeric_limits<int>::max();
    compute();
    cout << (W == numeric_limits<int>::max() ? -1 : W) << '\n';
  }

  return 0;
}