#include "StdAfx.h"
#include "RandomizedSelect.h"


RandomizedSelect::RandomizedSelect(int s,int range):OrderSelect(s,range)
{
}

RandomizedSelect::RandomizedSelect(int s,int *ay):OrderSelect(s,ay)
{

}


RandomizedSelect::~RandomizedSelect(void)
{
	free(getArray());
}

int RandomizedSelect::select_(int p,int r,int i)
{
	int q;
	int *A;
	
	A=getArray();
	if(p==r)
	{
		return A[p];
	}
	else
	{
		q=randomizedPartition(p,r);
		if(q-p+1==i)
		{
			return A[q];
		}
		else if(q-p+1>i)
		{
			return select_(p,q-1,i);
		}
		else
		{
			return select_(q+1,r,i-(q-p+1));
		}
	}
}

int RandomizedSelect::randomizedPartition(int p,int r)
{
	int temp;	//this is used for swapping elements
	int i,x,random;
	int *A;

	//first check variables
	if(p>=r)
	{
		cout<<"invalid input:partition fail due to that p equals to r or even bigger"<<endl;
		return p;
	}
	else
	{
		A=getArray();
		srand((unsigned)time(NULL));
		random=rand()%(r-p+1)+p;
		//swap A[random] with A[r];
		temp=A[random];
		A[random]=A[r];
		A[r]=temp;

		//using new A[r] as pivot
		x=A[r];
		i=p-1;
		for(int j=p;j<r;j++)
		{
			if(A[j]<=x)
			{
				i=i+1;
				temp=A[j];
				A[j]=A[i];
				A[i]=temp;
			}
		}
		temp=A[r];
		A[r]=A[i+1];
		A[i+1]=temp;
		return i+1;
	}
}