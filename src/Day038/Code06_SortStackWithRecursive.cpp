// 用递归函数排序栈
// 栈只提供push、pop、isEmpty三个方法
// 请完成无序栈的排序，要求排完序之后，从栈顶到栈底从小到大
// 只能使用栈提供的push、pop、isEmpty三个方法、以及递归函数
// 除此之外不能使用任何的容器，数组也不行
// 就是排序过程中只能用：
// 1) 栈提供的push、pop、isEmpty三个方法
// 2) 递归函数，并且返回值最多为单个整数
#include <iostream>
#include <stack>
#include <climits>
using namespace std;

int depth(stack<int> &st)
{
  if (st.empty())
  {
    return 0;
  }

  int num = st.top();
  st.pop();
  int d = depth(st) + 1;
  st.push(num);
  return d;
}

int maxInDepth(stack<int> &st, int deep)
{
  if (deep == 0)
  {
    return INT_MIN;
  }

  int num = st.top();
  st.pop();
  int restMax = maxInDepth(st, deep - 1);
  int maxVal = max(num, restMax);
  st.push(num);
  return maxVal;
}

int timesInDepth(stack<int> &st, int deep, int maxVal)
{
  if (deep == 0)
  {
    return 0;
  }

  int num = st.top();
  st.pop();
  int restTimes = timesInDepth(st, deep - 1, maxVal);
  int times = restTimes + (num == maxVal ? 1 : 0);
  st.push(num);
  return times;
}

// 将栈顶往下 deep 层中的 k 个最大值沉底（即移动到这部分的最底部），其余元素相对顺序不变
void sinkMax(stack<int> &st, int deep, int maxVal, int k)
{
  if (deep == 0)
  {
    for (int i = 0; i < k; i++)
    {
      st.push(maxVal);
    }
  }
  else
  {
    int num = st.top();
    st.pop();
    sinkMax(st, deep - 1, maxVal, k);
    if (num != maxVal)
    {
      st.push(num);
    }
  }
}

stack<int> randomStack(int n, int v)
{
  stack<int> st;
  for (int i = 0; i < n; ++i)
  {
    st.push(rand() % v);
  }

  return st;
}

bool isSorted(stack<int> st)
{
  int prev = INT_MIN;
  while (!st.empty())
  {
    int cur = st.top();
    if (prev > cur)
    {
      return false;
    }
    prev = cur;
    st.pop();
  }

  return true;
}

void sortStack(stack<int> &st)
{
  int deep = depth(st);
  while (deep > 0)
  {
    int maxVal = maxInDepth(st, deep);
    int k = timesInDepth(st, deep, maxVal);
    sinkMax(st, deep, maxVal, k);
    deep -= k;
  }
}

int main()
{
  stack<int> test;
  test.push(1);
  test.push(5);
  test.push(4);
  test.push(5);
  test.push(3);
  test.push(2);
  test.push(3);
  test.push(1);
  test.push(4);
  test.push(2);

  sortStack(test);
  cout << "排序后（栈顶到栈底）：" << endl;
  while (!test.empty())
  {
    cout << test.top() << endl;
    test.pop();
  }

  const int N = 20, V = 20;
  const int TEST_TIMES = 20000;
  srand(static_cast<unsigned>(time(nullptr)));
  cout << "\n测试开始" << endl;

  for (int i = 0; i < TEST_TIMES; ++i)
  {
    int n = rand() % N;
    stack<int> st = randomStack(n, V);
    sortStack(st);
    if (!isSorted(st))
    {
      cout << "出错了！" << endl;
      break;
    }
  }
  cout << "测试结束" << endl;

  return 0;
}