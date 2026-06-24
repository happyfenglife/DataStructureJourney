#include <iostream>
#include <stack>
using namespace std;

int bottomOut(stack<int> &stk)
{
  int ans = stk.top();
  stk.pop();
  if (stk.empty())
  {
    return ans;
  }
  else
  {
    int last = bottomOut(stk);
    stk.push(ans);
    return last;
  }
}

void reverseStack(stack<int> &stk)
{
  if (stk.empty())
  {
    return;
  }

  int num = bottomOut(stk);
  reverseStack(stk);
  stk.push(num);
}

int main()
{
  stack<int> stk;
  for (int i = 1; i <= 5; i++)
  {
    stk.push(i);
  }

  reverseStack(stk);

  while (!stk.empty())
  {
    cout << stk.top() << '\n';
    stk.pop();
  }

  return 0;
}