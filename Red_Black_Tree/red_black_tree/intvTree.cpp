#include "StdAfx.h"
#include "intvTree.h"


intvTree::intvTree(void):rbTree()
{
}


intvTree::~intvTree(void)
{
}


double intvTree::upDateMax(rbNode *s)
{
	double rmax,lmax,m;
	if(s->lchild_==nil_&&s->rchild_==nil_)
	{
		s->maxtime_=s->high_;
		return s->maxtime_;
	}
	else if(s->lchild_==nil_&&s->rchild_!=nil_)
	{
		rmax=upDateMax(s->rchild_);
		if(rmax>s->high_)
		{
			s->maxtime_=rmax;
			return s->maxtime_;
		}
		else
		{
			s->maxtime_=s->high_;
			return s->maxtime_;
		}
	}
	else if(s->lchild_!=nil_&&s->rchild_==nil_)
	{
		lmax=upDateMax(s->lchild_);
		if(lmax>s->high_)
		{
			s->maxtime_=lmax;
			return s->maxtime_;
		}
		else
		{
			s->maxtime_=s->high_;
			return s->maxtime_;
		}
	}
	else
	{
		lmax=upDateMax(s->lchild_);
		rmax=upDateMax(s->rchild_);
		m=s->high_;
		if(lmax>m)
		{
			m=lmax;
		}
		if(rmax>m)
		{
			m=rmax;
		}
		s->maxtime_=m;
		return s->maxtime_;

	}
}

void intvTree::insert(rbNode *newnode)
{
	rbTree::insert(newnode);
	upDateMax(root_);
}

rbNode *intvTree::search_(double low,double high)
{
	rbNode *x=root_;
	while(x!=nil_&&(low>=x->high_||high<=x->low_))
	{
		if(x->lchild_!=nil_&&x->lchild_->maxtime_>=low)
		{
			x=x->lchild_;
		}
		else
		{
			x=x->rchild_;
		}
	}
	return x;
}

void intvTree::inOrderTravelsal(rbNode *s)
{
	if(s==nil_)
	{
		return;
	}
	else
	{
		inOrderTravelsal(s->lchild_);
		printf("No.%d,key=%.2f,\t,low=%.2f,high=%.2f,",s->id_,s->key_,s->low_,s->high_);
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