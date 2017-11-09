#pragma once
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
	int  *const  elems;	//申请内存用于存放队列的元素
	const  int   max;	//elems能存放的最大元素个数
	int   head, tail;		//队列头和尾，队列空时head=tail;初始时head=tail=0
public:
	QUEUE(int m);		//初始化循环队列：elems有m个元素
	QUEUE(const QUEUE&s); 			//用队列s拷贝初始化队列
	virtual operator int() const;			//返回队列的实际元素个数
	virtual int full() const;		       //返回队列是否已满，满返回1，否则返回0
	virtual int operator[ ](int x)const;   //取下标为x的元素,第1个元素下标为0
	virtual QUEUE& operator<<(int e); 	//将e入队列,并返回队列
	virtual QUEUE& operator>>(int &e);	//出队列到e,并返回队列
	virtual QUEUE& operator=(const QUEUE&s); //赋s给队列,并返回被赋值的队列
	virtual void print() const;			//打印队列
	std::string getprint() const;		//赋s给栈,并返回被赋值的栈
	virtual ~QUEUE();					//销毁队列
};
