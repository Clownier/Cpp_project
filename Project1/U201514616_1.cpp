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
	//write << t << " ";
	while (t != 0) {
		pop(stack, e);
		t--;
	}
	//printStack();
	return 0;
}
int main(int argc,char *argv[]) {
	char *openfile = getOpenFile(argv[0]);

	write.open(openfile);
	if (!write.is_open()) {
		exit(-1);
	}
	int(*carry[3])(int);
	carry[0] = carryS;
	carry[1] = carryI;
	carry[2] = carryO;
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
		default:kind = -1; write << "E ";
			break;
		}
	}
	if(times != -1)
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