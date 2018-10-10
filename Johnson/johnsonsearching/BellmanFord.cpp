#include "StdAfx.h"
#include "BellmanFord.h"


BellmanFord::BellmanFord(graph *G):SingleSrcShortest(G)
{
}


BellmanFord::~BellmanFord(void)
{
}

bool BellmanFord::BFShortest(int src)
{
	struct edge *p;
	InitSingleSrc(src);
	for(size_t i=0;i<g->vnumber-1;i++)
	{
		for(int j=0;j<g->vnumber;j++)
		{
			p=g->Adj[j];
			while(p)
			{
				RelaxEdge(j,p->des_num);
				p=p->next;
			}
		}
	}
	for(int j=0;j<g->vnumber;j++)
	{
		p=g->Adj[j];
		while(p)
		{
			if(vinfo[p->des_num].d>vinfo[j].d+p->weight)
			{
				return false;
			}
			p=p->next;
		}
	}
	return true;
}