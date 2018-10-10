#include "StdAfx.h"
#include "WorstCaseLinearSelect.h"


WorstCaseLinearSelect::WorstCaseLinearSelect(int s,int range):OrderSelect(s,range)
{
}

WorstCaseLinearSelect::WorstCaseLinearSelect(int s,int *ay):OrderSelect(s,ay)
{

}


WorstCaseLinearSelect::~WorstCaseLinearSelect(void)
{
	free(getArray());
}

void WorstCaseLinearSelect::sort_(int p,int r,int *A)
{
	int j,key;
	if(p>=r)
	{
		cout<<"invalid input:p>=r"<<endl;
	}
	else
	{
		for(int i=p+1;i<=r;i++)
		{
			key=A[i];
			j=i-1;
			while(j>=p&&A[j]>key)
			{
				A[j+1]=A[j];
				j=j-1;
			}
			A[j+1]=key;
		}
	}
}

int WorstCaseLinearSelect::Partition_(int p,int r,int *A,int key)
{
	int i,temp;
	//this partition function is modified from randomizedPartition,
	//here a pre-defined key is given
	//in order to reduce unnecessary waste, we assume those elements equal to
	//key---the pivot are put in the right pile,by which we can make sure every 
	//element in left pile is small than the pivot.
	//Additionally, we are sure that the pivot is among the elements but we don't
	//know it's index,so we search it during this process.

	//firstly, variables chk!
	if(p>=r)
	{
		cout<<"invalid input:p>=i"<<endl;
		return -1;
	}
	else
	{
		i=p-1;
		for(int j=p;j<r;j++)
		{
			//we check if the current element is key
			//if yes, swap it with the last element, then do routinely job
			//if no,go ahead
			if(A[j]==key)
			{
				temp=A[r];
				A[r]=key;
				A[j]=temp;
			}
			if(A[j]<key)
			{
				i++;
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

int WorstCaseLinearSelect::in_select_(int p,int r,int i,int *A)
{
	int *B;							//B is a dynamic int array,which stores the temporary medians of each group;
	int cptgpnumber=(r-p)/5;		//complete group number,exclude the last group with size less than 5(or5)
	int median;
	int pivot;
	int j=0;

	if(p==r)
	{
		return A[p];
	}
	else if(r-p+1<=5)
	{
		sort_(p,r,A);
		return A[p+i-1];
	}
	else 
	{
		B=(int *)malloc((cptgpnumber+1)*sizeof(int));

		while(j<cptgpnumber)
		{
			sort_(p+5*j,p+5*(j+1)-1,A);
			B[j]=A[p+5*j+2];
			j++;
		}
		switch((r-p+1)%5)
		{
		case 0:
			sort_(r-4,r,A);
			B[cptgpnumber]=A[r-2];
			break;
		case 1:
			B[cptgpnumber]=A[r];
			break;
		case 2:
			sort_(r-1,r,A);
			B[cptgpnumber]=A[r-1];
			break;
		case 3:
			sort_(r-2,r,A);
			B[cptgpnumber]=A[r-1];
			break;
		case 4:
			sort_(r-3,r,A);
			B[cptgpnumber]=A[r-2];
			break;
		default:
			break;
		}
		//next we recurse select_ function with the input B array, in order to find the median
		median=in_select_(0,cptgpnumber,cptgpnumber/2+1,B);
		/*cout<<"Median="<<median<<endl;*/
		free(B);

		pivot=Partition_(p,r,A,median);
		if(pivot-p+1==i)
		{
			return A[pivot];
		}
		else if(pivot-p+1<i)
		{
			return in_select_(pivot+1,r,i-(pivot-p+1),A);
		}
		else 
		{
			return in_select_(p,pivot-1,i,A);
		}
	}
}

int WorstCaseLinearSelect::select_(int p,int r,int i)
{
	return in_select_(p,r,i,getArray());
}