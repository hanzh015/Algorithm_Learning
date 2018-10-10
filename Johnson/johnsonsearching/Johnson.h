#pragma once
#include "BellmanFord.h"
#include "Dijkstra.h"
class Johnson
{
public:
	Johnson(graph *G);
	~Johnson(void);

	void JohnsonShortestPairs();
	bool PrintPath(int src, int des);
	void PrintDtable();

	graph *g;
	djn *hlist;
	djn **dtable;

private:
	bool Reweighting();
	void RecoverWeights();
	void ConstructSrc();

};

