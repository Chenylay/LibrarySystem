#include "SeqStack.h"
#include "calculate.h"
#include <string>
#include <iostream>
using namespace std;

/*
* ����������
* 2
* 10
* 5*9+3-1
* 7+2*5
*/
int main()
{
	int i;
	cout << "������Ҫ����ı��ʽ������" << endl;
	cin >> i;
	cout << "�������ű��ʽ��˳��ջ���������" << endl;
	int sz; cin >> sz;
	Calculator<double> newCal(sz);
	string mid_str;
	for (int j = 0; j < i; j++)
	{
		cout << "�������" << j + 1 << "����׺�������ʽ��" << endl;
		cin >> mid_str;
		newCal.postfix(mid_str);  //������׺��������׺ת���ɺ�׺ 
		newCal.Run();
	}
	return 0;
}