#include"STACK3.h"

STACK::STACK(int m) throw ():
	max(m),elems((int *)malloc(m*sizeof(int))),pos(0)
{
	if (NULL == elems)
		throw "construct fail!";
}

STACK::STACK(const STACK &s) throw ():
	max(s.size()), pos(s),elems((int *)malloc(s.max* sizeof(int))) 
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
	}else
		return elems[x];
}

STACK & STACK::operator<<(int e)
{
	// TODO: 在此处插入 return 语句
	if (max <= pos)
		throw "range_error";
	else{
		elems[pos++] = e;
	}
	return *this;
}

STACK & STACK::operator>>(int & e)
{
	// TODO: 在此处插入 return 语句
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
	// TODO: 在此处插入 return 语句
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