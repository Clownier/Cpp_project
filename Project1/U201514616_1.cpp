#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<fstream>
#include <vector>
#include<string>
#include"STACK.h"
using namespace std;


ofstream write;
STACK *stack = (STACK *)malloc(1*sizeof(STACK));
void printStack() {
	string res = getprint(stack);
	if (res[0] != '\0') {
		write << res;
	}
}
static int isdigitstr(char *str)
{
	return (strspn(str, "0123456789") == strlen(str));
}
char * getOpenFile(char * filename) {
	char *openfile= strtok(filename, ".");
	char *file = strtok(NULL,".") ;
	while (file&&strcmp(file,"exe")) {
		strcat(openfile, file);
		file = strtok(NULL, ".");
	}
	strcat(openfile, ".txt");
	return openfile;
}
int carryS(int t){
	write << t << " ";
	initSTACK(stack, t);
	return 0;
}
int carryI(int t) {
	//write << t << " ";
	if (stack->pos >= stack->max) {
		write << "E ";
		return -1;
	}else
		push(stack, t);
	return 0;
}
int carryO(int t) {
	int e;
	if (t == 0)
		return 0;
	//write << t << " ";
	if (t > stack->pos) {
		write << "E";
		return -1;
	}
	while (t != 0) {
		pop(stack, e);
		t--;
	}
	//printStack();
	return 0;
}
int carryG(int t) {
	if (t >= stack->pos) {
		write << "E ";
		return -1;
	}
	write << stack->elems[t] << " ";
	return 0;
}
int carryA(int t) {
	STACK *pNew = (STACK *)malloc(1 * sizeof(STACK));
	initSTACK(pNew, t);
	stack = assign(pNew, *stack);
	return 0;
}
int carryC(int t) {
	STACK *pNew = (STACK *)malloc(1 * sizeof(STACK));
	initSTACK(pNew,*stack);
	stack = pNew;
	return 0;
}
int main(int argc,char *argv[]) {
	char *openfile = getOpenFile(argv[0]);

	write.open(openfile);
	if (!write.is_open()) {
		exit(-1);
	}
	int(*carry[6])(int);
	carry[0] = carryS;
	carry[1] = carryI;
	carry[2] = carryO;
	carry[3] = carryG;
	carry[4] = carryA;
	carry[5] = carryC;
	int kind = -1,times = 0;
	while (times < argc-1) {
		times++;
		if (isdigitstr(argv[times])) {
			if (-1 == (*carry[kind])(atoi(argv[times]))) {
				times = -1;
				break;
			}
			continue;
		}
		if (argv[times][2] != '\0') {
			kind = -1;
			write << "E ";
			continue;
		}
		if(kind != 3&&kind!=-2)
			printStack();
		switch (argv[times][1])
		{
		case 'S':
		case 's':kind = 0; write << "S "; break;
		case 'I':
		case 'i':kind = 1; write << "I "; //printStack()
			; break;
		case 'O':
		case 'o':kind = 2; write << "O "; break;
		case 'N':
		case 'n':write << "N " << stack->pos<<" "; kind = -2; break;
		case 'G':
		case 'g':write << "G "; kind = 3; break;
		case 'A':
		case 'a':write << "A "; kind = 4; break;
		case 'C':
		case 'c':write << "C "; kind = -1; break;
		default:kind = -1; write << "E ";
			break;
		}
	}
	if(times != -1&&kind>-2)
		printStack();
	//carryS(10);
	//carryI(1);
	//print(stack);
	//write << "this is version 1.0";
	write.close();
	system("type D:\\WorkSpace\\VS_C\\Cpp_expericen\\Project1\\Debug\\Project1.txt");
	printf("\n");
	//system("pause");
	return 0;
}