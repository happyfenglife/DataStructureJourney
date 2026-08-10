// 线段树支持范围重置、范围查询
// 维护累加和
// 对数器验证
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

constexpr int MAXN = 1E5 + 1;
ll arr[MAXN];
ll sum[MAXN << 2];
ll change[MAXN << 2];
bool update[MAXN << 2];

void up(int i)
{
  sum[i] = sum[i << 1] + sum[i << 1 | 1];
}

void lazy(int i, ll v, int n)
{
  sum[i] = v * n;
  change[i] = v;
  update[i] = true;
}

void down(int i, int ln, int rn)
{
  if (update[i])
  {
    lazy(i << 1, change[i], ln);
    lazy(i << 1 | 1, change[i], rn);
    update[i] = false;
  }
}

void rangeUpdate(int jobl, int jobr, long jobv, int l, int r, int i)
{
  if (jobl <= l && r <= jobr)
  {
    lazy(i, jobv, r - l + 1);
  }
  else
  {
    int mid = (l + r) >> 1;
    down(i, mid - l + 1, r - mid);
    if (jobl <= mid)
    {
      rangeUpdate(jobl, jobr, jobv, l, mid, i << 1);
    }
    if (jobr > mid)
    {
      rangeUpdate(jobl, jobr, jobv, mid + 1, r, i << 1 | 1);
    }

    up(i);
  }
}

ll query(int jobl, int jobr, int l, int r, int i)
{
  if (jobl <= l && r <= jobr)
  {
    return sum[i];
  }

  int mid = (l + r) >> 1;
  down(i, mid - l + 1, r - mid);
  ll ans{};
  if (jobl <= mid)
  {
    ans += query(jobl, jobr, l, mid, i << 1);
  }
  if (jobr > mid)
  {
    ans += query(jobl, jobr, mid + 1, r, i << 1 | 1);
  }

  return ans;
}

void build(int l, int r, int i)
{
  if (l == r)
  {
    sum[i] = arr[l];
  }
  else
  {
    int mid = (l + r) >> 1;
    build(l, mid, i << 1);
    build(mid + 1, r, i << 1 | 1);
    up(i);
  }

  change[i] = 0;
  update[i] = false;
}

// 生成随机值填入 arr 数组
void randomArray(int n, int v, mt19937 &rng)
{
  uniform_int_distribution<int> dist(0, max(0, v - 1));
  for (int i = 1; i <= n; ++i)
  {
    arr[i] = dist(rng);
  }
}

// 验证结构的更新（暴力更新）
void checkUpdate(vector<ll> &check, int jobl, int jobr, ll jobv)
{
  for (int i = jobl; i <= jobr; ++i)
  {
    check[i] = jobv;
  }
}

// 验证结构的查询（暴力查询）
ll checkQuery(vector<ll> &check, int jobl, int jobr)
{
  ll ans = 0;
  for (int i = jobl; i <= jobr; ++i)
  {
    ans += check[i];
  }

  return ans;
}

// 对数器逻辑
// 展示了线段树的建立和使用
// 使用验证结构来检查线段树是否正常工作
int main()
{
  cout << "测试开始..." << endl;
  int n = 1000;
  int v = 2000;
  int t = 50000;

  // 随机数生成器
  mt19937 rng((unsigned)chrono::high_resolution_clock::now().time_since_epoch().count());

  // 生成随机值填入 arr 数组
  randomArray(n, v, rng);

  // 建立线段树
  build(1, n, 1);
  // 生成验证的结构
  vector<ll> check(n + 1);
  for (int i = 1; i <= n; i++)
  {
    check[i] = arr[i];
  }

  uniform_int_distribution<int> opDist(0, 1);
  uniform_int_distribution<int> idxDist(1, n);
  uniform_int_distribution<int> valDist(-v, v - 1); // jobv in [-v, v-1]

  for (int i = 1; i <= t; ++i)
  {
    int op = opDist(rng);
    int a = idxDist(rng);
    int b = idxDist(rng);
    int jobl = min(a, b);
    int jobr = max(a, b);
    if (op == 0)
    {
      int jobv = valDist(rng);
      rangeUpdate(jobl, jobr, jobv, 1, n, 1);
      checkUpdate(check, jobl, jobr, jobv);
    }
    else
    {
      ll ans1 = query(jobl, jobr, 1, n, 1);
      ll ans2 = checkQuery(check, jobl, jobr);
      if (ans1 != ans2)
      {
        cout << "出错了!" << '\n';
        // 如果想查看细节可以打印并退出
        cout << "range: [" << jobl << ", " << jobr << "]\n";
        cout << "segAns = " << ans1 << ", bruteAns = " << ans2 << '\n';
        return 0;
      }
    }
  }

  cout << "测试结束" << '\n';
  return 0;
}