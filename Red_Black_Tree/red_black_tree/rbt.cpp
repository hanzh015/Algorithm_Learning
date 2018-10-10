#include "stdafx.h"
#include "rbt.h"

rbNode::rbNode()
{

}

rbNode::rbNode(Ncolor c)
{
	color_=c;
}

rbNode::rbNode(double k)
{
	key_=k;
}

rbNode::rbNode(double k,Ncolor c)
{
	key_=k;
	color_=c;
}

void rbNode::upDate()
{
	key_=low_;
}

rbNode::~rbNode()
{

}

rbTree::rbTree()
{
	nil_=new rbNode(NBLACK);
	nil_->id_=-1;
	root_=nil_;
}

rbTree::~rbTree()
{
	delete nil_;
}

//define rotation operation
void rbTree::leftRotation(rbNode *pivot)
{
	if(pivot->rchild_==nil_)
	{
		std::cout<<"invalid leftRotation,rchild of pivot is nil."<<std::endl;
		return;
	}
	else
	{
		rbNode *y=pivot->rchild_;
		pivot->rchild_=y->lchild_;
		if(y->lchild_!=nil_)
		{
			y->lchild_->parent_=pivot;
		}
		y->parent_=pivot->parent_;
		if(pivot->parent_==nil_)
		{
			root_=y;
		}
		else if(pivot==pivot->parent_->lchild_)
		{
			pivot->parent_->lchild_=y;
		}
		else
		{
			pivot->parent_->rchild_=y;
		}
		y->lchild_=pivot;
		pivot->parent_=y;
	}

}

void rbTree::rightRotation(rbNode *pivot)
{
	if(pivot->lchild_==nil_)
	{
		std::cout<<"invalid leftRotation,lchild of pivot is nil."<<std::endl;
		return;
	}
	else
	{
		rbNode *y=pivot->lchild_;
		pivot->lchild_=y->rchild_;
		if(y->rchild_!=nil_)
		{
			y->rchild_->parent_=pivot;
		}
		y->parent_=pivot->parent_;
		if(pivot->parent_==nil_)
		{
			root_=y;
		}
		else if(pivot==pivot->parent_->rchild_)
		{
			pivot->parent_->rchild_=y;
		}
		else
		{
			pivot->parent_->lchild_=y;
		}
		y->rchild_=pivot;
		pivot->parent_=y;
	}

}

//define travelsal operation
void rbTree::preOrderTravelsal(rbNode *s)
{
	if(s==nil_)
	{
		return;
	}
	else
	{
		printf("No.%d,key=%.2f,\t",s->id_,s->key_);
		if(s->color_==NBLACK)
		{
			printf("color:BLACK,\t");
		}
		else
		{
			printf("color:RED,\t");
		}
		printf("left child is No.%d,\tright child is No.%d\n",
			s->lchild_->id_,s->rchild_->id_);
		preOrderTravelsal(s->lchild_);
		preOrderTravelsal(s->rchild_);
	}
}

void rbTree::inOrderTravelsal(rbNode *s)
{
	if(s==nil_)
	{
		return;
	}
	else
	{
		inOrderTravelsal(s->lchild_);
		printf("No.%d,key=%.2f,\t",s->id_,s->key_);
		if(s->color_==NBLACK)
		{
			printf("color:BLACK,\t");
		}
		else
		{
			printf("color:RED,\t");
		}
		printf("left child is No.%d,\tright child is No.%d\n",
			s->lchild_->id_,s->rchild_->id_);
		inOrderTravelsal(s->rchild_);
	}
}

void rbTree::postOrderTravelsal(rbNode *s)
{
	if(s==nil_)
	{
		return;
	}
	else
	{
		postOrderTravelsal(s->lchild_);
		postOrderTravelsal(s->rchild_);
		printf("No.%d,key=%.2f,\t",s->id_,s->key_);
		if(s->color_==NBLACK)
		{
			printf("color:BLACK,\t");
		}
		else
		{
			printf("color:RED,\t");
		}
		printf("left child is No.%d,\tright child is No.%d\n",
			s->lchild_->id_,s->rchild_->id_);
	}
}

rbNode *rbTree::max_(rbNode *rt)
{
	if(rt==nil_)
	{
		std::cout<<"invalid max inquiry:root node is nil!"<<std::endl;
		return 0;
	}
	else
	{
		rbNode *y=rt->rchild_;
		while(y!=nil_)
		{
			rt=y;
			y=y->rchild_;
		}
		return rt;
	}
}

rbNode *rbTree::min_(rbNode *rt)
{
	if(rt==nil_)
	{
		std::cout<<"invalid max inquiry:root node is nil!"<<std::endl;
		return 0;
	}
	else
	{
		rbNode *y=rt->lchild_;
		while(y!=nil_)
		{
			rt=y;
			y=y->lchild_;
		}
		return rt;
	}
}

rbNode* rbTree::precessor(rbNode *cur_)
{
	if(cur_->lchild_!=nil_)
	{
		return min_(cur_->lchild_);
	}
	rbNode *y=cur_->parent_;
	while(y!=nil_&&cur_==y->lchild_)
	{
		cur_=y;
		y=y->parent_;
	}
	return y;
}

rbNode* rbTree::successor(rbNode *cur_)
{
	if(cur_->rchild_!=nil_)
	{
		return min_(cur_->rchild_);
	}
	rbNode *y=cur_->parent_;
	while(y!=nil_&&cur_==y->rchild_)
	{
		cur_=y;
		y=y->parent_;
	}
	return y;
}

void rbTree::insert(rbNode *newnode)
{
	rbNode *y=nil_;
	rbNode *x=root_;
	while(x!=nil_)
	{
		y=x;
		if(newnode->key_<x->key_)
		{
			x=x->lchild_;
		}
		else
		{
			x=x->rchild_;
		}
	}
	newnode->parent_=y;
	if(y==nil_)
	{
		root_=newnode;
	}
	else if(newnode->key_<y->key_)
	{
		y->lchild_=newnode;
	}
	else
	{
		y->rchild_=newnode;
	}
	newnode->lchild_=newnode->rchild_=nil_;
	newnode->color_=NRED;
	insert_fixup(newnode);
}

void rbTree::insert_fixup(rbNode *newnode)
{
	rbNode *y;
	while(newnode->parent_->color_==NRED)
	{
		if(newnode->parent_==newnode->parent_->parent_->lchild_)
		{
			y=newnode->parent_->parent_->rchild_;
			if(y->color_==NRED)
			{
				newnode->parent_->color_=NBLACK;
				y->color_=NBLACK;
				newnode->parent_->parent_->color_=NRED;
				newnode=newnode->parent_->parent_;
			}
			else 
			{
				if(newnode==newnode->parent_->rchild_)
				{
					newnode=newnode->parent_;
					leftRotation(newnode);
				}
				newnode->parent_->color_=NBLACK;
				newnode->parent_->parent_->color_=NRED;
				rightRotation(newnode->parent_->parent_);
			}
		}
		else
		{
			y=newnode->parent_->parent_->lchild_;
			if(y->color_==NRED)
			{
				newnode->parent_->color_=NBLACK;
				y->color_=NBLACK;
				newnode->parent_->parent_->color_=NRED;
				newnode=newnode->parent_->parent_;
			}
			else 
			{
				if(newnode==newnode->parent_->lchild_)
				{
					newnode=newnode->parent_;
					rightRotation(newnode);
				}
				newnode->parent_->color_=NBLACK;
				newnode->parent_->parent_->color_=NRED;
				leftRotation(newnode->parent_->parent_);
			}
		}
	}
	root_->color_=NBLACK;
}

