## 命题自动证明小助手
##### 项目介绍
本项目利用王浩算法，读取输入的命题并给出命题的正误
本项目完全由C语言实现，不含任何面向对象编程的方法和思想，也未使用STL标准库，适合作为编程初学者的练习项目
##### 输入格式要求
可读取 $A,B,\cdots,Z$ 表示的命题变项和 $\neg,\vee,\wedge,\to$ 四种联结词，下面是联结词与输入符号的对照表：
|联结词|输入符号|
|--|--|
|$\neg$|0|
|$\vee$|1|
|$\wedge$|2|
|$\to$|3|

例如：

$\neg P\to(P\wedge Q\vee R)$

应输入：

$0P3(P2Q1R)$

注意：本项目不能识别除 $\neg$ 外的联结词的优先级，会自动从左到右计算，因此需要输入时合理添加括号
##### 输出
会输出 $TRUE$ 或 $FALSE$ ，不会显示证明过程
##### 开发说明
开发者： $lsh$ ，Tsinghua University，Dushi College
项目灵感：清华大学计算机系课程《离散数学(1)》作业
## Automated Propositional Proof Assistant
##### Project Introduction
This project utilizes the Wang Hao algorithm to read input propositions and determine their truth values.
The project is fully implemented in C language, without any object-oriented programming methods or ideas, and does not use the STL standard library, making it suitable as a practice project for beginners in programming.
##### Input Format Requirements
It can read propositional variables represented by $A, B, \cdots, Z$ and four connectives $\neg, \vee, \wedge, \to$ . Below is a table of connectives and their corresponding input symbols:
|Connective|Input Symbol|
|--|--|
|$\neg$|0|
|$\vee$|1|
|$\wedge$|2|
|$\to$|3|

For example:

$\neg P \to (P \wedge Q \vee R)$

Should be input as:

$0P3(P2Q1R)$

Note: This project cannot recognize the precedence of connectives other than $\neg$ , and will calculate from left to right automatically, so it is necessary to add parentheses reasonably when inputting.
##### Output
It will output $TRUE$ or $FALSE$, without displaying the proof process.
##### Development Notes
Developer: $lsh$ , Tsinghua University, Dushi College
Project Inspiration: Assignment from the course "Discrete Mathematics (1)" in the Department of Computer Science at Tsinghua University.
