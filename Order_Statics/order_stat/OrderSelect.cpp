#include "StdAfx.h"
#include "OrderSelect.h"


OrderSelect::OrderSelect(int s,int range)
{
	//s is the size of the array
	//range is the range of the array
	size=s;
	array_=(int*)malloc(s*sizeof(int));

	srand((unsigned)time(NULL));

	for(int i=0;i<s;i++)
	{
		array_[i]=rand()%(range+1);
	}
}

OrderSelect::OrderSelect(int s,int *ay)
{
	size=s;
	array_=(int*)malloc(s*sizeof(int));

	for(int i=0;i<s;i++)
	{
		array_[i]=ay[i];
	}
}


OrderSelect::~OrderSelect(void)
{
	
}

int *OrderSelect::getArray()
{
	return array_;
}

void OrderSelect::print_()
{
	int j=1;
	for(int i=0;i<size;i++)
	{
		cout<<array_[i]<<"\t";
		if(j%10==0)
		{
			j=0;
			cout<<endl;
		}
		j++;
	}
}