#include "Graph.h"

Graph::Graph()
	: vertexNum(0)
{	}

Graph::~Graph()
{	}



int Graph::getVertexNum() const
{
	return this->vertexNum;
}

int Graph::getValue(const int& row, const int& column) const
{
	return this->matrix[row][column];
}

bool Graph::checkConnectivity() const {
	for (int i = 0; i < vertexNum; ++i) {
		if (std::count(matrix[i].begin(), matrix[i].end(), INF) == vertexNum - 1 && 
			std::count(matrix[i].begin(), matrix[i].end(), 0) == 1) {
			return false;
		}
	}
	return true;
}

std::pair<int, std::string> Graph::findShortestPath(const int& start, const int& end) const
{
	// Checks if graph is connected
	if (!checkConnectivity()) {
		throw std::exception("Graph is disconnected");
	}
	// Checks range of indexes
	if ((start >= 0 && start < this->vertexNum) &&
		(end >= 0 && end < this->vertexNum)) {
		if (start == end) {
			return std::make_pair(0, std::to_string(start));
		}
		// Result pair <distance, path>
		std::pair<int, std::string> path;

		std::vector<int> prevVertex(this->vertexNum, -2);
		std::vector<int> shortestPath(this->vertexNum, INF);
		std::vector<bool> visited(this->vertexNum, false);

		for (int i = 0; i < this->vertexNum; i++) {
			shortestPath[i] = this->matrix[start][i];
			if (matrix[start][i] != INF) {
				prevVertex[i] = start;
			}
		}

		shortestPath[start] = 0;
		prevVertex[start] = -1;
		visited[start] = true;
		int currentVertex = start;

		while (!visited[end]) {
			for (int i = 0; i < vertexNum; ++i) {
				// Checks if exists the shorter path to vertex [i]
				if (!visited[i] &&
					(shortestPath[currentVertex] + matrix[currentVertex][i] < shortestPath[i]) &&
					matrix[currentVertex][i] != INF) {
					shortestPath[i] = shortestPath[currentVertex] + matrix[currentVertex][i];
					prevVertex[i] = currentVertex;
				}
			}
			for (int i = 0; i < vertexNum; ++i) {
				// Finds the first unvisited vertex
				if (!visited[i]) {
					currentVertex = i;
					break;
				}
			}
			for (int i = 0; i < vertexNum; ++i) {
				// If path to [i] shorter than to [currentVertex] move to [i]
				if (shortestPath[i] < shortestPath[currentVertex] && !visited[i]) {
					currentVertex = i;
				}
			}
			visited[currentVertex] = true;
		}

		path.first = shortestPath[end];
		path.second = "";
		currentVertex = end;
		do {
			path.second.insert(0, std::to_string(currentVertex));
			path.second.insert(0, "->");
			currentVertex = prevVertex[currentVertex];
		} while (prevVertex[currentVertex] != -1);
		path.second.insert(0, std::to_string(start));

		return path;
	}
	else {
		std::string error;
		error = "Wrong index of vertixes: [" + std::to_string(start) + "; " + std::to_string(end) + ']';
		throw std::exception(error.c_str());
	}
}



std::ostream& operator<<(std::ostream& out, const Graph& g)
{
	out << "Number of vertexes: " << g.vertexNum << std::endl;
	for (int i = 0; i < g.vertexNum; ++i) {
		out << '|';
		for (int j = 0; j < g.vertexNum; ++j) {
			if (g.matrix[i][j] == INF) {
				out << std::setw(4) << "INF";
			}
			else {
				out << std::setw(4) << g.matrix[i][j];
			}

		}
		out << '|' << std::endl;
	}

	return out;
}

std::istream& operator>>(std::istream& in, Graph& g)
{
	std::string temp;
	in >> g.vertexNum;
	g.matrix.resize(g.vertexNum);
	for (int i = 0; i < g.vertexNum; ++i) {
		g.matrix[i].resize(g.vertexNum);
		for (int j = 0; j < g.vertexNum; ++j) {
			in >> temp;
			if (temp == "INF") {
				g.matrix[i][j] = INF;
			}
			else {
				g.matrix[i][j] = stoi(temp);
			}
		}
	}

	return in;
}
