void bfs(int x, int pes) //peso diminui encontra limite
{
	dist[x]=pes;
	queue <int> q;
	q.push(x);
	while (!q.empty())
	{
		int u= q.front();
		q.pop();
		for (auto e : adj[u])
		{
			if (dist[e]==-1 && dist[u]>0)
			{
				dist[e]=dist[u]-1;
				q.push(e);
			}
		}
	}
}
