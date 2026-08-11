// 线段树同时支持范围重置、范围增加、范围查询
// 维护最大值
// 测试链接 : https://www.luogu.com.cn/problem/P1253
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

constexpr int MAXN = 1E6 + 1;

ll arr[MAXN];
ll rangeMax[MAXN << 2];
ll add[MAXN << 2];
ll change[MAXN << 2];
bool update[MAXN << 2];

int n, m;

void up(int i)
{
  rangeMax[i] = max(rangeMax[i << 1],
                    rangeMax[i << 1 | 1]);
}

void updateLazy(int i, ll v)
{
  rangeMax[i] = v;
  add[i] = 0;
  change[i] = v;
  update[i] = true;
}

void addLazy(int i, ll v)
{
  rangeMax[i] += v;
  add[i] += v;
}

void down(int i)
{
  if (update[i])
  {
    updateLazy(i << 1, change[i]);
    updateLazy(i << 1 | 1, change[i]);
    update[i] = false;
  }
  if (add[i])
  {
    addLazy(i << 1, add[i]);
    addLazy(i << 1 | 1, add[i]);
    add[i] = 0;
  }
}

void rangeAdd(int jobl, int jobr, ll jobv, int l, int r, int i)
{
  if (jobl <= l && r <= jobr)
  {
    addLazy(i, jobv);
  }
  else
  {
    int m = (l + r) >> 1;
    down(i);
    if (jobl <= m)
    {
      rangeAdd(jobl, jobr, jobv, l, m, i << 1);
    }
    if (jobr > m)
    {
      rangeAdd(jobl, jobr, jobv, m + 1, r, i << 1 | 1);
    }

    up(i);
  }
}

void rangeUpdate(int jobl, int jobr, ll jobv, int l, int r, int i)
{
  if (jobl <= l && r <= jobr)
  {
    updateLazy(i, jobv);
  }
  else
  {
    int m = (l + r) >> 1;
    down(i);
    if (jobl <= m)
    {
      rangeUpdate(jobl, jobr, jobv, l, m, i << 1);
    }
    if (jobr > m)
    {
      rangeUpdate(jobl, jobr, jobv, m + 1, r, i << 1 | 1);
    }

    up(i);
  }
}

ll query(int jobl, int jobr, int l, int r, int i)
{
  if (jobl <= l && r <= jobr)
  {
    return rangeMax[i];
  }

  int m = (l + r) >> 1;
  down(i);
  ll ans{LLONG_MIN};
  if (jobl <= m)
  {
    ans = max(ans, query(jobl, jobr, l, m, i << 1));
  }
  if (jobr > m)
  {
    ans = max(ans, query(jobl, jobr, m + 1, r, i << 1 | 1));
  }

  return ans;
}

void build(int l, int r, int i)
{
  if (l == r)
  {
    rangeMax[i] = arr[l];
  }
  else
  {
    int m = (l + r) >> 1;
    build(l, m, i << 1);
    build(m + 1, r, i << 1 | 1);
    up(i);
  }
}

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  while (cin >> n >> m)
  {
    for (int i = 1; i <= n; i++)
    {
      cin >> arr[i];
    }

    build(1, n, 1);
    ll jobv;
    for (int i = 1, op, jobl, jobr; i <= m; i++)
    {
      cin >> op;
      if (op == 1)
      {
        cin >> jobl >> jobr >> jobv;
        rangeUpdate(jobl, jobr, jobv, 1, n, 1);
      }
      else if (op == 2)
      {
        cin >> jobl >> jobr >> jobv;
        rangeAdd(jobl, jobr, jobv, 1, n, 1);
      }
      else
      {
        cin >> jobl >> jobr;
        cout << query(jobl, jobr, 1, n, 1) << '\n';
      }
    }
  }

  return 0;
}