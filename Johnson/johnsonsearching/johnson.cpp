#include "StdAfx.h"
#include "Johnson.h"


Johnson::Johnson(graph *G)
{
	g=G;
	hlist=new djn[g->vnumber];
	dtable=new djn *[g->vnumber];
	for(int i=0;i<g->vnumber;i++)
	{
		dtable[i]=new djn[g->vnumber];
	}


}


Johnson::~Johnson(void)
{
	if(hlist)
	{
		delete hlist;
	}
	if(dtable)
	{
		for(int i=0;i<g->vnumber;i++)
		{
			if(dtable[i])
			{
				delete dtable[i];
			}
		}
		delete dtable;
	}
}

void Johnson::ConstructSrc()
{
	struct edge *p,*q;
	q=g->Adj[g->vnumber-1]=new struct edge;
	q->des_num=0;
	q->weight=0;
	for(int i=1;i<g->vnumber-1;i++)
	{
		p=new struct edge;
		p->des_num=i;
		p->weight=0;
		p->next=NULL;
		q->next=p;
		q=q->next;
	}

}

bool Johnson::Reweighting()
{
	BellmanFord bmf(g);
	if(bmf.BFShortest(g->vnumber-1))
	{
		bmf.Export(hlist);
		struct edge *p;
		for(int j=0;j<g->vnumber-1;j++)
		{
			p=g->Adj[j];
			while(p)
			{
				p->weight+=(-hlist[p->des_num].d+hlist[j].d);
				p=p->next;
			}
		}
		return true;
	}
	else
	{
		printf("bellmanford fail!\n");
		return false;
	}
	
}

void Johnson::RecoverWeights()
{
	struct edge *p;
	for(int j=0;j<g->vnumber-1;j++)
	{
		p=g->Adj[j];
		while(p)
		{
			p->weight+=(hlist[p->des_num].d-hlist[j].d);
			p=p->next;
		}
	}
}

void Johnson::JohnsonShortestPairs()
{
	ConstructSrc();
	if(!Reweighting())
	{
		return;
	}
	Dijkstra *djk;
	for(int i=0;i<g->vnumber-1;i++)
	{
		djk=new Dijkstra(g);
		djk->DKShortest(i);
		djk->Export(dtable[i]);
		for(int j=0;j<g->vnumber;j++)
		{
			(dtable[i][j]).d+=(hlist[j].d-hlist[i].d);
		}
		delete djk;
	}
	RecoverWeights();
}

bool Johnson::PrintPath(int src, int des)
{
	if(src==des)
	{
		printf("%d",src);
		return true;
	}
	else
	{
		if((dtable[src][des]).pi==-1)
		{
			return false;
		}
		else
		{
			PrintPath(src,(dtable[src][des]).pi);
			printf("-->%d",des);
			return true;
		}
	}
}

void Johnson::PrintDtable()
{
	printf("weight/pi\n");
	for(int i=0;i<g->vnumber-1;i++)
	{
		for(int j=0;j<g->vnumber-1;j++)
		{
			printf("%d/%d  ",(dtable[i][j]).d,(dtable[i][j]).pi);
		}
		printf("\n");
	}

}