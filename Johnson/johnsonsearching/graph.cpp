#include "StdAfx.h"
#include "graph.h"


graph::graph(void)
{
	vnumber=-1;
	Adj=NULL;
}


graph::~graph(void)
{
	if(Adj)
	{
		for(size_t i=0;i<vnumber;i++)
		{
			DelChain(Adj[i]);
		}
		delete Adj;
	}
	if(vertex)
	{
		delete vertex;
	}

}

bool graph::InsertEdge(struct edge *newedge,int src_index)
{
	if(src_index>vnumber-1)
	{
		return false;
	}
	else
	{
		if(SearchEdge(src_index,newedge->des_num))
		{
			return false;
		}
		else
		{
			struct edge *E=Adj[src_index];
			if(E)
			{
				while(E->next)
				{
					E=E->next;
				}
				E->next=newedge;
				E->next->next=NULL;
				return true;
			}
			else
			{
				Adj[src_index]=newedge;
				Adj[src_index]->next=NULL;
				return true;
			}
		}
	}

}

struct edge* graph::SearchEdge(int src, int des)
{
	struct edge *E;
	if(src>vnumber-1)
	{
		return NULL;
	}
	else
	{
		E=Adj[src];
		while(E)
		{
			if(E->des_num==des)
			{
				return E;
			}
			E=E->next;
		}
		return NULL;
	}
}

bool graph::DelEdge(int src, int des)
{
	struct edge *E=SearchEdge(src,des);
	if(E)
	{
		struct edge *point=Adj[src];
		if(point->des_num==des)
		{
			Adj[src]=NULL;
			return true;
		}
		else
		{
			while(point->next)
			{
				if(point->next->des_num==des)
				{
					point->next=point->next->next;
					delete point->next;
					return true;
				}
				point=point->next;
			}
			return false;
		}

	}
	else
	{
		return false;
	}
}

void graph::InitGraph(int nodenumber,int edgerange)
{
	Adj=new struct edge *[nodenumber];
	for(size_t i=0;i<nodenumber;i++)
	{
		Adj[i]=NULL;
	}
	vertex=new int[nodenumber];
	vnumber=nodenumber;
	struct edge *p;
	srand((unsigned)time(NULL));
	for(size_t i=0;i<edgerange;i++)
	{
		struct edge *p;
		int edge_number;
		edge_number=rand()%6+5;
		for(size_t j=0;j<edge_number;j++)
		{
			p=new struct edge;
			p->next=NULL;
			do 
			{
				p->des_num=rand()%(edgerange);
				if(p->des_num==i)
				{
					delete p;
					break;
				}
				p->weight=rand()%31;
			} while (!InsertEdge(p,i));
		}

	}
}

bool graph::ModifyWeight(int src,int des,int weight)
{
	struct edge *p;
	p=SearchEdge(src,des);
	if(p)
	{
		p->weight=weight;
		return true;
	}
	else
	{
		return false;
	}
}

void graph::DelChain(struct edge *p)
{
	if(p)
	{
		if(p->next)
		{
			DelChain(p->next);
			delete p;
			return;
		}
		else
		{
			delete p;
			return;
		}
	}
	else
	{
		return;
	}
}

void graph::PrintGraph()
{
	if(Adj==NULL)
	{
		printf("Graph is empty\n");
	}
	else
	{
		printf("vertex number\tedge/weight\n");
		struct edge *p;
		for(size_t i=0;i<vnumber;i++)
		{
			p=Adj[i];
			printf("%d\t",i);
			while(p)
			{
				printf("%d/%d\t",p->des_num,p->weight);
				p=p->next;
			}
			printf("\n");
		}
	}
}