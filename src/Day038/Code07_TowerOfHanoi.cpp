// 打印n层汉诺塔问题的最优移动轨迹
#include <iostream>
#include <string>
using namespace std;

void move(int i, const string &from, const string &to, const string &other)
{
  if (i == 1)
  {
    cout << "移动圆盘 1 从 " << from << " 到 " << to << endl;
  }
  else
  {
    move(i - 1, from, other, to);
    cout << "移动圆盘 " << i << " 从 " << from << " 到 " << to << endl;
    move(i - 1, other, to, from);
  }
}

void hanoi(int n)
{
  if (n > 0)
  {
    move(n, "左", "右", "中");
  }
}

int main()
{
  int n = 3;
  hanoi(n);
  return 0;
}