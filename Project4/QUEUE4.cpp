//#include "QUEUE4.h"
//
//QUEUE::QUEUE(int m) :
//	max(m),elems((int *)malloc(m*sizeof(int)))
//{
//	head = tail = 0;
//	if (NULL == elems) {
//		throw "construct fail";
//	}
//}
//
//QUEUE::QUEUE(const QUEUE & s) :
//	QUEUE(s.max)
//{
//	for (int i = s.tail; i != s.head; i = (i+1)%max) {
//		elems[head] = s.elems[i];
//		head = (head + 1) % max;
//	}
//}
//
//QUEUE::operator int() const
//{
//	return ((head + max) - tail) % max;
//}
//
//int QUEUE::full() const
//{
//	return ((head + 1) % max == tail) ? 1 : 0;
//}
//
//int QUEUE::operator[](int x) const
//{
//	if (x < 0 || x >= (int)(*this)) {
//		throw "range_error";
//		return -1;
//	}
//	else {
//		return elems[(tail + x) % max];
//	}
//}
//
//QUEUE & QUEUE::operator<<(int e)
//{
//	if (full())
//		throw "range_error";
//	else {
//		elems[head] = e;
//		head = (head + 1) % max;
//	}
//	return *this;
//}
//
//QUEUE & QUEUE::operator>>(int & e)
//{
//	// TODO: 在此处插入 return 语句
//	if (head == tail)
//		throw "range_error";
//	else {
//		e = elems[tail];
//		tail = (tail + 1) % max;
//	}
//	return *this;
//}
//
//QUEUE & QUEUE::operator=(const QUEUE & s)
//{
//	// TODO: 在此处插入 return 语句
//	const_cast<int &>(max) = s.max;
//	const_cast<int *>(elems) = new int[max];
//	if (NULL == elems) {
//		throw "new fail!";
//	}
//	tail = head = 0;
//	for (; head < s; head++) {
//		elems[head] = s[head];
//	}
//	return *this;
//}
//
//void QUEUE::print() const
//{
//	std::cout << getprint() << std::endl;
//}
//
//std::string QUEUE::getprint() const
//{
//	std::stringstream res;
//	for (int i = 0; i < *this; i++) {
//		res << (*this)[i] << " ";
//	}
//	std::string end = *this == 0 ? "" : res.str();
//	return end;
//}
//
//QUEUE::~QUEUE()
//{
//	free(elems);
//	const_cast<int &>(max) = 0;
//	tail = head = 0;
//}
//
//
//
//
