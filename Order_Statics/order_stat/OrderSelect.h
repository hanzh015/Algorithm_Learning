#pragma once
#include <iostream>
#include <ctime>

using namespace std;

class OrderSelect
{
public:
	OrderSelect(int s,int range);
	OrderSelect(int s,int *ay);

	virtual ~OrderSelect(void);

	virtual int select_(int p,int r,int i)=0;

	int *getArray();

	void print_();
private:
	int size;
	int *array_;
};

