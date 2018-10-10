#pragma once
#include "singlesrcshortest.h"
class Dijkstra :
	public SingleSrcShortest
{
public:
	Dijkstra(graph *G);
	~Dijkstra(void);
	
	int *marked;

	int FindMin();
	void DKShortest(int src);
};

