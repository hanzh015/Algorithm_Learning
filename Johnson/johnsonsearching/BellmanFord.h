#pragma once
#include "SingleSrcShortest.h"

class BellmanFord:
	public SingleSrcShortest
{
public:
	BellmanFord(graph *G);
	~BellmanFord(void);

	bool BFShortest(int src);
};

