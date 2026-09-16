// 团伙
// 注意洛谷关于本题的描述有问题，请按照如下的描述来理解题意
// 一共有n个黑帮成员，编号1 ~ n，发现了m条事实，每条事实一定属于如下两种类型中的一种
// F l r : l号成员和r号成员是朋友
// E l r : l号成员和r号成员是敌人
// 黑帮遵守如下的约定，敌人的敌人一定是朋友，朋友都来自同一个黑帮，敌人一定不是同一个黑帮
// 如果根据事实无法推断出一个成员有哪些朋友，那么该成员自己是一个黑帮
// 输入数据不存在矛盾，也就是任何两人不会推出既是朋友又是敌人的结论
// 遵守上面的约定，根据m条事实，计算黑帮有多少个
// 1 <= n <= 1000    1 <= m <= 5000
// 测试链接 : https://www.luogu.com.cn/problem/P1892
#include <bits/stdc++.h>
using namespace std;

constexpr int MAXN = 1001;

vector<int> father(MAXN);
vector<int> enemy(MAXN);

int n, m;
char op;

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

int main()
{
  cin >> n >> m;
  prepare();
  for (int i = 1, l, r; i <= m; i++)
  {
    cin >> op >> l >> r;
    if (op == 'F')
    {
      unionSet(l, r);
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

  int ans = 0;
  for (int i = 1; i <= n; i++)
  {
    if (father[i] == i)
    {
      ++ans;
    }
  }

  cout << ans << endl;

  return 0;
}