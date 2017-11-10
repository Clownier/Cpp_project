#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<fstream>
#include <vector>
#include<string>
#include<algorithm>
#include"QUEUE6.h"
#define Partner_Problem //舞伴问题
//#define TEXT  //出入队测试
using namespace std;

#ifdef TEXT
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
	system("type D:\\WorkSpace\\VS_C\\Cpp_expericen\\Project1\\Debug\\Project6.txt");
	printf("\n");
	system("pause");
	return 0;
}
#endif // TEXT
#ifdef Partner_Problem
/*假定在一次舞会上，男士排成一队，
女士排成另一队。每次舞曲响起时，从男队和女队的队头各出一人，
配成舞伴跳完此曲，跳完后各自进入自己队列的尾部。
若男女两队的初始人数分别为M和F（M和F均为素数，且M != F），
男队中排在位置m（m <= M）的男士，非常想和女队位置f（f <= F）的女士跳舞，
问他在第几支曲舞曲才能和该女士跳舞 ?*/
int main() {
	int M, F;
	cout << "please input M and F:" << endl;
	cin >> M >> F;
	QUEUE *qMale = new QUEUE(M);
	QUEUE *qFemale = new QUEUE(F);
	for (int i = 0; i < max(M, F); i++) {
		if (i < M)
			*qMale << i+1;
		if (i < F)
			*qFemale << i+1;
	}
	int m, f, res = 0,c = 0;
	cout << "please input m and f:" << endl;
	cin >> m >> f;
	while(true) {
		c++;
		*qFemale >> F;
		*qMale >> M;
		if (M == m) {
			res++;
			if (F == f)
				break;
		}
		*qFemale << F;
		*qMale << M;
	}
	cout << "On the " << res << "th rounds,they can dance together!" <<c<< endl;
	system("pause");
	return 0;
}
#endif // Partner_Problem
