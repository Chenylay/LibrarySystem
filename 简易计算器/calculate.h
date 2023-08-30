#pragma once
#include "SeqStack.h"
#include <cmath>
#include <string>
#include <iostream>
using namespace std;

//模拟一个简单的计算器，对从键盘读入的中缀表达式先转化为后缀表达式再求值
template<class T>
class Calculator {
public:
    Calculator(int sz) : s(sz) {
        for (int i = 0; i < 100; i++) {
            RPN_ch[i] = ' ';
        }
    }
    void postfix(const string& mid_str);  //中缀转后缀
    void Run();  //执行表达式运算
    void Clear();

private:
    char RPN_ch[100];
    SeqStack<T> s; //因为我们计算器是针对后缀表达式的，所以这个栈中存放的必须是后缀表达式
    void AddOperand(const T& value); //进操作数栈
    bool Get2Operands(T& left, T& right);//从栈中退出两个操作数
    void DoOperator(char op); //形成运算指令进行计算
};


template<class T>
void Calculator<T>::DoOperator(char op) {
    T left, right, value; //取两个操作数，根据操作符op形成运算指令并计算
    bool result = Get2Operands(left, right);  //取两个操作数
    if (!result) {
        cout << "取数不成功,无法进行下一步运算！" << endl;
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
        if (right == 0.0) { //检查：除数不能为零
            cerr << "Divide by 0!" << endl;
            Clear();  //报错清栈
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
        cerr << "缺少右操作数！" << endl;
        return false; //栈空，报错
    }
    else
        right = s.Pop(); //取出右操作数

    if (s.IsEmpty()) {
        cerr << "缺少左操作数！" << endl;
        return false;
    }
    else
        left = s.Pop();

    return true; //代表成功取出了两个操作数
}

template<class T>
void Calculator<T>::AddOperand(const T& value) {
    s.Push(value); //将操作数的值Push进操作数栈
}

template<class T>
void Calculator<T>::Run() {
    T newOperand{};  //用来存储运算操作数
    int i = 0;
    while (RPN_ch[i] != '=') {
        switch (RPN_ch[i]) {
        case '+':
        case '-':
        case '*':
        case '/':
            DoOperator(RPN_ch[i]); //如果是操作符，进行计算
            break;
        default:
            cin.putback(RPN_ch[i]); //将字符放回输入流
            cin >> newOperand;  //重新从输入流中读操作数
            AddOperand(newOperand); //将操作数放入栈中
            break;
        }
        i++;
    }

    if (!s.IsEmpty()) {
        T result = s.getTop();
        cout << "表达式运算结果为：" << result << endl;
    }
}

template<class T>
void Calculator<T>::Clear() {
    s.MakeEmpty();  //清栈
}

//栈内优先级
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

//栈外优先级
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

//中缀表达式转成后缀表达式
template<class T>
void Calculator<T>::postfix(const string& mid_str) {
    SeqStack<char> s1(100);   //转换时操作符的辅助栈
    s1.Push('#');
    int j = 0;
    for (int i = 0; i < mid_str.size(); i++) {
        if (mid_str[i] >= '0' && mid_str[i] <= '9') {
            RPN_ch[j++] = mid_str[i];
        }
        else {  //如果不是0~9操作数
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
    cout << "转化后的后缀表达式为：";
    for (int k = 0; k <= j; k++) {
        cout << RPN_ch[k];
    }
    cout << endl;
}
