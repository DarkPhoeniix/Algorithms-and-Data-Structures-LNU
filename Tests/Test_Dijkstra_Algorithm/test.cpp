#include "gtest/gtest.h"
#include "../../Dijkstra_Algorithm/Graph.cpp"
#include <fstream>

std::ifstream fin("Data.txt");
Graph firstGraph,
	  secondGraph,
	  thirdGraph,
	  fourthGraph;

TEST(Test_Dijkstra_Algorithm, Test_Read_Graph) {
	fin >> firstGraph;
	std::vector<std::vector<int>> test = {	{0,   4,   INF, INF, INF, INF, INF, 8,   INF},
											{4,   0,   8,   INF, INF, INF, INF, 11,  INF},
											{INF, 8,   0,   7,   INF, 4,   INF, INF, 2  },
											{INF, INF, 7,   0,   9,   14,  INF, INF, INF},
											{INF, INF, INF, 9,   0,   10,  INF, INF, INF},
											{INF, INF, 4,   14,  10,  0,   2,   INF, INF},
											{INF, INF, INF, INF, INF, 2,   0,   1,   6  },
											{8,   4,   INF, INF, INF, INF, 1,   0,   7  },
											{INF, INF, 2,   INF, INF, INF, 6,   7,   0  } };
	for (int i = 0; i < firstGraph.getVertexNum(); ++i) {
		for (int j = 0; j < firstGraph.getVertexNum(); ++j) {
			EXPECT_EQ(test[i][j], firstGraph.getValue(i, j));
		}
	}
}

TEST(Test_Dijkstra_Algorithm, Test_Dijkstra_Algorithm_First_Graph) {
	EXPECT_EQ(firstGraph.findShortestPath(0, 4).first, 21);
	EXPECT_EQ(firstGraph.findShortestPath(0, 4).second, std::string("0->7->6->5->4"));

	EXPECT_EQ(firstGraph.findShortestPath(3, 7).first, 14);
	EXPECT_EQ(firstGraph.findShortestPath(3, 7).second, std::string("3->2->5->6->7"));

	EXPECT_EQ(firstGraph.findShortestPath(8, 1).first, 10);
	EXPECT_EQ(firstGraph.findShortestPath(8, 1).second, std::string("8->2->1"));

	EXPECT_EQ(firstGraph.findShortestPath(1, 6).first, 12);
	EXPECT_EQ(firstGraph.findShortestPath(1, 6).second, std::string("1->7->6"));

	EXPECT_EQ(firstGraph.findShortestPath(1, 7).first, 11);
	EXPECT_EQ(firstGraph.findShortestPath(1, 7).second, std::string("1->7"));
}

TEST(Test_Dijkstra_Algorithm, Test_Dijkstra_Algorithm_Second_Graph) {
	fin >> secondGraph;

	EXPECT_EQ(secondGraph.findShortestPath(1, 5).first, 17);
	EXPECT_EQ(secondGraph.findShortestPath(1, 5).second, std::string("1->3->5"));

	EXPECT_EQ(secondGraph.findShortestPath(0, 4).first, 22);
	EXPECT_EQ(secondGraph.findShortestPath(0, 4).second, std::string("0->5->3->4"));

	EXPECT_EQ(secondGraph.findShortestPath(1, 2).first, 10);
	EXPECT_EQ(secondGraph.findShortestPath(1, 2).second, std::string("1->2"));
}

TEST(Test_Dijkstra_Algorithm, Test_Dijkstra_Algorithm_Third_Graph) {
	fin >> thirdGraph;

	EXPECT_EQ(thirdGraph.findShortestPath(18, 10).first, 44);
	EXPECT_EQ(thirdGraph.findShortestPath(18, 10).second, std::string("18->1->0->17->6->9->10"));

	EXPECT_EQ(thirdGraph.findShortestPath(15, 9).first, 38);
	EXPECT_EQ(thirdGraph.findShortestPath(15, 9).second, std::string("15->4->16->0->17->6->9"));
	
	EXPECT_EQ(thirdGraph.findShortestPath(0, 9).first, 25);
	EXPECT_EQ(thirdGraph.findShortestPath(0, 9).second, std::string("0->17->6->9"));
	
	EXPECT_EQ(thirdGraph.findShortestPath(9, 2).first, 21);
	EXPECT_EQ(thirdGraph.findShortestPath(9, 2).second, std::string("9->10->2"));
	
	EXPECT_EQ(thirdGraph.findShortestPath(18, 15).first, 29);
	EXPECT_EQ(thirdGraph.findShortestPath(18, 15).second, std::string("18->1->0->16->4->15"));

	EXPECT_EQ(thirdGraph.findShortestPath(1, 14).first, 16);
	EXPECT_EQ(thirdGraph.findShortestPath(1, 14).second, std::string("1->0->14"));

	EXPECT_EQ(thirdGraph.findShortestPath(5, 19).first, 23);
	EXPECT_EQ(thirdGraph.findShortestPath(5, 19).second, std::string("5->20->11->19"));

	EXPECT_EQ(thirdGraph.findShortestPath(3, 13).first, 32);
	EXPECT_EQ(thirdGraph.findShortestPath(3, 13).second, std::string("3->4->16->0->7->13"));
}

TEST(Test_Dijkstra_Algorithm, Test_Zero_Path) {
	EXPECT_EQ(thirdGraph.findShortestPath(9, 9).first, 0);
	EXPECT_EQ(thirdGraph.findShortestPath(9, 9).second, std::string("9"));
}

TEST(Test_Dijkstra_Algorithm, Test_Wrong_Index) {
	try {
		EXPECT_EQ(thirdGraph.findShortestPath(21, 20).first, 29);
		EXPECT_EQ(thirdGraph.findShortestPath(21, 20).second, std::string("18->1->0->16->4->15"));
		EXPECT_ANY_THROW();
	}
	catch (...)
	{	}
}

TEST(Test_Dijkstra_Algorithm, Test_Unconnected_Grapg) {
	fin >> fourthGraph;
	//std::cout << fourthGraph << std::endl;
	try {
		fourthGraph.findShortestPath(3, 4);
		EXPECT_ANY_THROW();
	}
	catch (...) {}
}