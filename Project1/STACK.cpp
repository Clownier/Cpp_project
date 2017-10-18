#include "STACK.h"   //要使用stringstream流应包含此头文件 
using namespace std;
void initSTACK(STACK * const p, int m)
{
	//assert(p);
	p->elems = (int *)malloc(m * sizeof(int));
	if (NULL == p->elems) 
		exit(-1);
	p->max = m;
	p->pos = 0;
}

void initSTACK(STACK * const p, const STACK & s)
{
	if (NULL == s.elems) 
		exit(-1);
	p->elems = s.elems;
	p->max = s.max;
	p->pos = s.pos;
}

int size(const STACK * const p)
{
	if (NULL == p)
		return -1;
	return p->max;
}

int howMany(const STACK * const p)
{
	if (NULL == p || p->pos <= 0)
		return 0;
	return p->pos;
}

int getelem(const STACK * const p, int x)
{
	if (NULL == p || p->pos <= x)
		return -1;
	return p->elems[x];
}

STACK * const push(STACK * const p, int e)
{
	if (NULL == p)
		exit(-1);
	if (p->max <= p->pos) {
		p -> elems = (int *)realloc(p->elems, (p->max + 5) * sizeof(int));
		if (NULL == p->elems)
			exit(-1);
		p->max += 5;
	}
	p->elems[p->pos] = e;
	p->pos++;
	return p;
}

STACK * const pop(STACK * const p, int & e)
{
	if (NULL == p->elems|| 0 == p->pos)
		exit(-1);
	e = p->elems[--(p->pos)];
	return p;
}

STACK * const assign(STACK * const p, const STACK & s)
{
	if (NULL == p)
		exit(-1);
	p->elems = s.elems;
	p->max = s.max;
	p->pos = s.pos;
	return p;
}

std::string getprint(const STACK * const p)
{
	int i = 0;
	stringstream res;
	for (; i < p->pos; i++) {
		res <<p->elems[i]<<" ";
	}
	string end = p->pos!=0?res.str():"";
	return end;
}

void print(const STACK * const p)
{
	cout << getprint(p) << endl;
}

void destroySTACK(STACK * const p)
{
	free(p->elems);
	p->max = 0;
	p->pos = 0;
}

