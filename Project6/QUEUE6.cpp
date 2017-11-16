//#include "QUEUE6.h"
//
//QUEUE::QUEUE(int m) :
//	STACK(m), s2(m) {
//
//}
//
//QUEUE::QUEUE(const QUEUE& s) :
//	STACK(s), s2(s) {
//
//}
//
//QUEUE::operator int() const {
//	return STACK::operator int() + inStack;
//}
//
//int QUEUE::full() const {
//	if (inStack.size() <= inStack) {//ÈëÕ»Âú
//		if (STACK::operator int()) {//³öÕ»·Ç¿Õ
//			return 1;
//		}
//	}
//	return 0;
//}
//
//int QUEUE::operator [](int x) const {
//	int res;
//	if (x >= STACK::operator int()) {
//		try {
//			res = inStack[x - STACK::operator int()];
//		}
//		catch (char *) {
//			throw "range_error!";
//			res = -1;
//		}
//	}
//	else {
//		try {
//			res = STACK::operator[](STACK::operator int() - x - 1);
//		}
//		catch (char *) {
//			throw "range_error!";
//			res = -1;
//		}
//	}
//	return res;
//}
//
//QUEUE& QUEUE::operator<<(int e) {
//	if (full()) {
//		throw "range_error";
//	}
//	else {
//		try {
//			inStack << e;
//		}
//		catch (char *) {
//			while (inStack) {
//				int temp;
//				inStack >> temp;
//				STACK::operator<<(temp);
//			}
//			inStack << e;
//		}
//	}
//	return *this;
//}
//
//QUEUE& QUEUE::operator>>(int &e) {
//	if (!inStack && !STACK::operator int()) {
//		throw"range_error";
//	}
//	try {
//		STACK::operator>>(e);
//	}
//	catch (char *) {
//		while (inStack) {
//			int temp;
//			inStack >> temp;
//			STACK::operator<<(temp);
//		}
//		STACK::operator>>(e);
//	}
//	return *this;
//}
//
//QUEUE& QUEUE::operator=(const QUEUE&s) {
//	try {
//		inStack = s.inStack;
//		STACK::operator=((STACK)s);
//	}
//	catch (char *) {
//		throw"new fail!";
//	}
//	return *this;
//}
//
//std::string QUEUE::getprint() const {
//	std::stringstream res;
//	for (int i = 0; i < (*this); i++) {
//		res << (*this)[i] << " ";
//	}
//	std::string end = *this == 0 ? "" : res.str();
//	return end;
//}
//
//void QUEUE::print() const {
//	std::cout << getprint() << std::endl;
//}
//QUEUE::~QUEUE() {
//	//STACK::~STACK();
//}