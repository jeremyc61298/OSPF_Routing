// -----------------------------------------------------
// ospf.cpp
// Jeremy Campbell
// Uses Dijstra's Shortest Path algorithm to find the 
// shortest paths between routers in an OSPF area.
// -----------------------------------------------------
#include <iostream>
#include <fstream>
#include <vector>

using std::cerr;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::vector;

class OSPF_Area
{
public:
	explicit OSPF_Area(int numRouters);
	void inputAreaMap(ifstream &fin);
	void calculateShortestPaths();
	void printShortestPaths(ofstream &fout, vector<int> startingRouters);

private:
	vector<vector<int>> adjacency;

	void printShortestPaths(ofstream &fout, int startRouter);
};

OSPF_Area::OSPF_Area(int numRouters)
{
	adjacency.resize(numRouters, vector<int>(numRouters, 0));
}

void OSPF_Area::inputAreaMap(ifstream &fin)
{

}

// Dijkstra's Shortest Path Algorithm
void OSPF_Area::calculateShortestPaths()
{

}

void OSPF_Area::printShortestPaths(ofstream &fout, vector<int> startRouters)
{
	for (int router : startRouters)
	{
		printShortestPaths(fout, router);
	}
}

void OSPF_Area::printShortestPaths(ofstream &fout, int startRouter)
{
	//TODO: Print all the paths from the startRouter

	if (startRouter != 0)
		fout << " ";
	else
		fout << endl;
}

int main()
{
	ifstream fin("ospf.in");
	if (!fin.is_open())
	{
		cerr << "Problem opening the input file. " << endl;
		return -1;
	}

	ofstream fout("ospf.out");
	int numRouters;
	fin >> numRouters;
	OSPF_Area ospfArea(numRouters);

	while (numRouters != 0)
	{
		ospfArea.inputAreaMap(fin);
		ospfArea.calculateShortestPaths();

		// Read in the routers wanted to start from
		vector<int> startRouters;
		int startRouter;
		fin >> startRouter;
		while (startRouter != 0)
		{
			startRouters.push_back(startRouter);
		}

		ospfArea.printShortestPaths(fout, startRouters);
		
		fin >> numRouters;
		if (numRouters != 0)
			fout << "*****" << endl;
	}
}