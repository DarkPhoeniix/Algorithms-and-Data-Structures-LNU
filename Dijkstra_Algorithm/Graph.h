#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

const int INF = INT_MAX;

class Graph
{
public:
	Graph();
	~Graph();

	int getVertexNum() const;
	int getValue(const int& row, const int& column) const;
	bool checkConnectivity() const;
	std::pair<int, std::string> findShortestPath(const int& start, const int& end) const;

	friend std::ostream& operator<<(std::ostream& out, const Graph& g);
	friend std::istream& operator>>(std::istream& in, Graph& g);

private:
	int vertexNum;
	std::vector<std::vector<int>> matrix;
};
