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
	std::string getprint() const;		//��s��ջ,�����ر���ֵ��ջ
	virtual ~QUEUE();					//���ٶ���
};
