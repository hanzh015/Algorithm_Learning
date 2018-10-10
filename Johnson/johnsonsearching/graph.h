#pragma once

#include <stdlib.h>
#include "time.h"
struct edge
{
	int des_num;	//number of this node
	int weight;
	struct edge *next;
};



class graph
{
public:
	graph(void);
	void InitGraph(int nodenumber,int edgerange);

	~graph(void);

	int vnumber;
	struct edge **Adj;
	int *vertex;			//this is for storing d info

	bool InsertEdge(struct edge *newedge,int src_index);
	bool DelEdge(int src, int des);
	struct edge *SearchEdge(int src, int des);
	bool ModifyWeight(int src,int des,int weight);
	
	void PrintGraph();

private:
	void DelChain(struct edge *p);


};

