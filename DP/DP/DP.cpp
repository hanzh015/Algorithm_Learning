// DP.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#define MIN -60000
#define DATA_NUMBER 20
#define DATA_RANGE 50
#include <fstream>
using namespace std;

void Matrix_Chain_Order(int *p, int len, int **m, int **s)
{
	int n = len-1;
	int j=0;
	int q;
	for(size_t i=0;i<n;i++)
	{
		m[i][i]=0;
	}
	for(size_t l=1;l<n;l++)
	{
		for(size_t i=0;i<n-l;i++)
		{
			j=i+l;
			m[i][j]=-1;
			for(size_t k=i;k<j;k++)
			{
				q=m[i][k]+m[k+1][j]+p[i]*p[k+1]*p[j+1];

				if(q<m[i][j]||m[i][j]==-1)
				{
					m[i][j]=q;
					s[i][j]=k;
				}
			}
		}
	}
}

void Print_Optimal_Parens(int **s,int i,int j)
{
	if(i==j)
	{
		printf("A%d",i);
	}
	else
	{
		printf("(");
		Print_Optimal_Parens(s,i,s[i][j]);
		Print_Optimal_Parens(s,s[i][j]+1,j);
		printf(")");
	}
}

struct maxSubArray
{
	int low_;
	int high_;
	int sum_;
};

maxSubArray CrossMax(int *Array,int l,int r,int mid);
maxSubArray Divide(int *Array,int l,int r)
{

	maxSubArray msa;
	maxSubArray lmsa;
	maxSubArray rmsa;
	maxSubArray crossmsa;
	int mid;

	if(l==r)
	{
		msa.low_=l;
		msa.high_=r;
		msa.sum_=Array[l];
		return msa;
	}
	else
	{
		mid=(l+r)/2;
		lmsa=Divide(Array,l,mid);
		rmsa=Divide(Array,mid+1,r);
		crossmsa=CrossMax(Array,l,r,mid);
		if(lmsa.sum_>=rmsa.sum_&&lmsa.sum_>=crossmsa.sum_)
		{
			return lmsa;
		}
		else if(rmsa.sum_>=lmsa.sum_&&rmsa.sum_>=crossmsa.sum_)
		{
			return rmsa;
		}
		else
		{
			return crossmsa;
		}
	}
}

maxSubArray CrossMax(int *Array,int l,int r,int mid)
{
	int sum=0;
	int lmax=MIN,rmax=MIN;
	int lcursor=mid,rcursor=mid+1;
	maxSubArray cross;

	for(int i=mid;i>=l;i--)
	{
		sum+=Array[i];
		if(sum>lmax)
		{
			lmax=sum;
			lcursor=i;
		}
	}
	sum=0;
	for(int j=mid+1;j<=r;j++)
	{
		sum+=Array[j];
		if(sum>rmax)
		{
			rmax=sum;
			rcursor=j;
		}
	}
	cross.low_=lcursor;
	cross.high_=rcursor;
	cross.sum_=lmax+rmax;
	return cross;
}

maxSubArray Greedy(int *Array,int l,int r)
{
	int sum=MIN,send_=0,lcursor,rcursor;
	int minsum=0;
	maxSubArray msa;
	//sum:candidate max sum
	//send_:sum of elements from l to current position
	//minsum: minimum sum of the first m elements
	//lcursor,rcursor: the candidate start and end position
	for(int i=l;i<=r;i++)
	{
		send_+=Array[i];
		if(send_<minsum)
		{
			minsum=send_;
			lcursor=i;
		}
		if(send_-minsum>sum)
		{
			sum=send_-minsum;
			rcursor=i;
		}
	}
	lcursor++;
	msa.low_=lcursor;
	msa.high_=rcursor;
	msa.sum_=sum;
	return msa;

}

bool createReportFile()
{
	time_t timep;
	/*int *test=(int *)malloc(sizeof(int)*pow(2.0,(2+DATA_NUMBER)));*/
	int test[1000*DATA_NUMBER];
	int datanumber;
	char filename[64];
	double performance[DATA_NUMBER][2];
	maxSubArray maxsa;

	//this is for precise time counter
	LARGE_INTEGER freq;
	LARGE_INTEGER start_t,stop_t;

	double exe_time;

	QueryPerformanceFrequency(&freq);

	for(int i=0;i<DATA_NUMBER;i++)
	{
		/*datanumber=pow(2.0,i);*/
		datanumber=1000*(i+1);
		srand((unsigned)time(NULL));
		for(int k=0;k<datanumber;k++)
		{
			test[k]=rand()%(DATA_RANGE+1)-DATA_RANGE/2;
		}

		QueryPerformanceCounter(&start_t);
		maxsa=Divide(test,0,datanumber-1);
		QueryPerformanceCounter(&stop_t);
		exe_time=1e3*(stop_t.QuadPart-start_t.QuadPart)/freq.QuadPart;
		performance[i][0]=exe_time;

		QueryPerformanceCounter(&start_t);
		maxsa=Greedy(test,0,datanumber-1);
		QueryPerformanceCounter(&stop_t);
		exe_time=1e3*(stop_t.QuadPart-start_t.QuadPart)/freq.QuadPart;
		performance[i][1]=exe_time;

	}
	/*free(test);*/

	ofstream report_data;
	timep=time(0);
	strftime(filename,64,"%Y%m%d%H%M%S.csv",localtime(&timep));
	report_data.open(filename);
	if(report_data.is_open())
	{
		for(int l=0;l<DATA_NUMBER;l++)
		{
			/*report_data<<pow(2.0,(l+3))<<",";*/
			report_data<<1000*(l+1)<<",";
			report_data<<performance[l][0]<<",";
			report_data<<performance[l][1]<<",";
			report_data<<"\n";
		}
		report_data.close();
		return true;
	}
	else
	{
		return false;
	}
}


int main()
{
	//----------------Matrix Chain Order-----------------//
	int p[7]={30,35,12,5,10,20,25};
	int len=7;
	int **m=(int **)malloc((len-1)*sizeof(int *));
	int **s=(int **)malloc((len-1)*sizeof(int *));
	for(size_t i=0;i<len-1;i++)
	{
		m[i]=(int *)malloc((len-1)*sizeof(int));
		s[i]=(int *)malloc((len-1)*sizeof(int));
	}
	

	Matrix_Chain_Order(p,len,m,s);
	Print_Optimal_Parens(s,0,5);
	printf("\n");

	//---------------Max Sub Array:Dividing--------------//
	int A[16]={13,-3,-25,20,-3,-16,-23,18,20,-7,12,-5,-22,15,-4,7};
	printf("****************testing dividing algorithm**********\n");
	maxSubArray maxsubarray1=Divide(A,0,15);
	printf("low=%d,  ",maxsubarray1.low_);
	printf("high=%d  ",maxsubarray1.high_);
	printf("sum=%d  \n",maxsubarray1.sum_);

	printf("****************testing greedy algorithm**********\n");
	maxSubArray maxsubarray2=Greedy(A,0,15);
	printf("low=%d,  ",maxsubarray2.low_);
	printf("high=%d  ",maxsubarray2.high_);
	printf("sum=%d  \n",maxsubarray2.sum_);

	printf("********Now generating report file please wait*********\n");
	if(createReportFile())
	{
		printf("Succeed\n");
	}
	else
	{
		printf("Unable to create report file\n");
	}

	getchar();


	return 0;
}

