void bfs(int inicio, int fim) //estilo bfs "unidimensional" conta distancia
{
   for (int i=0; i<1000; i++)
   {
        dis[i]=-1;
   }
   dis[inicio]=0;
   queue <int> q;
   q.push(inicio);
    while (q.size())
    {
        int u = q.front();
        q.pop();
        for (auto e : adj[u])
        {
            if (dis[e]==-1)
            {
                dis[e]=dis[u]+1;
                q.push(e);
            }
        }
    }
}

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


