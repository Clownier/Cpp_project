#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<fstream>
#include <vector>
#include<string>
#include"QUEUE5.h"
using namespace std;

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
	system("pause");
	return 0;
}