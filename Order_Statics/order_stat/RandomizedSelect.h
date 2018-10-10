#pragma once
#include "OrderSelect.h"

using namespace std;
class RandomizedSelect :
	public OrderSelect
{
public:
	RandomizedSelect(int s,int range);
	RandomizedSelect(int s,int *ay);

	~RandomizedSelect(void);

	int select_(int p,int r,int i);

private:
	int randomizedPartition(int p,int r);
};

