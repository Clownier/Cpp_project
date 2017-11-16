//#include"QUEUE5.h"
//
//QUEUE::QUEUE(int m) :
//	s1(m), s2(m) {
//
//}
//
//QUEUE::QUEUE(const QUEUE & s) :
//	s1(s.s1.size()), s2(s.s2.size()) {
//
//}
//
//QUEUE::operator int() const {
//	return inStack + outStack;
//}
//
//int QUEUE::full() const {
//	if (inStack.size() <= inStack) {
//		if (outStack)
//			return 1;
//	}
//	return 0;
//}
//
//int QUEUE::operator[](int x) const {
//	int res;
//	if (x >= outStack) {
//		try {
//			res = inStack[x - outStack];
//		}
//		catch (char *) {
//			throw "range_error";
//			res = -1;
//		}
//	}
//	else {
//		try {
//			res = outStack[outStack - x - 1];
//		}
//		catch (char *) {
//			throw "range_error";
//			res = -1;
//		}
//	}
//	return res;
//}
//
//QUEUE& QUEUE::operator<<(int e) {
//	if (full()) {
//		throw "range_error";
//		return *this;
//	}
//	else {
//		try {
//			inStack << e;
//		}
//		catch (char *) {
//			while (inStack) {
//				int temp;
//				inStack >> temp;
//				outStack << temp;
//			}
//			inStack << e;
//		}
//	}
//	return *this;
//}
//
//QUEUE& QUEUE::operator>>(int &e) {
//	if (!outStack && !inStack)
//		throw "range_error";
//	try {
//		outStack >> e;
//	}
//	catch (char *) {
//		while (inStack) {
//			int temp;
//			inStack >> temp;
//			outStack << temp;
//		}
//		outStack >> e;
//	}
//	return *this;
//}
//
//QUEUE& QUEUE::operator=(const QUEUE&s) {
//	try {
//		inStack = s.inStack;
//		outStack = s.outStack;
//	}
//	catch (char *) {
//		throw "new fail!";
//	}
//	return *this;
//}
//
//std::string QUEUE::getprint() const {
//	std::stringstream res;
//	for (int i = 0; i < *this; i++) {
//		res << (*this)[i]<<" ";
//	}
//	std::string end = *this == 0 ? "" : res.str();
//	return end;
//}
//
//void QUEUE::print() const {
//	std::cout << getprint() << std::endl;
//}
//
//QUEUE::~QUEUE() {
//	//inStack.~STACK();
//	//outStack.~STACK();
//}