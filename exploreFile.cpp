#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

void extractDataFromFile(int& quota, int &swaps, int &devtypes, int& m, int& n, int& pool, int& bonus, vector<vector<int>>& initial_state)
{
	string line;
	ifstream myfile("puzzle2.txt");
	if(myfile.is_open())
	{
		getline(myfile, line);
		quota = stoi(line, nullptr);
		State::maxscore = quota;
		getline(myfile, line);
		swaps = stoi(line, nullptr);
		State::maxswaps = swaps;
		getline(myfile, line);
		devtypes = stoi(line, nullptr);
		State::devices = devtypes;
		getline(myfile, line);
		m = stoi(line, nullptr);
		State::matWidth = m;
		getline(myfile, line);
		n = stoi(line, nullptr);
		State::matHeight = n;
		getline(myfile, line);
		pool = stoi(line, nullptr);
		State::poolHeight = pool;
		getline(myfile, line);
		bonus = stoi(line, nullptr);
		int i = 0;
		while (getline (myfile,line))
		{
			initial_state.push_back(vector<int>());
			stringstream iss(line);
			string subs;
			while(iss >> subs)
				initial_state[i].push_back(stoi(subs, nullptr));
			i++;
		}
		myfile.close();
	}
	else
		cout<<"unable to open the file"<<endl;
}
