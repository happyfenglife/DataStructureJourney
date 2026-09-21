// 异或关系
// 一共n个数，编号0 ~ n-1，实现如下三种类型的操作，一共调用m次
// I x v        : 声明 第x个数 = v
// I x y v      : 声明 第x个数 ^ 第y个数 = v
// Q k a1 .. ak : 查询 一共k个数，编号为a1 .. ak，这些数字异或起来的值是多少
// 对每个Q的操作打印答案，如果根据之前的声明无法推出答案，打印"I don't know."
// 如果处理到第s条声明，发现了矛盾，打印"The first s facts are conflicting."
// 注意只有声明操作出现，s才会增加，查询操作不占用声明操作的计数
// 发现矛盾之后，所有的操作都不再处理，更多的细节可以打开测试链接查看题目
// 1 <= n <= 20000    1 <= m <= 40000    1 <= k <= 15
// 测试链接 : https://acm.hdu.edu.cn/showproblem.php?pid=3234
// 测试链接 : https://www.luogu.com.cn/problem/UVA12232
// 测试链接 : https://vjudge.net/problem/UVA-12232
#include <bits/stdc++.h>
using namespace std;

constexpr int MAXN = 2E4 + 2;
constexpr int MAXK = 21;

int cnti;
bool conflict;
int n, m, t;
char op;

vector<int> father(MAXN);
vector<int> exclu(MAXN);
vector<int> nums(MAXK);
vector<int> fas(MAXK);

void prepare()
{
  conflict = false;
  cnti = 0;
  for (int i = 0; i <= n; i++)
  {
    father[i] = i;
    exclu[i] = 0;
  }
}

int find(int i)
{
  if (i != father[i])
  {
    int tmp = father[i];
    father[i] = find(tmp);
    exclu[i] ^= exclu[tmp];
  }

  return father[i];
}

bool opi(int l, int r, int v)
{
  cnti++;
  int lf = find(l), rf = find(r);
  if (lf == rf)
  {
    if ((exclu[l] ^ exclu[r]) != v)
    {
      conflict = true;
      return false;
    }
  }
  else
  {
    if (lf == n)
    {
      lf = rf;
      rf = n;
    }

    father[lf] = rf;
    exclu[lf] = exclu[r] ^ exclu[l] ^ v;
  }

  return true;
}

// 查询 a1 ^ a2 ^ ... ^ ak，无法确定返回 -1
int opq(int k)
{
  int ans = 0;
  for (int i = 1; i <= k; i++)
  {
    int fa = find(nums[i]);
    ans ^= exclu[nums[i]];
    fas[i] = fa;
  }

  sort(fas.begin() + 1, fas.begin() + 1 + k);
  // 若某个根出现奇数次，且它不是固定根 n，则该根对应的值无法消去 -> 无法确定
  for (int l = 1, r = 1; l <= k; l = ++r)
  {
    while (r + 1 <= k && fas[r + 1] == fas[l])
      ++r;

    if ((r - l + 1) % 2 && fas[l] != n)
      return -1;
  }

  return ans;
}

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  t = 0;
  string line;
  while (getline(cin, line))
  {
    if (line.empty())
      continue;

    istringstream iss(line);
    if (!(iss >> n >> m))
      continue;

    if (!n && !m)
      break;

    prepare();
    cout << "Case " << (++t) << ":\n";
    for (int i = 1; i <= m; i++)
    {
      do
      {
        getline(cin, line);
      } while (line.empty() && !cin.eof());

      istringstream ss(line);
      ss >> op;
      if (op == 'I')
      {
        vector<int> vals;
        int x;
        while (ss >> x)
          vals.push_back(x);

        if (!conflict)
        {
          if (vals.size() == 2)
          {
            if (!opi(vals[0], n, vals[1]))
            {
              cout << "The first " << cnti << " facts are conflicting.\n";
            }
          }
          else
          {
            if (!opi(vals[0], vals[1], vals[2]))
            {
              cout << "The first " << cnti << " facts are conflicting.\n";
            }
          }
        }
      }
      else
      {
        int k;
        ss >> k;
        for (int j = 1; j <= k; j++)
          ss >> nums[j];

        if (!conflict)
        {
          int ans = opq(k);
          if (ans == -1)
            cout << "I don't know.\n";
          else
            cout << ans << '\n';
        }
      }
    }

    cout << '\n';
  }

  return 0;
}