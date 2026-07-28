// 可以翻转1次的情况下子数组最大累加和
// 给定一个数组nums，
// 现在允许你随意选择数组连续一段进行翻转，也就是子数组逆序的调整
// 比如翻转[1,2,3,4,5,6]的[2~4]范围，得到的是[1,2,5,4,3,6]
// 返回必须随意翻转1次之后，子数组的最大累加和
// 对数器验证
#include <iostream>
#include <vector>
#include <limits>
using namespace std;

void reverse(vector<int> &nums, int l, int r)
{
  while (l < r)
  {
    int tmp = nums[l];
    nums[l++] = nums[r];
    nums[r--] = tmp;
  }
}

// 返回子数组最大累加和
int maxSum(vector<int> &nums)
{
  int n = static_cast<int>(nums.size());
  int ans{nums[0]};
  for (int i = 1, pre = nums[0]; i < n; i++)
  {
    pre = max(nums[i], pre + nums[i]);
    ans = max(ans, pre);
  }

  return ans;
}

// 暴力方法
int maxSumReverse1(vector<int> &nums)
{
  int ans = numeric_limits<int>::min();
  for (int l = 0; l < nums.size(); l++)
  {
    for (int r = l; r < nums.size(); r++)
    {
      reverse(nums, l, r);
      ans = max(ans, maxSum(nums));
      reverse(nums, l, r);
    }
  }

  return ans;
}

// 正式方法
// 时间复杂度O(n)
int maxSumReverse2(vector<int> &nums)
{
  int n = static_cast<int>(nums.size());
  // start[i] : 所有必须以i开头的子数组中，最大累加和是多少
  vector<int> start(n);
  start[n - 1] = nums[n - 1];
  for (int i = n - 2; i >= 0; i--)
  {
    start[i] = max(nums[i], nums[i] + start[i + 1]);
  }

  int ans{start[0]};
  // end : 子数组必须以i-1结尾，其中的最大累加和
  int end{nums[0]};
  // 0~i-1范围上，
  // 子数组必须以0结尾，其中的最大累加和
  // 子数组必须以1结尾，其中的最大累加和
  // ...
  // 子数组必须以i-1结尾，其中的最大累加和
  // 所有情况中，最大的那个累加和就是maxEnd
  int maxEnd{nums[0]};
  for (int i = 1; i < n; i++)
  {
    // maxend   i....
    // 枚举划分点 i...
    ans = max(ans, maxEnd + start[i]);
    // 子数组必须以i结尾，其中的最大累加和
    end = max(nums[i], end + nums[i]);
    maxEnd = max(maxEnd, end);
  }

  ans = max(ans, maxEnd);
  return ans;
}

// 为了测试
// 生成随机数组
vector<int> randomArray(int n, int v)
{
  vector<int> ans(n);
  int range = v * 2 + 1;
  for (int i = 0; i < n; i++)
  {
    ans[i] = (rand() % range) - v;
  }
  return ans;
}

int main()
{
  srand(static_cast<unsigned int>(time(nullptr)));

  int n = 50;
  int v = 200;
  int testTime = 20000;
  cout << "测试开始" << '\n';
  for (int i = 0; i < testTime; i++)
  {
    int len = (rand() % n) + 1;
    vector<int> arr = randomArray(len, v);
    vector<int> arrCopy = arr; // maxSumReverse1 will modify array
    int ans1 = maxSumReverse1(arrCopy);
    int ans2 = maxSumReverse2(arr);
    if (ans1 != ans2)
    {
      cout << "出错了!" << '\n';
      // 可选：打印出错时的数组与结果以便调试
      // cout << "ans1=" << ans1 << " ans2=" << ans2 << '\n';
      return 0;
    }
  }

  cout << "测试结束" << '\n';
  return 0;
}