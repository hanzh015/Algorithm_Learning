//this is the header file of rb tree basic
#pragma once
#include <iostream>
#include <stdio.h>

enum Ncolor 
{
	NRED=0,
	NBLACK=1,
};

class rbNode
{
public:
	rbNode();
	//Three ways to initial a new node

	rbNode(Ncolor c);
	rbNode(double k);
	rbNode(double k,Ncolor c);

	void upDate();

	virtual  ~rbNode();

	Ncolor color_;
	double key_;
	int id_;			//to help us identify each node
	double low_;
	double high_;
	double maxtime_;

	rbNode *parent_;
	rbNode *rchild_;
	rbNode *lchild_;

};

class rbTree
{
public:
	rbTree();
	virtual ~rbTree();


	rbNode *root_;								//root
	rbNode *nil_;								//sentinel
								

	virtual void insert(rbNode *newnode);
	void insert_fixup(rbNode *newnode);
	void preOrderTravelsal(rbNode *s);			//Traveling print each node and its relationship 
												//with children and parent
	void inOrderTravelsal(rbNode *s);
	void postOrderTravelsal(rbNode *s);

	rbNode *max_(rbNode *rt);
	rbNode *min_(rbNode *rt);

	rbNode *precessor(rbNode *cur_);
	rbNode *successor(rbNode *cur_);

	void leftRotation(rbNode *pivot);
	void rightRotation(rbNode *pivot);


};