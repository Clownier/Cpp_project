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
	STACK(int m);		//初始化栈：最多m个元素
	STACK(const STACK&s); //用栈s拷贝初始化栈
	int  size() const;		//返回栈的最大元素个数max
	int  howMany() const;	//返回栈的实际元素个数pos
	int  getelem(int x) const;	//取下标x处的栈元素
	STACK& push(int e); 	//将e入栈,并返回栈
	STACK& pop(int &e); 	//出栈到e,并返回栈
	STACK& assign(const STACK&s);
	std::string getprint() const;
	//赋s给栈,并返回被赋值的栈
	void print() const;		//打印栈
	~STACK();				//销毁栈
};
using namespace std;

STACK::STACK(int m) throw(char *) :
	max(m), elems((int*)malloc(m * sizeof(int))), pos(0)
{
	if (NULL == elems)
		throw "exception";
}


STACK::STACK(const STACK & s) :
	max(s.max), elems(s.elems), pos(s.pos)
{
}

int STACK::size() const
{
	return max;
}

int STACK::howMany() const
{
	return pos;
}

int STACK::getelem(int x) const throw(char *)
{
	if (x >= pos)
		throw "exception";
	else
		return elems[x];
	return -1;
}

STACK & STACK::push(int e)throw(char *)
{
	if (max <= pos)
		throw "exception";
	else {
		elems[pos] = e;
		pos++;
	}
	return *this;
}

STACK & STACK::pop(int & e) throw(char *)
{
	if (0 == pos)
		throw "exception";
	e = elems[--pos];
	return *this;
}

STACK & STACK::assign(const STACK & s)
{
	const_cast<int *>(elems) = new int[s.max];
	for (int i = 0; i < s.pos; i++) {
		elems[i] = s.elems[i];
	}
	const_cast<int &>(max) = s.max;
	pos = s.pos;
	return *this;
}

std::string STACK::getprint() const
{
	std::stringstream res;
	for (int i = 0; i < pos; i++) {
		res << elems[i] << " ";
	}
	std::string end = pos != 0 ? res.str() : "";
	return end;
}
void STACK::print() const
{
	std::cout << getprint() << std::endl;
}

STACK::~STACK()
{
	if (elems) {
		free(elems);
		const_cast<int &>(max) = 0;//const_cast change const data
		pos = 0;
	}


}





ofstream write;
STACK *pStack = nullptr;
int(*carry[6])(int);
void printStack() {
	if (!pStack)
		return;
	string res = pStack->getprint();
	if ('\0' != res[0]) {
		write << res;
	}
}
static int isdigitstr(char *str) {
	return (strspn(str, "0123456789") == strlen(str));
}
char * getOpenFIle(char *filename) {
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
		pStack->push(t);
	}
	catch (char * ) {
		write << "E ";
		return -1;
	}
	return 0;
}
int carryO(int t) {
	int e;
	while(t>0){
		try {
			pStack->pop(e);
		}
		catch (char * ) {
			write << "E ";
			return -1;
		}
		t--;
	}
	return 0;
}
int carryA(int t) {
	STACK *pNew = new STACK(t);
	pNew->assign(*pStack);
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
		write << pStack->getelem(t) << " ";
	}
	catch (char * e) {
		write << "E ";
		return -1;
	}
	return 0;
}
int initFile(char *filename) {
	char *openfile = getOpenFIle(filename);
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
int main(int argc,char *argv[]) {
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
		if ('\0' != argv[times][2]||'-'!=argv[times][0]) {//命令行参数错误 非"-X"形式
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
		case 'n':write << "N " << pStack->howMany() << " "; kind = -2; break;
		default:kind = -1; write << "E "; break;
		}
	}
	if (times != -1&&kind>-2) {
		printStack();
	}
	write.close();
	system("type D:\\WorkSpace\\VS_C\\Cpp_expericen\\Project1\\Debug\\Project2.txt");
	printf("\n");
	//system("pause");
	return 0;

}