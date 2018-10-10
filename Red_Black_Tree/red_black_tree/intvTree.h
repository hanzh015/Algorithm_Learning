#pragma once
#include "rbt.h"

class intvTree :
	public rbTree
{
public:
	intvTree(void);

	void insert(rbNode *newnode);
	double upDateMax(rbNode *s);

	rbNode *search_(double low,double high);
	void inOrderTravelsal(rbNode *s);

	~intvTree(void);
};

