#pragma once
#include "SeqStack.h"
#include <cmath>
#include <string>
#include <iostream>
using namespace std;

//ģ��һ���򵥵ļ��������ԴӼ��̶������׺���ʽ��ת��Ϊ��׺���ʽ����ֵ
template<class T>
class Calculator {
public:
    Calculator(int sz) : s(sz) {
        for (int i = 0; i < 100; i++) {
            RPN_ch[i] = ' ';
        }
    }
    void postfix(const string& mid_str);  //��׺ת��׺
    void Run();  //ִ�б��ʽ����
    void Clear();

private:
    char RPN_ch[100];
    SeqStack<T> s; //��Ϊ���Ǽ���������Ժ�׺���ʽ�ģ��������ջ�д�ŵı����Ǻ�׺���ʽ
    void AddOperand(const T& value); //��������ջ
    bool Get2Operands(T& left, T& right);//��ջ���˳�����������
    void DoOperator(char op); //�γ�����ָ����м���
};


template<class T>
void Calculator<T>::DoOperator(char op) {
    T left, right, value; //ȡ���������������ݲ�����op�γ�����ָ�����
    bool result = Get2Operands(left, right);  //ȡ����������
    if (!result) {
        cout << "ȡ�����ɹ�,�޷�������һ�����㣡" << endl;
        Clear();
        return;
    }

    switch (op) {
    case '+':
        value = left + right;
        s.Push(value);
        break;
    case '-':
        value = left - right;
        s.Push(value);
        break;
    case '*':
        value = left * right;
        s.Push(value);
        break;
    case '/':
        if (right == 0.0) { //��飺��������Ϊ��
            cerr << "Divide by 0!" << endl;
            Clear();  //������ջ
        }
        else {
            value = left / right;
            s.Push(value);
        }
        break;
    }
}

template<class T>
bool Calculator<T>::Get2Operands(T& left, T& right) {
    if (s.IsEmpty()) {
        cerr << "ȱ���Ҳ�������" << endl;
        return false; //ջ�գ�����
    }
    else
        right = s.Pop(); //ȡ���Ҳ�����

    if (s.IsEmpty()) {
        cerr << "ȱ�����������" << endl;
        return false;
    }
    else
        left = s.Pop();

    return true; //����ɹ�ȡ��������������
}

template<class T>
void Calculator<T>::AddOperand(const T& value) {
    s.Push(value); //����������ֵPush��������ջ
}

template<class T>
void Calculator<T>::Run() {
    T newOperand{};  //�����洢���������
    int i = 0;
    while (RPN_ch[i] != '=') {
        switch (RPN_ch[i]) {
        case '+':
        case '-':
        case '*':
        case '/':
            DoOperator(RPN_ch[i]); //����ǲ����������м���
            break;
        default:
            cin.putback(RPN_ch[i]); //���ַ��Ż�������
            cin >> newOperand;  //���´��������ж�������
            AddOperand(newOperand); //������������ջ��
            break;
        }
        i++;
    }

    if (!s.IsEmpty()) {
        T result = s.getTop();
        cout << "���ʽ������Ϊ��" << result << endl;
    }
}

template<class T>
void Calculator<T>::Clear() {
    s.MakeEmpty();  //��ջ
}

//ջ�����ȼ�
int isp(char op) {
    int priority = 0;
    if (op == '#') {
        priority = 0;
    }
    else if (op == '(') {
        priority = 1;
    }
    else if (op == ')') {
        priority = 6;
    }
    else if (op == '+' || op == '-') {
        priority = 3;
    }
    else if (op == '*' || op == '/') {
        priority = 5;
    }
    return priority;
}

//ջ�����ȼ�
int icp(char op) {
    int priority = 0;
    if (op == '#') {
        priority = 0;
    }
    else if (op == '(') {
        priority = 6;
    }
    else if (op == ')') {
        priority = 1;
    }
    else if (op == '+' || op == '-') {
        priority = 2;
    }
    else if (op == '*' || op == '/') {
        priority = 4;
    }
    return priority;
}

//��׺���ʽת�ɺ�׺���ʽ
template<class T>
void Calculator<T>::postfix(const string& mid_str) {
    SeqStack<char> s1(100);   //ת��ʱ�������ĸ���ջ
    s1.Push('#');
    int j = 0;
    for (int i = 0; i < mid_str.size(); i++) {
        if (mid_str[i] >= '0' && mid_str[i] <= '9') {
            RPN_ch[j++] = mid_str[i];
        }
        else {  //�������0~9������
            int op_icp = icp(mid_str[i]);

            if (isp(s1.getTop()) > op_icp) {
                RPN_ch[j++] = s1.getTop();
                s1.Pop();
                s1.Push(mid_str[i]);
            }
            else if (isp(s1.getTop()) < op_icp) {
                s1.Push(mid_str[i]);
            }
            else if (isp(s1.getTop()) == op_icp) {
                s1.Pop();
            }
        }
    }

    while (!s1.IsEmpty()) {
        if (s1.getTop() != '#') {
            RPN_ch[j++] = s1.getTop();
            s1.Pop();
        }
        else {
            s1.Pop();
        }
    }

    RPN_ch[j] = '=';
    cout << "ת����ĺ�׺���ʽΪ��";
    for (int k = 0; k <= j; k++) {
        cout << RPN_ch[k];
    }
    cout << endl;
}
