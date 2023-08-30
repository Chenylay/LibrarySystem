#include "SeqStack.h"
#include "calculate.h"
#include <string>
#include <iostream>
using namespace std;

/*
* 测试样例：
* 2
* 10
* 5*9+3-1
* 7+2*5
*/
int main()
{
	int i;
	cout << "请输入要计算的表达式行数：" << endl;
	cin >> i;
	cout << "请输入存放表达式的顺序栈最大容量：" << endl;
	int sz; cin >> sz;
	Calculator<double> newCal(sz);
	string mid_str;
	for (int j = 0; j < i; j++)
	{
		cout << "请输入第" << j + 1 << "条中缀算术表达式：" << endl;
		cin >> mid_str;
		newCal.postfix(mid_str);  //输入中缀并将将中缀转换成后缀 
		newCal.Run();
	}
	return 0;
}