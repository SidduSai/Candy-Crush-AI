#include <iostream>
using namespace std;

void printSolution(State st)
{
	cout<<"inside the printsolution functions "<<endl;
	cout<<"actions is "<<st.act.a.first<<' '<<st.act.a.second<<" and "<<st.act.b.first<<' '<<st.act.b.second<<endl;
	State *par = st.parent;
	while(par != NULL)
	{
		cout<<"actions is "<<par->act.a.first<<' '<<par->act.a.second<<" and "<<par->act.b.first<<' '<<par->act.b.second<<endl;
		par = par->parent;
	}
}

bool GraphSearch(State state)
{
	priority_queue<State, vector<State>, State> frontier;
	state.testMatrix();
	state.score += state.simulateGravity();
	frontier.push(state);
	set<State> explored;
	set<State> frontier_set;
	do
	{
		if(frontier.empty())
		{
			cout<<"frontier empty "<<endl;
			return false;
		}
//		cout<<"assigning new state "<<endl;
		State st = frontier.top();
		cout<<"frontier size "<<frontier.size()<<"frontier set size "<<frontier_set.size()<<" score "<<st.score<<endl;
		frontier.pop();
		frontier_set.erase(st);
		st.printState();
		if(st.GoalState())
		{
			cout<<"goal found"<<endl;
			st.printState();
//			printSolution(st);
			return true;
		}
		cout<<"adding to explored "<<endl;
		explored.insert(st);
		cout<<"explored one layer, explored size is "<<explored.size()<<endl;
		st.generateMoves(frontier, explored, frontier_set);
	}while(!frontier.empty());
}
