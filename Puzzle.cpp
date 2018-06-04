#include <iostream>
#include "state.cpp"
#include "GraphSearch.cpp"
#include "exploreFile.cpp"
using namespace std;

int main()
{
	int quota, swaps, devtypes, m, n, pool, bonus;
	vector<vector<int>> initial_state;
	extractDataFromFile(quota, swaps, devtypes, m, n, pool, bonus, initial_state);
	GraphSearch(State(initial_state));
}
