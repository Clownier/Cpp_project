#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<fstream>
#include <vector>
#include<string>
#include <malloc.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
//#define NDEBUG
#include <assert.h>
#include <string>
#include<cstring>
#include <sstream> 

class STACK {
	int  *const  elems;	//申请内存用于存放栈的元素
	const  int   max;	//栈能存放的最大元素个数
	int   pos;			//栈实际已有元素个数，栈空时pos=0;
public:
	STACK(int m);		//初始化栈：最多存m个元素
	STACK(const STACK&s); 			//用栈s拷贝初始化栈
	virtual int  size() const;			//返回栈的最大元素个数max
	virtual operator int() const;			//返回栈的实际元素个数pos
	virtual int operator[ ] (int x) const;	//取下标x处的栈元素，第1个元素x=0
	virtual STACK& operator<<(int e); 	//将e入栈,并返回栈
	virtual STACK& operator>>(int &e);	//出栈到e,并返回栈
	virtual STACK& operator=(const STACK&s); //赋s给栈,并返回被赋值的栈
	virtual void print() const;			//打印栈
	virtual ~STACK();					//销毁栈
	std::string getprint() const;		//赋s给栈,并返回被赋值的栈
};


class QUEUE {
	STACK s1, s2;
	STACK &inStack = s1, &outStack = s2;
public:
	QUEUE(int m); //每个栈最多m个元素，要求实现的队列最多能入2m个元素
	QUEUE(const QUEUE&s); 			//用队列s拷贝初始化队列
	virtual operator int() const;			//返回队列的实际元素个数
	virtual int full() const;		       //返回队列是否已满，满返回1，否则返回0
	virtual int operator[ ](int x)const;   //取下标为x的元素,第1个元素下标为0
	virtual QUEUE& operator<<(int e); 	//将e入队列,并返回队列
	virtual QUEUE& operator>>(int &e);	//出队列到e,并返回队列
	virtual QUEUE& operator=(const QUEUE&s); //赋s给队列,并返回被赋值的队列
	std::string getprint() const;
	virtual void print() const;			//打印队列
	virtual ~QUEUE();					//销毁队列
};

using namespace std;

STACK::STACK(int m) throw () :
	max(m), elems((int *)malloc(m * sizeof(int))), pos(0)
{
	if (NULL == elems)
		throw "construct fail!";
}

STACK::STACK(const STACK &s) throw () :
	max(s.size()), pos(s), elems((int *)malloc(s.max * sizeof(int)))
{
	if (NULL == elems)
		throw "malloc fail!";
	else
		for (int i = 0; i < s.pos; i++) {
			elems[i] = s.elems[i];
		}
}
int STACK::size() const
{
	return max;
}

STACK::operator int() const
{
	return pos;
}

int STACK::operator[](int x) const
{
	if (x < 0 || x >= pos) {
		throw "range_error";
		return -1;
	}
	else
		return elems[x];
}

STACK & STACK::operator<<(int e)
{
	// TODO: 在此处插入 return 语句
	if (max <= pos)
		throw "range_error";
	else {
		elems[pos++] = e;
	}
	return *this;
}

STACK & STACK::operator>>(int & e)
{
	// TODO: 在此处插入 return 语句
	if (pos <= 0) {
		throw "range_error";
	}
	else {
		e = elems[--pos];
	}
	return *this;
}

STACK & STACK::operator=(const STACK & s)
{
	// TODO: 在此处插入 return 语句
	const_cast<int &>(max) = s.size();
	const_cast<int *>(elems) = new int[max];
	pos = s;
	for (int i = 0; i < pos; i++) {
		elems[i] = s[i];
	}
	return *this;
}

std::string STACK::getprint() const {
	std::stringstream res;
	for (int i = 0; i < pos; i++) {
		res << elems[i] << " ";
	}
	std::string end = pos != 0 ? res.str() : "";
	return end;
}

void STACK::print() const {
	std::cout << getprint() << std::endl;
}

STACK::~STACK() {
	free(elems);
	const_cast<int &>(max) = 0;
	pos = 0;
}


QUEUE::QUEUE(int m) :
	s1(m), s2(m) {

}

QUEUE::QUEUE(const QUEUE & s) :
	s1(s.s1.size()), s2(s.s2.size()) {

}

QUEUE::operator int() const {
	return inStack + outStack;
}

int QUEUE::full() const {
	if (inStack.size() <= inStack) {
		if (outStack)
			return 1;
	}
	return 0;
}

int QUEUE::operator[](int x) const {
	int res;
	if (x >= outStack) {
		try {
			res = inStack[x - outStack];
		}
		catch (char *) {
			throw "range_error";
			res = -1;
		}
	}
	else {
		try {
			res = outStack[outStack - x - 1];
		}
		catch (char *) {
			throw "range_error";
			res = -1;
		}
	}
	return res;
}

