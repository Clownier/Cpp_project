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


class QUEUE {
	int  *const  elems;	//�����ڴ����ڴ�Ŷ��е�Ԫ��
	const  int   max;	//elems�ܴ�ŵ����Ԫ�ظ���
	int   head, tail;		//����ͷ��β�����п�ʱhead=tail;��ʼʱhead=tail=0
public:
	QUEUE(int m);		//��ʼ��ѭ�����У�elems��m��Ԫ��
	QUEUE(const QUEUE&s); 			//�ö���s������ʼ������
	virtual operator int() const;			//���ض��е�ʵ��Ԫ�ظ���
	virtual int full() const;		       //���ض����Ƿ�������������1�����򷵻�0
	virtual int operator[ ](int x)const;   //ȡ�±�Ϊx��Ԫ��,��1��Ԫ���±�Ϊ0
	virtual QUEUE& operator<<(int e); 	//��e�����,�����ض���
	virtual QUEUE& operator>>(int &e);	//�����е�e,�����ض���
	virtual QUEUE& operator=(const QUEUE&s); //��s������,�����ر���ֵ�Ķ���
	virtual void print() const;			//��ӡ����
	std::string getprint() const;
	virtual ~QUEUE();					//���ٶ���
};
using namespace std;

QUEUE::QUEUE(int m) :
	max(m), elems((int *)malloc(m * sizeof(int)))
{
	head = tail = 0;
	if (NULL == elems) {
		throw "construct fail";
	}
}

QUEUE::QUEUE(const QUEUE & s) :
	QUEUE(s.max)
{
	for (int i = s.tail; i != s.head; i = (i + 1) % max) {
		elems[head] = s.elems[i];
		head = (head + 1) % max;
	}
}

QUEUE::operator int() const
{
	return ((head + max) - tail) % max;
}

int QUEUE::full() const
{
	return ((head + 1) % max == tail) ? 1 : 0;
}

int QUEUE::operator[](int x) const
{
	if (x < 0 || x >= (int)(*this)) {
		throw "range_error";
		return -1;
	}
	else {
		return elems[(tail + x) % max];
	}
}

QUEUE & QUEUE::operator<<(int e)
{
	if (full())
		throw "range_error";
	else {
		elems[head] = e;
		head = (head + 1) % max;
	}
	return *this;
}

QUEUE & QUEUE::operator>>(int & e)
{
	// TODO: �ڴ˴����� return ���
	if (head == tail)
		throw "range_error";
	else {
		e = elems[tail];
		tail = (tail + 1) % max;
	}
	return *this;
}

QUEUE & QUEUE::operator=(const QUEUE & s)
{
	// TODO: �ڴ˴����� return ���
	const_cast<int &>(max) = s.max;
	const_cast<int *>(elems) = new int[max];
	if (NULL == elems) {
		throw "new fail!";
	}
	tail = head = 0;
	for (; head < s; head++) {
		elems[head] = s[head];
	}
	return *this;
}

void QUEUE::print() const
{
	std::cout << getprint() << std::endl;
}

std::string QUEUE::getprint() const
{
	std::stringstream res;
	for (int i = 0; i < *this; i++) {
		res << (*this)[i] << " ";
	}
	std::string end = *this == 0 ? "" : res.str();
	return end;
}

QUEUE::~QUEUE()
{
	free(elems);
	const_cast<int &>(max) = 0;
	tail = head = 0;
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
	system("type D:\\WorkSpace\\VS_C\\Cpp_expericen\\Project1\\Debug\\Project4.txt");
	printf("\n");
	//system("pause");
	return 0;
}