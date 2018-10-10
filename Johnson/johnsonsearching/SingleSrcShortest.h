#pragma once
#include "stdafx.h"
#include "graph.h"


typedef struct djnode
{
	int vindex;
	int d;
	int pi;

	bool operator >(const djnode b)const{return this->d>b.d;}
	bool operator <(const djnode b)const{return this->d<b.d;};
	bool operator <=(const djnode b)const{return this->d<=b.d;};
	bool operator >=(const djnode b)const{return this->d>=b.d;};
	bool operator ==(const djnode b)const{return this->d==b.d;};


}djn;


class SingleSrcShortest
{
public:
	SingleSrcShortest(graph *G);
	virtual ~SingleSrcShortest();

	void InitSingleSrc(int src);
	void RelaxEdge(int src,int des);
	void PrintShortest();
	void Export(djn *list);

	graph *g;
	djn *vinfo;

};

