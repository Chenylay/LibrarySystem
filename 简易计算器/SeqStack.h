#pragma once
#include <iostream>
#include <assert.h>
using namespace std;

const int stackIncreament = 10;  //ջ���ʱ��չ�ռ������

template<class T>
class SeqStack {
public:
	SeqStack() { elements = 0; top = -1; maxSize = 0; }
	SeqStack(int sz = 50); //���캯��
	~SeqStack() { delete[] elements; } //����
	void Push(const T& x);  //���ջ���˾�Ҫ��������������ջ��ջ��
	T Pop(); //�˳�ջ��Ԫ��ͨ�������Ͳ���x����
	T getTop(); //��ȡջ��Ԫ�ص�ֵ
	bool IsEmpty()const { return(top == -1) ? true : false; }
	bool IsFull()const { return(top == maxSize - 1) ? true : false; }
	int getSize()const { return top + 1; } //����ջ��Ԫ�ظ���
	void MakeEmpty() { top = -1; } //���ջ������
private:
	T* elements;   //���ջ��Ԫ�ص�ջ����
	int top;    //ջ��ָ��
	int maxSize;   //ջ���������
	void overflowProcess(); //ջ���������
};

template<class T>
SeqStack<T>::SeqStack(int sz) :top(-1), maxSize(sz) { //��ִ�г�ʼ���б�
	elements = new T[maxSize];
	if (elements == nullptr) {
		cout << "ջ�洢�ռ����ʧ�ܣ�" << endl; exit(1);
	}
}

template<class T>
void SeqStack<T>::overflowProcess() {  //˽�к���������ջ�洢�ռ�
	T* newArray = new T[maxSize + stackIncreament];
	if (newArray == nullptr) { cout << "�洢����ʧ�ܣ�" << endl; exit(1); }
	for (int i = 0; i <= top; i++)
		newArray[i] = elements[i];  //�����ջ��ԭ��Ԫ�ط����µ�
	maxSize = maxSize + stackIncreament; //�����������
	delete[] elements; //ɾ���ɵ�
	elements = newArray; //���µ�����
}

template<class T>
void SeqStack<T>::Push(const T& x) {
	if (IsFull() == true) { cout << "ջ�����Զ�����������" << endl; overflowProcess(); }//ջ�������������
	elements[++top] = x; //ջ��ָ���ȼ�1�ٷŽ�ջ
	cout << "Ԫ�� " << x << " �ɹ�����ջ��" << endl;
}

template<class T>
T SeqStack<T>::Pop() {
	if (IsEmpty() == true) { cout << "ջΪ��!" << endl; return false; }
	T x = elements[top--]; //�ȴ����������ָ����1
	return x;
}

template<class T>
T SeqStack<T>::getTop() {
	if (IsEmpty() == true)return false;
	T x;
	x = elements[top];
	return x;
}

