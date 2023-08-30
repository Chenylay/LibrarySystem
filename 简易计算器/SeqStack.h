#pragma once
#include <iostream>
#include <assert.h>
using namespace std;

const int stackIncreament = 10;  //栈溢出时扩展空间的增量

template<class T>
class SeqStack {
public:
	SeqStack() { elements = 0; top = -1; maxSize = 0; }
	SeqStack(int sz = 50); //构造函数
	~SeqStack() { delete[] elements; } //析构
	void Push(const T& x);  //如果栈满了就要溢出处理，否则就入栈到栈顶
	T Pop(); //退出栈的元素通过引用型参数x返回
	T getTop(); //获取栈顶元素的值
	bool IsEmpty()const { return(top == -1) ? true : false; }
	bool IsFull()const { return(top == maxSize - 1) ? true : false; }
	int getSize()const { return top + 1; } //返回栈中元素个数
	void MakeEmpty() { top = -1; } //清空栈的内容
private:
	T* elements;   //存放栈中元素的栈数组
	int top;    //栈顶指针
	int maxSize;   //栈的最大容量
	void overflowProcess(); //栈的溢出处理
};

template<class T>
SeqStack<T>::SeqStack(int sz) :top(-1), maxSize(sz) { //先执行初始化列表
	elements = new T[maxSize];
	if (elements == nullptr) {
		cout << "栈存储空间分配失败！" << endl; exit(1);
	}
}

template<class T>
void SeqStack<T>::overflowProcess() {  //私有函数：扩充栈存储空间
	T* newArray = new T[maxSize + stackIncreament];
	if (newArray == nullptr) { cout << "存储分配失败！" << endl; exit(1); }
	for (int i = 0; i <= top; i++)
		newArray[i] = elements[i];  //逐个将栈内原有元素放入新的
	maxSize = maxSize + stackIncreament; //更新最大容量
	delete[] elements; //删掉旧的
	elements = newArray; //给新的正名
}

template<class T>
void SeqStack<T>::Push(const T& x) {
	if (IsFull() == true) { cout << "栈满，自动扩充容量！" << endl; overflowProcess(); }//栈满就做溢出处理
	elements[++top] = x; //栈顶指针先加1再放进栈
	cout << "元素 " << x << " 成功推入栈顶" << endl;
}

template<class T>
T SeqStack<T>::Pop() {
	if (IsEmpty() == true) { cout << "栈为空!" << endl; return false; }
	T x = elements[top--]; //先存出数据再让指针退1
	return x;
}

template<class T>
T SeqStack<T>::getTop() {
	if (IsEmpty() == true)return false;
	T x;
	x = elements[top];
	return x;
}

