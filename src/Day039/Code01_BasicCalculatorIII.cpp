// 含有嵌套的表达式求值
// 测试链接 : https://www.nowcoder.com/practice/c215ba61c8b1443b996351df929dc4d4
#include <string>
#include <vector>
using namespace std;

class Solution
{
private:
  int f(const string &s, int i)
  {
    int cur = 0;
    vector<int> numbers;
    vector<char> ops;

    while (i < s.size() && s[i] != ')')
    {
      if (s[i] >= '0' && s[i] <= '9')
      {
        cur = cur * 10 + (s[i++] - '0');
      }
      else if (s[i] != '(')
      {
        push(numbers, ops, cur, s[i++]);
        cur = 0;
      }
      else
      {
        cur = f(s, i + 1);
        i = where + 1;
      }
    }

    push(numbers, ops, cur, '+');
    where = i;
    return compute(numbers, ops);
  }

  void push(vector<int> &numbers, vector<char> &ops, int cur, int op)
  {
    int n = numbers.size();
    if (n == 0 || ops[n - 1] == '+' ||
        ops[n - 1] == '-')
    {
      numbers.push_back(cur);
      ops.push_back(op);
    }
    else
    {
      int topNumber = numbers[n - 1];
      char topOp = ops[n - 1];
      if (topOp == '*')
      {
        numbers[n - 1] = topNumber * cur;
      }
      else
      {
        numbers[n - 1] = topNumber / cur;
      }

      ops[n - 1] = op;
    }
  }

  int compute(const vector<int> &numbers, const vector<char> &ops)
  {
    int n = numbers.size();
    int ans = numbers[0];
    for (int i = 1; i < n; i++)
    {
      ans += (ops[i - 1] == '+' ? numbers[i] : -numbers[i]);
    }

    return ans;
  }

public:
  int where;

  int solve(string s)
  {
    where = 0;
    return f(s, 0);
  }
};