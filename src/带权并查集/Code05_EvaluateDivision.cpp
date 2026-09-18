// 除法求值
// 所有变量都用字符串表示，并且给定若干组等式
// 比如等式
// ["ab", "ef"] = 8，代表ab / ef = 8
// ["ct", "ef"] = 2，代表ct / ef = 2
// 所有等式都是正确的并且可以进行推断，给定所有等式之后，会给你若干条查询
// 比如查询，["ab", "ct"]，根据上面的等式推断，ab / ct = 4
// 如果某条查询中的变量，从来没在等式中出现过，认为答案是-1.0
// 如果某条查询的答案根本推断不出来，认为答案是-1.0
// 返回所有查询的答案
// 测试链接 : https://leetcode.cn/problems/evaluate-division/
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
  vector<double> calcEquation(vector<vector<string>> &eqs, vector<double> &values, vector<vector<string>> &queries)
  {
    prepare(eqs);

    for (int i = 0; i < eqs.size(); i++)
    {
      unionSet(eqs[i][0], eqs[i][1], values[i]);
    }

    vector<double> ans(queries.size());
    for (int i = 0; i < queries.size(); i++)
    {
      ans[i] = query(queries[i][0], queries[i][1]);
    }

    return ans;
  }

  unordered_map<string, string> father;

  unordered_map<string, double> dist;

  void prepare(vector<vector<string>> &v)
  {
    father.clear();
    dist.clear();
    for (auto &eq : v)
    {
      for (auto &s : eq)
      {
        father[s] = s;
        dist[s] = 1.0;
      }
    }
  }

  string find(string &s)
  {
    if (!father.contains(s))
    {
      return "";
    }

    string tmp, fa = s;
    if (s != father[s])
    {
      tmp = father[s];
      fa = find(tmp);
      dist[s] = dist[s] * dist[tmp];
      father[s] = fa;
    }

    return fa;
  }

  void unionSet(string &l, string &r, double v)
  {
    string lf = find(l), rf = find(r);
    if (lf != rf)
    {
      father[lf] = rf;
      dist[lf] = dist[r] * v / dist[l];
    }
  }

  double query(string &l, string &r)
  {
    string lf = find(l), rf = find(r);
    if (lf.empty() || rf.empty() || lf != rf)
    {
      return -1.0;
    }

    return dist[l] / dist[r];
  }
};