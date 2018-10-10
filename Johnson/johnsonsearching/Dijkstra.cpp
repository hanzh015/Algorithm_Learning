#include "StdAfx.h"
#include "Dijkstra.h"


Dijkstra::Dijkstra(graph *G):SingleSrcShortest(G)
{
	marked=new int[g->vnumber];
	for(size_t i=0;i<g->vnumber;i++)
	{
		marked[i]=0;
	}
}


Dijkstra::~Dijkstra(void)
{
	if(marked)
	{
		delete marked;
	}
}

int Dijkstra::FindMin()
{
	int min_index=-1;
	int min_key=BIGNUMBER+1;
	for(size_t i=0;i<g->vnumber;i++)
	{
		if(marked[i])
		{
			continue;
		}
		else
		{
			if(vinfo[i].d<min_key)
			{
				min_key=vinfo[i].d;
				min_index=i;
			}
		}
	}
	return min_index;
}

void Dijkstra::DKShortest(int src)
{
	InitSingleSrc(src);
	int minindex;
	struct edge *p;
	for(size_t i=0;i<g->vnumber;i++)
	{
		minindex=FindMin();
		if(minindex==-1)
		{
			printf("oops\n");
		}
		marked[minindex]=1;
		p=g->Adj[minindex];
		while(p)
		{
			RelaxEdge(minindex,p->des_num);
			p=p->next;
		}

	}
}