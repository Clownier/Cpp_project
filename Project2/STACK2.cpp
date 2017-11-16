//#include "STACK2.h"
//
//STACK::STACK(int m) throw(char *) :
//	max(m),elems((int*)malloc(m * sizeof(int))),pos(0)
//{
//	if (NULL == elems)
//		throw "exception";
//}
//
//
//STACK::STACK(const STACK & s):
//	max(s.max),elems(s.elems),pos(s.pos)
//{
//}
//
//int STACK::size() const
//{
//	return max;
//}
//
//int STACK::howMany() const
//{
//	return pos;
//}
//
//int STACK::getelem(int x) const throw(char *)
//{
//	if (x >= pos)
//		throw "exception";
//	else 
//		return elems[x];
//	return -1;
//}
//
//STACK & STACK::push(int e)throw(char *)
//{
//	if (max <= pos)
//		throw "exception";
//	else {
//		elems[pos] = e;
//		pos++;
//	}
//	return *this;
//}
//
//STACK & STACK::pop(int & e) throw(char *)
//{
//	if (0 == pos)
//		throw "exception";
//	e = elems[--pos];
//	return *this;
//}
//
//STACK & STACK::assign(const STACK & s)
//{
//	const_cast<int *>(elems) = new int[s.max];
//	for (int i = 0; i < s.pos; i++) {
//		elems[i] = s.elems[i];
//	}
//	const_cast<int &>(max) = s.max;
//	pos = s.pos;
//	return *this;
//}
//
//std::string STACK::getprint() const
//{
//	std::stringstream res;
//	for (int i = 0; i < pos;i++) {
//		res << elems[i] << " ";
//	}
//	std::string end = pos != 0 ? res.str(): "";
//	return end;
//}
//void STACK::print() const
//{
//	std::cout << getprint()<< std::endl;
//}
//
//STACK::~STACK()
//{
//	if (elems) {
//		free(elems);
//		const_cast<int &>(max) = 0;//const_cast change const data
//		pos = 0;
//	}
//
//
//}
