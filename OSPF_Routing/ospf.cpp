// -----------------------------------------------------
// ospf.cpp
// Jeremy Campbell
// Uses Dijstra's Shortest Path algorithm to find the 
// shortest paths between routers in an OSPF area.
// -----------------------------------------------------
#include <iostream>
#include <fstream>
#include <vector>
#include <set>

using std::cerr;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::vector;
using std::set;

class OSPF_Area
{
public:
	explicit OSPF_Area(int numRouters);
	void inputAreaMap(ifstream &fin);
	void calculateShortestPaths(int startRouter);
	void printShortestPaths(ofstream &fout, int startRouter);

private:
	// Data (Speeds are measured in Bps)
	vector<vector<unsigned long long>> adjacency; 
	vector<int> parents;
	vector<unsigned long long> speeds;
	set<int> routers;

	// Methods
	void printAdjacency();
};

OSPF_Area::OSPF_Area(int numRouters)
{
	adjacency.resize(numRouters, vector<unsigned long long>(numRouters, 0));
	parents.resize(numRouters, -1);
	speeds.resize(numRouters, ULLONG_MAX);

	// Place routers in the set
	for (int i = 0; i < numRouters; i++)
		routers.insert(i);
}

void OSPF_Area::inputAreaMap(ifstream &fin)
{
	int numRouters = adjacency.size();
	for (int i = 0; i < numRouters; i++)
	{
		for (int j = 0; j < numRouters; j++)
		{
			unsigned long long Bps;
			fin >> Bps;
			adjacency[i][j] = Bps;
		}
	}

	//printAdjacency();
}

// Dijkstra's Shortest Path Algorithm
void OSPF_Area::calculateShortestPaths(int startRouter)
{
	set<int> t;
	speeds[startRouter] = 0;

	while (t != routers)
	{
		int selected; 
		unsigned long long smallestValue = ULLONG_MAX;

		for (int router : routers)
		{
			// for all the routers not in t that are in "routers"
			if (t.find(router) == t.end() && speeds[router] < smallestValue)
			{
				selected = router;
				smallestValue = speeds[router];
			}
		}

		t.insert(selected);

		for (int router : routers)
		{
			// for all routers not in t that are adjacent to selected
			if (t.find(router) == t.end() && adjacency[selected][router] != 0)
			{
				if (speeds[selected] + adjacency[selected][router] < speeds[router])
				{
					speeds[router] = speeds[selected] + adjacency[selected][router];
					parents[router] = selected;
				}
			}
		}
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

// Debug Method
void OSPF_Area::printAdjacency()
{
	cerr << "Adjacency: " << endl;
	cerr << "----------------------------------------" << endl;
	for (vector<unsigned long long> row : adjacency)
	{
		for (unsigned long long Bps : row)
		{
			cerr << Bps << " ";
		}
		cerr << endl;
	}
	cerr << "----------------------------------------" << endl;
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

		int startRouter;
		fin >> startRouter;
		while (startRouter != 0)
		{
			ospfArea.calculateShortestPaths(startRouter);
			ospfArea.printShortestPaths(fout, startRouter);
			fin >> startRouter;
		}
		
		fin >> numRouters;
		if (numRouters != 0)
			fout << "*****" << endl;
	}
}