QUEUE& QUEUE::operator<<(int e) {
	if (full()) {
		throw "range_error";
		return *this;
	}
	else {
		try {
			inStack << e;
		}
		catch (char *) {
			while (inStack) {
				int temp;
				inStack >> temp;
				outStack << temp;
			}
			inStack << e;
		}
	}
	return *this;
}

QUEUE& QUEUE::operator>>(int &e) {
	if (!outStack && !inStack)
		throw "range_error";
	try {
		outStack >> e;
	}
	catch (char *) {
		while (inStack) {
			int temp;
			inStack >> temp;
			outStack << temp;
		}
		outStack >> e;
	}
	return *this;
}

QUEUE& QUEUE::operator=(const QUEUE&s) {
	try {
		inStack = s.inStack;
		outStack = s.outStack;
	}
	catch (char *) {
		throw "new fail!";
	}
	return *this;
}

std::string QUEUE::getprint() const {
	std::stringstream res;
	for (int i = 0; i < *this; i++) {
		res << (*this)[i] << " ";
	}
	std::string end = *this == 0 ? "" : res.str();
	return end;
}

void QUEUE::print() const {
	std::cout << getprint() << std::endl;
}

QUEUE::~QUEUE() {
	//inStack.~STACK();
	//outStack.~STACK();
}







ofstream write;
QUEUE *pQueue = nullptr;
int(*carry[6])(int);
void printStack() {
	if (!pQueue)
		return;
	string res = pQueue->getprint();
	if (res.length() != 0) {
		write << res;
	}
}
static int isdigitstr(char *str) {
	return (strspn(str, "0123456789") == strlen(str));
}
char * getOpenFile(char *filename) {
	char *openfile = strtok(filename, ".");
	char *file = strtok(NULL, ".");
	while (file&&strcmp(file, "exe")) {
		strcat(openfile, file);
		file = strtok(NULL, "");
	}
	strcat(openfile, ".txt");
	return openfile;
}
int carryS(int t) {
	write << t << " ";
	pQueue = new QUEUE(t);
	return 0;
}
int carryI(int t) {
	try {
		*pQueue << t;
	}
	catch (char *) {
		write << "E ";
		return -1;
	}
	return 0;
}
int carryO(int t) {
	int e;
	while (t-- > 0) {
		try {
			*pQueue >> e;
		}
		catch (char *) {
			write << "E ";
			return -1;
		}
	}
	return 0;
}
int carryA(int t) {
	QUEUE *pNew = new QUEUE(t);
	*pNew = *pQueue;
	delete pQueue;
	pQueue = pNew;
	return 0;
}
int carryC(int t) {
	QUEUE *pNew = new QUEUE(*pQueue);
	pQueue = pNew;
	return 0;
}
int carryG(int t) {
	try {
		write << (*pQueue)[t] << " ";
	}
	catch (char *) {
		write << "E ";
		return -1;
	}
	return 0;
}
int initFile(char *filename) {
	char *openfile = getOpenFile(filename);
	write.open(openfile);
	if (!write.is_open()) {
		throw "exception";
	}
	carry[0] = carryS;
	carry[1] = carryI;
	carry[2] = carryO;
	carry[3] = carryA;
	carry[4] = carryC;
	carry[5] = carryG;
	return 0;
}
int main(int argc, char *argv[]) {
	initFile(argv[0]);
	int kind = -1, times = 0;
	while (times < argc - 1) {
		times++;//循环次数
		if (isdigitstr(argv[times])) {//参数为数字
			if (-1 == (*carry[kind])(atoi(argv[times]))) {//调用响应函数
				times = -1;
				break;
			}
			continue;
		}
		if ('\0' != argv[times][2] || '-' != argv[times][0]) {//命令行参数错误 非"-X"形式
			kind = -1;
			write << "E ";
			continue;
		}
		if (kind != 5 && kind != -2)
			printStack();//打印当前栈

		switch (argv[times][1])
		{
		case 's':
		case 'S':kind = 0; write << "S "; break;
		case 'i':
		case 'I':kind = 1; write << "I "; break;
		case 'o':
		case 'O':kind = 2; write << "O "; break;
		case 'a':
		case 'A':kind = 3; write << "A "; break;
		case 'c':
		case 'C':kind = 4; write << "C "; break;
		case 'g':
		case 'G':kind = 5; write << "G "; break;
		case 'N':
		case 'n':write << "N " << (int)*pQueue << " "; kind = -2; break;
		default:kind = -1; write << "E "; break;
		}
	}
	if (times != -1 && kind>-2) {
		printStack();
	}
	write.close();
	system("type D:\\WorkSpace\\VS_C\\Cpp_expericen\\Project1\\Debug\\Project5.txt");
	printf("\n");
	//system("pause");
	return 0;
}