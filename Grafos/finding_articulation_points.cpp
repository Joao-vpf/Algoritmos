vector <int> adj[101], low(101,-1), par(101,-1), dist(101,-1);
vector <bool> ap(101,false);
int Time=1;
void dfs(int x)
{
	int filho=0;
	low[x]= dist[x] = Time;
	Time++;
	for (auto e : adj[x])
	{
		if (dist[e]==-1)
		{
			par[e]=x;
			filho++;
			dfs(e);
			low[x] = min(low[x], low[e]);
			if(par[x]==-1 && filho>1)
			{
				ap[x]=true;
			}
			else if(par[x]!=-1 && low[e]>=dist[x])
			{
				ap[x]=true;
			}
		}
		else if(par[x]!=e)
		{
			low[x] = min(low[x], dist[e]);
		}
	}
}
