// 关押罪犯
// 一共有n个犯人，编号1 ~ n，一共有两个监狱，你可以决定每个犯人去哪个监狱
// 给定m条记录，每条记录 l r v，表示l号犯人和r号犯人的仇恨值
// 每个监狱的暴力值 = 该监狱中仇恨最深的犯人之间的仇恨值
// 冲突值 = max(第一座监狱的暴力值，第二座监狱的暴力值)
// 犯人的分配方案需要让这个冲突值最小，返回最小能是多少
// 1 <= n <= 20000    1 <= m <= 100000    1 <= 仇恨值 <= 10^9
// 测试链接 : https://www.luogu.com.cn/problem/P1525
#include <bits/stdc++.h>
using namespace std;

constexpr int MAXN = 2E4 + 2;
constexpr int MAXM = 1E5 + 1;

vector<int> father(MAXN);
vector<int> enemy(MAXN);
vector<vector<int>> arr(MAXM, vector<int>(3));

int n, m;

void prepare()
{
  for (int i = 1; i <= n; i++)
  {
    father[i] = i;
    enemy[i] = 0;
  }
}

int find(int i)
{
  father[i] = (i == father[i] ? i : find(father[i]));
  return father[i];
}

void unionSet(int l, int r)
{
  father[find(l)] = find(r);
}

bool same(int l, int r)
{
  return find(l) == find(r);
}

int compute()
{
  sort(arr.begin() + 1, arr.begin() + m + 1, [](auto &a, auto &b)
       { return a[2] > b[2]; });
  int ans = 0;
  for (int i = 1, l, r, v; i <= m; i++)
  {
    l = arr[i][0];
    r = arr[i][1];
    v = arr[i][2];

    if (same(l, r))
    {
      ans = v;
      break;
    }
    else
    {
      if (enemy[l])
      {
        unionSet(enemy[l], r);
      }
      else
      {
        enemy[l] = r;
      }

      if (enemy[r])
      {
        unionSet(enemy[r], l);
      }
      else
      {
        enemy[r] = l;
      }
    }
  }

  return ans;
}

int main()
{
  cin >> n >> m;
  prepare();
  for (int i = 1; i <= m; i++)
  {
    cin >> arr[i][0] >> arr[i][1] >> arr[i][2];
  }

  cout << compute() << endl;
  return 0;
}