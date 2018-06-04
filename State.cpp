#include <iostream>
#include <algorithm>
#include <queue>
#include <set>
using namespace std;

class State
{
	struct action
	{
		pair<int, int> a;
		pair<int, int> b;
	};
	
	public:
		
	static int poolHeight;
	static int matHeight;
	static int matWidth;
	static int maxscore;
	static int maxswaps;
	static int devices;

	vector<vector<int>> state;
	State *parent;
	action act;
	int score;
	int actionCount;
	
	State()
	{
		score = 0;
		actionCount = 0;
		parent = NULL;
		state = vector<vector<int>>();
	}
	
	State(vector<vector<int>> st)
	{
		state = st;
		score = 0;
		actionCount = 0;
		parent = NULL;
	}
	
	#include "matrixOperations.cpp"
	
	void generateMoves(priority_queue<State, vector<State>, State>& frontier, set<State>& explored, set<State>& frontier_set)
	{
		cout<<"generate moves with actionCount "<<actionCount<<endl;
		if(actionCount >= maxswaps)
			return;
		vector<vector<int> > current = state;
//		testMatrix();
//		score += simulateGravity();
//		explored.insert(*this);
		cout<<"new score "<<score<<endl;
		cout<<"entering row matches "<<endl;
		for(int i=poolHeight;i<matHeight;i++)
		{
			for(int j=0;j<matWidth-1;j++)
			{
//				cout<<"checking for swaps "<<i<<' '<<j<<" and "<<i<<' '<<j+1<<endl;
				if(state[i][j] != state[i][j+1])
				{
					swap(state[i][j], state[i][j+1]);
//					printState();
					if(rowCheck(i, false) || colCheck(j, false) || colCheck(j+1, false))
					{
						pair<int,int> a(i,j);
						pair<int,int> b(i,j+1);
						State st = ChildNode(a,b);
						st.state = state;
						st.testMatrix();
						st.score += st.simulateGravity();
						if(!explored.count(st) && !frontier_set.count(st))
						{
							cout<<"not in e and f, this is obtained by swapping "<<endl;
							cout<<st.act.a.first<<' '<<st.act.a.second<<" and "<<st.act.b.first<<' '<<st.act.b.second<<endl;
//							st.printState();
							frontier.push(st);
							frontier_set.insert(st);
						}
						else
						{
							cout<<"this state already seen before"<<endl;
							cout<<endl<<endl<<endl;
						}
					}
					swap(state[i][j], state[i][j+1]);
				}
			}
		}
//		cout<<"looking for column matches"<<endl;
		cout<<"entering col matches "<<endl;
		for(int k=poolHeight;k<matHeight-1;k++)
		{
			for(int l=0;l<matWidth;l++)
			{
//				cout<<"checking for swaps "<<k<<' '<<l<<" and "<<k+1<<' '<<l<<endl;
				if(state[k][l] != state[k+1][l])
				{
					swap(state[k][l], state[k+1][l]);
//					printState();
					if(rowCheck(k, false) || colCheck(l, false) || rowCheck(k+1, false))
					{
						pair<int,int> a(k,l);
						pair<int,int> b(k+1,l);
						State st = ChildNode(a,b);
						st.state = state;
						st.testMatrix();
						st.score += st.simulateGravity();
						if(!explored.count(st) && !frontier_set.count(st))
						{
							cout<<"not in e and f, this is obtained by swapping "<<endl;
							cout<<st.act.a.first<<' '<<st.act.a.second<<" and "<<st.act.b.first<<' '<<st.act.b.second<<endl;							
//							st.printState();
							frontier.push(st);
							frontier_set.insert(st);
						}
						else
						{
							cout<<"this state already seen before"<<endl;
							cout<<endl<<endl<<endl;
//							st.printState();
						}							
					}
					swap(state[k][l], state[k+1][l]);
				}
			}
		}
	}
	
	State ChildNode(pair<int, int> a, pair<int, int> b)
	{
		State st;
		st.act.a = a;
		st.act.b = b;
		st.score = score;
		st.actionCount = this->actionCount + 1;
		st.parent = this;
		vector<vector<int>> temp = st.parent->state;
		swap(temp[a.first][a.second], temp[b.first][b.second]);
		return st;
	}
	
	bool GoalState()
	{
		return score >= maxscore;
	}
	
	bool operator<(const State& st) const
	{
		vector<vector<int>> vec = st.state;
		for(int i=poolHeight;i<matHeight;i++)
		{
			for(int j=0;j<matWidth;j++)
			{
				if(vec[i][j] != this->state[i][j])
				return vec[i][j] < this->state[i][j];
			}
		}
		return false;
	}
	
	void printState()
	{
		for(int i=0;i<matHeight;i++)
		{
			for(int j=0;j<matWidth;j++)
			{
				cout<<state[i][j]<<' ';
			}
			cout<<endl;
		}
	}
	
	bool operator()(State a, State b)
	{
		return a < b;
	}
	
};

int State::poolHeight = 0;
int State::matHeight = 0;
int State::matWidth = 0;
int State::maxscore = 0;
int State::maxswaps = 0;
int State::devices = 0;
