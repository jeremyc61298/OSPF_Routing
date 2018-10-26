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

int main()
{
	ifstream fin("ospf.in");
	if (!fin.is_open())
	{
		cerr << "Problem opening the input file. " << endl;
		return -1;
	}

	ofstream fout("ospf.out");

}