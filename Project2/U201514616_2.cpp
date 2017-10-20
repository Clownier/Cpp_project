#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<fstream>
#include <vector>
#include<string>
#include"STACK2.h"
using namespace std;

ofstream write;
STACK *pStack = nullptr;
int(*carry[5])(int);
void printStack() {
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
int carryI(int t) {
	return 0;
}
int carryO(int t) {
	return 0;
}
int carryA(int t) {
	return 0;
}
int carryC(int t) {
	return 0;
}
int carryS(int t) {
	write << t << " ";
	pStack = new STACK(t);
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
	return 0;
}
int main(int argc,char *argv[]) {
	initFile(argv[0]);
	int kind = -1, times = 0;
	while (times < argc - 1) {
		times++;
		if (isdigitstr(argv[times])) {
			if (-1 == (*carry[kind])(atoi(argv[times]))) {
				times = -1;
				break;
			}
			continue;
		}
		if ('\0' != argv[times][2]||'-'!=argv[times][0]) {
			kind = -1;
			write << "E ";
			continue;
		}
		printStack();
		
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
		default:kind = -1; write << "E "; break;
		}
	}
	if (times != -1) {
		printStack();
	}
	write.close();
	system("type D:\\WorkSpace\\VS_C\\Cpp_expericen\\Project2\\Debug\\Project1.txt");
	printf("\n");
	system("pause");
	return 0;

}