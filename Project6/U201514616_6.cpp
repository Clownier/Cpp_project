#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<fstream>
#include <vector>
#include<string>
#include<algorithm>
#include"QUEUE6.h"
#define Partner_Problem //�������
//#define TEXT  //����Ӳ���
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
		times++;//ѭ������
		if (isdigitstr(argv[times])) {//����Ϊ����
			if (-1 == (*carry[kind])(atoi(argv[times]))) {//������Ӧ����
				times = -1;
				break;
			}
			continue;
		}
		if ('\0' != argv[times][2] || '-' != argv[times][0]) {//�����в������� ��"-X"��ʽ
			kind = -1;
			write << "E ";
			continue;
		}
		if (kind != 5 && kind != -2)
			printStack();//��ӡ��ǰջ

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
/*�ٶ���һ������ϣ���ʿ�ų�һ�ӣ�
Ůʿ�ų���һ�ӡ�ÿ����������ʱ�����жӺ�Ů�ӵĶ�ͷ����һ�ˣ�
����������������������Խ����Լ����е�β����
����Ů���ӵĳ�ʼ�����ֱ�ΪM��F��M��F��Ϊ��������M != F����
�ж�������λ��m��m <= M������ʿ���ǳ����Ů��λ��f��f <= F����Ůʿ���裬
�����ڵڼ�֧���������ܺ͸�Ůʿ���� ?*/
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
