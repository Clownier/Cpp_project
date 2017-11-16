#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<fstream>
#include <vector>
#include<string>
#include<algorithm>
//#define Partner_Problem //�������
#define TEXT  //����Ӳ���


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
	int  *const  elems;	//�����ڴ����ڴ��ջ��Ԫ��
	const  int   max;	//ջ�ܴ�ŵ����Ԫ�ظ���
	int   pos;			//ջʵ������Ԫ�ظ�����ջ��ʱpos=0;
public:
	STACK(int m);		//��ʼ��ջ������m��Ԫ��
	STACK(const STACK&s); 			//��ջs������ʼ��ջ
	virtual int  size() const;			//����ջ�����Ԫ�ظ���max
	virtual operator int() const;			//����ջ��ʵ��Ԫ�ظ���pos
	virtual int operator[ ] (int x) const;	//ȡ�±�x����ջԪ�أ���1��Ԫ��x=0
	virtual STACK& operator<<(int e); 	//��e��ջ,������ջ
	virtual STACK& operator>>(int &e);	//��ջ��e,������ջ
	virtual STACK& operator=(const STACK&s); //��s��ջ,�����ر���ֵ��ջ
	virtual void print() const;			//��ӡջ
	virtual ~STACK();					//����ջ
	std::string getprint() const;		//��s��ջ,�����ر���ֵ��ջ
};

class QUEUE :public STACK {
	STACK  s2;
	STACK &inStack = s2;
public:
	QUEUE(int m); //ÿ��ջ���m��Ԫ�أ�Ҫ��ʵ�ֵĶ����������2m��Ԫ��
	QUEUE(const QUEUE&s); 			//�ö���s������ʼ������
	virtual operator int() const;			//���ض��е�ʵ��Ԫ�ظ���
	virtual int full() const;		       //���ض����Ƿ�������������1�����򷵻�0
	virtual int operator[ ](int x)const;   //ȡ�±�Ϊx��Ԫ�أ���1��Ԫ���±�Ϊ0
	virtual QUEUE& operator<<(int e);  //��e�����,�����ض���
	virtual QUEUE& operator>>(int &e);	//�����е�e,�����ض���
	virtual QUEUE& operator=(const QUEUE&s); //��s������,�����ر���ֵ�Ķ���
	std::string getprint() const;
	virtual void print() const;			//��ӡ����
	virtual ~QUEUE();					//���ٶ���
};
using namespace std;

STACK::STACK(int m) :
	max(m), elems((int *)malloc(m * sizeof(int))), pos(0)
{
	if (NULL == elems)
		throw "construct fail!";
}

STACK::STACK(const STACK &s) throw () :
	max(s.size()), pos(s.pos), elems((int *)malloc(s.max * sizeof(int)))
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
	// TODO: �ڴ˴����� return ���
	if (max <= pos)
		throw "range_error";
	else {
		elems[pos++] = e;
	}
	return *this;
}

STACK & STACK::operator>>(int & e)
{
	// TODO: �ڴ˴����� return ���
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
	// TODO: �ڴ˴����� return ���
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
	STACK(m), s2(m) {

}

QUEUE::QUEUE(const QUEUE& s) :
	STACK(s), s2(s) {

}

QUEUE::operator int() const {
	return STACK::operator int() + inStack;
}

int QUEUE::full() const {
	if (inStack.size() <= inStack) {//��ջ��
		if (STACK::operator int()) {//��ջ�ǿ�
			return 1;
		}
	}
	return 0;
}

int QUEUE::operator [](int x) const {
	int res;
	if (x >= STACK::operator int()) {
		try {
			res = inStack[x - STACK::operator int()];
		}
		catch (char *) {
			throw "range_error!";
			res = -1;
		}
	}
	else {
		try {
			res = STACK::operator[](STACK::operator int() - x - 1);
		}
		catch (char *) {
			throw "range_error!";
			res = -1;
		}
	}
	return res;
}

QUEUE& QUEUE::operator<<(int e) {
	if (full()) {
		throw "range_error";
	}
	else {
		try {
			inStack << e;
		}
		catch (char *) {
			while (inStack) {
				int temp;
				inStack >> temp;
				STACK::operator<<(temp);
			}
			inStack << e;
		}
	}
	return *this;
}

QUEUE& QUEUE::operator>>(int &e) {
	if (!inStack && !STACK::operator int()) {
		throw"range_error";
	}
	try {
		STACK::operator>>(e);
	}
	catch (char *) {
		while (inStack) {
			int temp;
			inStack >> temp;
			STACK::operator<<(temp);
		}
		STACK::operator>>(e);
	}
	return *this;
}

QUEUE& QUEUE::operator=(const QUEUE&s) {
	try {
		inStack = s.inStack;
		STACK::operator=((STACK)s);
	}
	catch (char *) {
		throw"new fail!";
	}
	return *this;
}

std::string QUEUE::getprint() const {
	std::stringstream res;
	for (int i = 0; i < (*this); i++) {
		res << (*this)[i] << " ";
	}
	std::string end = *this == 0 ? "" : res.str();
	return end;
}

void QUEUE::print() const {
	std::cout << getprint() << std::endl;
}
QUEUE::~QUEUE() {
	//STACK::~STACK();
}

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
	//system("type D:\\WorkSpace\\VS_C\\Cpp_expericen\\Project1\\Debug\\Project6.txt");
	printf("\n");
	//system("pause");
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
