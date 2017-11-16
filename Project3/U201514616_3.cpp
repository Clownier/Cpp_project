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






ofstream write;
STACK *pStack = nullptr;
int(*carry[6])(int);
void printStack() {
	if (!pStack)
		return;
	string res = pStack->getprint();
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
	pStack = new STACK(t);
	return 0;
}
int carryI(int t) {
	try {
		*pStack << t;
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
			*pStack >> e;
		}
		catch (char *) {
			write << "E ";
			return -1;
		}
	}
	return 0;
}
int carryA(int t) {
	STACK *pNew = new STACK(t);
	*pNew = *pStack;
	delete pStack;
	pStack = pNew;
	return 0;
}
int carryC(int t) {
	STACK *pNew = new STACK(*pStack);
	pStack = pNew;
	return 0;
}
int carryG(int t) {
	try {
		write << (*pStack)[t] << " ";
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
		case 'n':write << "N " << (int)*pStack << " "; kind = -2; break;
		default:kind = -1; write << "E "; break;
		}
	}
	if (times != -1 && kind>-2) {
		printStack();
	}
	write.close();
	system("type D:\\WorkSpace\\VS_C\\Cpp_expericen\\Project1\\Debug\\Project3.txt");
	printf("\n");
	//system("pause");
	return 0;
}