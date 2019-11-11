<center><h1>
Data Structures and Algorithms Laboratory Projects Report </h1></center> 

# Linear List
## 常家奇
## Date: 2019-11-11

## Chapter 1: Introduction
> Use the stack to complete the evaluation of arithmetic expressions.Enter an arithmetic expression from the keyboard or file, calculate the result and display it.

## Chapter 2: Algorithm Specification 

### 主要数据结构设计说明

- 采用了两个栈来进行运算(数字栈，符号栈)，通过一边读取表达式一边压栈来计算表达式的值

### 系统设计思想

- 异常类
    - `no_expr_exception`类
    > 继承于基础异常类，当输入的表达式非法时，抛出此类。
    - `divide_zero_exception`类
    > 继承于基础异常类，当运算过程中出现除数为0的情况时，抛出此类。
    




