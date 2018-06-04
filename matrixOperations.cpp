	bool rowCheck(int a, bool mark)
	{
		int count = 0;
		for(int i=0;i<matWidth-1;i++)
		{
			if(state[a][i] == state[a][i+1])
				count++;
			else if(count >= 2)
			{
				if(mark)
				{
					for(int j=i;j>=i-count;j--)
						state[a][j] = INT_MAX;
				}
				else
					return true;
			}
			else
				count = 0;
		}
		if(count >= 2)
		{
			if(mark)
			{
				int i = matWidth-1;
				for(int j=i;j>=i-count;j--)
					state[a][j] = INT_MAX;
			}
			else
				return true;
		}
		return false;
	}
	
	bool colCheck(int a, bool mark)
	{
		int count = 0;
		for(int i=poolHeight;i<matHeight-1;i++)
		{
			if(state[i][a] == state[i+1][a])
				count++;
			else if(count >= 2)
			{
				if(mark)
				{
					for(int j=i;j>=i-count;j--)
						state[j][a] = INT_MAX;
				}
				else
					return true;
			}
			else
				count = 0;
		}
		if(count >= 2)
		{
			if(mark)
			{
				int i = matHeight-1;
				for(int j=i;j>=i-count;j--)
					state[j][a] = INT_MAX;
			}
			else
				return true;
		}
		return false;
	}
	
	void testMatrix()
	{
		for(int i=poolHeight; i<matHeight; i++)
			rowCheck(i, true);
		for(int i=0; i<matWidth; i++)
			colCheck(i, true);
	}
	
	int simulateGravity()
	{
		cout<<"inside simuate gravity "<<endl;
//		printState();
//		cout<<"after simulation"<<endl;
		int count = 0;
		for(int i=poolHeight;i<matHeight;i++)
		{
			for(int j=0;j<matWidth;j++)
			{
				if(state[i][j] == INT_MAX)
				{
					count++;
					for(int k=i;k>0;k--)
						state[k][j] = state[k-1][j];
					state[0][j] = ((state[i][j] + (poolHeight - i) + j) % devices)+1;
					if(state[0][j] < 1)
					state[0][j] = 1;
				}
			}
		}
//		printState();
//		cout<<"count returning "<<count<<endl;
		return count;
	}
