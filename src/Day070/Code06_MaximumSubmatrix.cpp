// 子矩阵最大累加和问题
// 给定一个二维数组grid，找到其中子矩阵的最大累加和
// 返回拥有最大累加和的子矩阵左上角和右下角坐标
// 如果有多个子矩阵都有最大累加和，返回哪一个都可以
// 测试链接 : https://leetcode.cn/problems/max-submatrix-lcci/
#include <vector>
#include <limits>
using namespace std;

class Solution
{
public:
  vector<int> getMaxMatrix(vector<vector<int>> &matrix)
  {
    int n = static_cast<int>(matrix.size());
    int m = static_cast<int>(matrix[0].size());

    int max = numeric_limits<int>::min();
    int a{}, b{}, c{}, d{};
    vector<int> nums(m);
    for (int up = 0; up < n; up++)
    {
      fill(nums.begin(), nums.end(), 0);
      for (int down = up; down < n; down++)
      {
        for (int l = 0, r = 0, pre = numeric_limits<int>::min(); r < m; r++)
        {
          nums[r] += matrix[down][r];
          if (pre >= 0)
          {
            pre += nums[r];
          }
          else
          {
            pre = nums[r];
            l = r;
          }

          if (pre > max)
          {
            max = pre;
            a = up;
            b = l;
            c = down;
            d = r;
          }
        }
      }
    }

    return {a, b, c, d};
  }
};