#pragma once
#include "OrderSelect.h"
#include <iostream>

using namespace std;

class WorstCaseLinearSelect :
	public OrderSelect
{
public:
	WorstCaseLinearSelect(int s,int range);
	WorstCaseLinearSelect(int s,int *ay);

	~WorstCaseLinearSelect(void);

	int select_(int p,int r,int i);

private:
	void sort_(int p,int r,int *A);
	int Partition_(int p,int r,int *A,int key);
	int in_select_(int p,int r,int i,int *A);
	
};

