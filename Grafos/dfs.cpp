void dfs(int x)
{
    vis[x]=true;
    for (auto e : gr[x])
    {
        if(!vis[e])
        {
            dfs(e);
        }
    }
}


void dfs(int u) //dfs que analisa por adj
{
    queue <int> q;
    q.push(u);
    while (!q.empty())
    {
        int v = q.front();
        q.pop();
        vis[v]=false
        for (auto e : adj[v])
        {
            q.push(e);
        }
    }
}
