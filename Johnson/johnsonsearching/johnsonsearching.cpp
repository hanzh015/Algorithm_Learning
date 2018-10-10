// johnsonsearching.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "graph.h"
#include <crtdbg.h>
#include "Dijkstra.h"
#include "BellmanFord.h"
#include "Johnson.h"

int main()
{
	_CrtSetDbgFlag(_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) | _CRTDBG_LEAK_CHECK_DF);
	graph test;
	test.InitGraph(20,19);
// 	Dijkstra djks(&test);
// 	djks.DKShortest(5);
 	BellmanFord bmfd(&test);
 	bmfd.BFShortest(5);
	test.PrintGraph();
// 	printf("---------------dijkstra-------------\n");
// 	djks.PrintShortest();
	printf("---------------bellmanfd------------\n");
	bmfd.PrintShortest();

	Johnson js(&test);
	js.JohnsonShortestPairs();
	printf("--------------Johnson---------------\n");
	js.PrintDtable();
	printf("\n");
	js.PrintPath(15,5);

	getchar();
	return 0;
}

