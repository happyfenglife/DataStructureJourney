// 用固定数组实现前缀树，空间使用是静态的。推荐！
// 测试链接 : https://www.nowcoder.com/practice/7f8a8553ddbf4eaab749ec988726702b
#include <bits/stdc++.h>
using namespace std;

constexpr int MAXN = 150001;
int tree[MAXN][26];
int endd[MAXN];
int pass[MAXN];
int cnt;

void build()
{
  cnt = 1;
}

void insert(string &word)
{
  int cur = 1;
  pass[cur]++;
  for (int i = 0, path; i < word.size(); i++)
  {
    path = word[i] - 'a';
    if (!tree[cur][path])
    {
      tree[cur][path] = ++cnt;
    }

    cur = tree[cur][path];
    pass[cur]++;
  }

  endd[cur]++;
}

int search(string &word)
{
  int cur = 1;
  for (int i = 0, path; i < word.size(); i++)
  {
    path = word[i] - 'a';
    if (!tree[cur][path])
    {
      return 0;
    }

    cur = tree[cur][path];
  }

  return endd[cur];
}

int prefixNumber(string &pre)
{
  int cur{1};
  for (int i = 0, path; i < pre.size(); i++)
  {
    path = pre[i] - 'a';
    if (!tree[cur][path])
    {
      return 0;
    }

    cur = tree[cur][path];
  }

  return pass[cur];
}

void deleteWord(string &word)
{
  if (search(word) > 0)
  {
    int cur = 1;
    pass[cur]--;
    for (int i = 0, path; i < word.size(); i++)
    {
      path = word[i] - 'a';
      if (--pass[tree[cur][path]] == 0)
      {
        tree[cur][path] = 0;
        return;
      }

      cur = tree[cur][path];
    }

    endd[cur]--;
  }
}

void clear()
{
  for (int i = 1; i <= cnt; i++)
  {
    memset(tree[i], 0, sizeof(tree[i]));
    endd[i] = 0;
    pass[i] = 0;
  }
}
int main()
{
  int m, op;
  string word;
  while (cin >> m)
  {
    build();
    for (int i = 1; i <= m; i++)
    {
      cin >> op >> word;
      if (op == 1)
      {
        insert(word);
      }
      else if (op == 2)
      {
        deleteWord(word);
      }
      else if (op == 3)
      {
        cout << (search(word) > 0 ? "YES" : "NO") << '\n';
      }
      else if (op == 4)
      {
        cout << prefixNumber(word) << '\n';
      }
    }

    clear();
  }

  return 0;
}