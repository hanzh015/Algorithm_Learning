#include "StdAfx.h"
#include "SingleSrcShortest.h"

SingleSrcShortest::SingleSrcShortest(graph *G)
{
	g=G;
	vinfo=new djn[G->vnumber];
	for(size_t i=0;i<G->vnumber;i++)
	{
		vinfo[i].vindex=i;
	}
}


SingleSrcShortest::~SingleSrcShortest()
{
	if(vinfo)
	{
		delete vinfo;
	}
}

void SingleSrcShortest::InitSingleSrc(int src)
{
	for(size_t i=0;i<g->vnumber;i++)
	{
		vinfo[i].d=BIGNUMBER;
		vinfo[i].pi=-1;
	}
	vinfo[src].d=0;
}

void SingleSrcShortest::RelaxEdge(int src,int des)
{
	struct edge *p=g->SearchEdge(src,des);
	if(p)
	{
		if(vinfo[des].d>(vinfo[src].d+p->weight))
		{
			vinfo[des].d=vinfo[src].d+p->weight;
			vinfo[des].pi=src;
		}
	}
}

void SingleSrcShortest::PrintShortest()
{
	int point;
	for(size_t i=0;i<g->vnumber;i++)
	{
		point=i;
		while(vinfo[point].pi!=-1)
		{
			printf("%d-->",point);
			point=vinfo[point].pi;
		}
		printf("%d\n",point);
	}


}

void SingleSrcShortest::Export(djn *list)
{
	for(size_t i=0;i<g->vnumber;i++)
	{
		list[i].d=vinfo[i].d;
		list[i].vindex=vinfo[i].vindex;
		list[i].pi=vinfo[i].pi;
	}
}