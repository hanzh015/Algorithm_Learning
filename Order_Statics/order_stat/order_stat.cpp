// order_stat.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "RandomizedSelect.h"
#include "WorstCaseLinearSelect.h"
#include "OrderSelect.h"
#include "time.h"
#include <fstream>
#include <Windows.h>

#define DATA_RANGE 1000000
#define DATA_NUMBER 1000
#define ITERATION_NUMBER 40
#define TEST_NUMBER 5			//run TEST_NUMBER times to either obtain average performance or get the range

bool createReportFile();
int main()
{
	int status;
	cout<<"please select work mode :"<<endl
		<<"1.Show you the demonstration of the performance of the two algorithm given those predefined parameters"<<endl
		<<"2.Generate a report file containing the performance under different conditions"<<endl;
	cin>>status;
	if(status==1)
	{
		time_t timep;
		int ors1,ors2;
		int test[DATA_NUMBER];
		char filename[64];

		OrderSelect *rs,*wcls;

		//this is for precise time counter
		LARGE_INTEGER freq;
		LARGE_INTEGER start_t,stop_t;

		double exe_time;

		QueryPerformanceFrequency(&freq);
		cout<<"Your PC frequency is:"<<freq.QuadPart<<endl;

		srand((unsigned)time(NULL));
		for(int i=0;i<DATA_NUMBER;i++)
		{
			test[i]=rand()%(DATA_RANGE+1);
		}

		/*ifstream data;*/
		// 	timep=time(0);
		// 	ofstream data;
		// 	strftime(filename,64,"%Y%m%d%H%M%S.csv",localtime(&timep));
		/*shit.open("20180322205949.csv");*/
		/*	data.open(filename);*/
		// 	if(data.is_open())
		// 	{
		// 		for(int j=0;j<DATA_NUMBER;j++)
		// 		{
		// 			/*data<<test[j]<<"\n";*/
		// 			data>>test[j];
		// 			/*cout<<test[j]<<endl;*/
		// 		}
		// 	}
		// 
		// 	data.close();

		rs=new RandomizedSelect(DATA_NUMBER,test);
		wcls=new WorstCaseLinearSelect(DATA_NUMBER,test);

		QueryPerformanceCounter(&start_t);
		ors1=rs->select_(0,DATA_NUMBER-1,6);
		QueryPerformanceCounter(&stop_t);
		exe_time=1e3*(stop_t.QuadPart-start_t.QuadPart)/freq.QuadPart;
		/*rs->print_();*/
		cout<<endl<<ors1<<endl;
		cout<<"Time consuming in RandomizedSelect Algorithm is:"<<exe_time<<" ms"<<endl;

		QueryPerformanceCounter(&start_t);
		ors2=wcls->select_(0,DATA_NUMBER-1,6);
		QueryPerformanceCounter(&stop_t);	
		exe_time=1e3*(stop_t.QuadPart-start_t.QuadPart)/freq.QuadPart;
		/*wcls->print_();*/
		cout<<endl<<ors2<<endl;
		cout<<"Time consuming in WorstCaseLinearSelect Algorithm is:"<<exe_time<<" ms"<<endl;

		delete rs;
		delete wcls;
	}
	else if(status==2)
	{
		status=createReportFile();
		if(status)
		{
			cout<<"Successfully created the report file!"<<endl;
		}
		else
		{
			cout<<"Fail to create the file!"<<endl;
		}
	}

	getchar();
	getchar();
	return 0;
}

bool createReportFile()
{
	time_t timep;
	int ors1,ors2;
	int test[DATA_NUMBER*ITERATION_NUMBER];
	int datanumber;
	char filename[64];
	double performance[ITERATION_NUMBER][TEST_NUMBER*2];

	OrderSelect *rs,*wcls;

	//this is for precise time counter
	LARGE_INTEGER freq;
	LARGE_INTEGER start_t,stop_t;

	double exe_time;

	QueryPerformanceFrequency(&freq);

	for(int i=0;i<ITERATION_NUMBER;i++)
	{
		datanumber=DATA_NUMBER*(i+1);
		for(int j=0;j<TEST_NUMBER;j++)
		{
			srand((unsigned)time(NULL));
			for(int k=0;k<datanumber;k++)
			{
				test[k]=rand()%(DATA_RANGE+1);
			}

			rs=new RandomizedSelect(datanumber,test);
			wcls=new WorstCaseLinearSelect(datanumber,test);

			QueryPerformanceCounter(&start_t);
			ors1=rs->select_(0,datanumber-1,6);
			QueryPerformanceCounter(&stop_t);
			exe_time=1e3*(stop_t.QuadPart-start_t.QuadPart)/freq.QuadPart;
			performance[i][j]=exe_time;

			QueryPerformanceCounter(&start_t);
			ors2=wcls->select_(0,datanumber-1,6);
			QueryPerformanceCounter(&stop_t);
			exe_time=1e3*(stop_t.QuadPart-start_t.QuadPart)/freq.QuadPart;
			performance[i][5+j]=exe_time;

			delete rs;
			delete wcls;
		}
	}

	ofstream report_data;
	timep=time(0);
 	strftime(filename,64,"%Y%m%d%H%M%S.csv",localtime(&timep));
	report_data.open(filename);
	if(report_data.is_open())
	{
		for(int l=0;l<ITERATION_NUMBER;l++)
		{
			report_data<<DATA_NUMBER*(l+1)<<",";
			for(int m=0;m<TEST_NUMBER*2;m++)
			{
				report_data<<performance[l][m]<<",";
			}
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
