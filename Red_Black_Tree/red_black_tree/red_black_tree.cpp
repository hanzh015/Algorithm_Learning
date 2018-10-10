// red_black_tree.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "rbt.h"
#include "intvTree.h"
#include "time.h"
#define NODENUMBER 20
#define KEYRANGE 1000

int main()
{
	//create rb-tree general

	rbNode nodes[NODENUMBER];
	rbTree *T;
	T=new rbTree();
	srand((unsigned)time(NULL));
	for(int i=0;i<NODENUMBER;i++)
	{
		nodes[i].id_=i;
		nodes[i].key_=rand()%(KEYRANGE+1);
		T->insert(&nodes[i]);
	}
	T->inOrderTravelsal(T->root_);
	std::cout<<"max key of nodes:"<<T->max_(T->root_)->key_<<std::endl;
	std::cout<<"min key of nodes:"<<T->min_(T->root_)->key_<<std::endl;

	int randnum=rand()%(NODENUMBER);
	std::cout<<"a random node id is\t"<<randnum<<"\tkey:\t"<<nodes[randnum].key_<<std::endl;
	std::cout<<"its precessor is:"<<std::endl;
	std::cout<<"id:\t"<<T->precessor(&(nodes[randnum]))->id_<<"\tkey:\t"
		<<T->precessor(&(nodes[randnum]))->key_<<std::endl;
	std::cout<<"its successor is:"<<std::endl;
	std::cout<<"id:\t"<<T->successor(&(nodes[randnum]))->id_<<"\tkey:\t"
		<<T->successor(&(nodes[randnum]))->key_<<std::endl;
	delete T;




	std::cout<<"---------------------Now testing interval tree:---------------------\n"<<std::endl;

	intvTree *Tree;
	rbNode intvnodes[NODENUMBER];
	Tree = new intvTree();
	srand((unsigned)time(NULL));
	for(int i=0;i<NODENUMBER;i++)
	{
		intvnodes[i].id_=i;
		intvnodes[i].low_=rand()%(KEYRANGE+1);
		intvnodes[i].high_=intvnodes[i].low_+rand()%(KEYRANGE+1);
		intvnodes[i].upDate();
		Tree->insert(&intvnodes[i]);
	}
	Tree->inOrderTravelsal(Tree->root_);


	std::cout<<"***************testing success case***************"<<std::endl;
	rbNode *testsearch=new rbNode();
	rbNode *searchresult;
	randnum=rand()%(NODENUMBER);
	testsearch->low_=intvnodes[randnum].low_-1;				//To ensure there is at least 1 interval that overlap our target one
	testsearch->high_=intvnodes[randnum].high_-1;			//However the result is not guaranteed to be the only one.
	testsearch->upDate();
	searchresult=Tree->search_(testsearch->low_,testsearch->high_);
	printf("target search interval: low:%.2f,\t high:%.2f\n",testsearch->low_,testsearch->high_);
	printf("result interval: id:%d,low:%.2f\t high:%.2f\n\n",searchresult->id_,searchresult->low_,searchresult->high_);


	std::cout<<"***************testing failed case1***************"<<std::endl;
	searchresult=Tree->search_(Tree->root_->maxtime_+1,Tree->root_->maxtime_+2);		//fail due to i.min>i'.max
	printf("target search interval: low:%.2f,\t high:%.2f\n",Tree->root_->maxtime_+1,Tree->root_->maxtime_+2);
	if(searchresult==Tree->nil_)
	{
		std::cout<<"search failed!"<<std::endl;
	}
	else
	{
		printf("result interval: id:%d,low:%.2f\t high:%.2f\n\n",searchresult->low_,searchresult->high_);
	}


	std::cout<<"***************testing failed case2***************"<<std::endl;
	searchresult=Tree->search_(-2,-1);					//fail due to i.max<i'.low
	printf("target search interval: low:%.2f,\t high:%.2f\n",-2,-1);
	if(searchresult==Tree->nil_)
	{
		std::cout<<"search failed!"<<std::endl;
	}
	else
	{
		printf("result interval: id:%d,low:%.2f\t high:%.2f\n\n",searchresult->low_,searchresult->high_);
	}
	delete Tree;


	getchar();
	return 0;

}

