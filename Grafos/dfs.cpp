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

//VARIAÇÕES
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

void dfsStack(int u) //dfs stack (confere por adjacência)
{
    stack<int> s;
    s.push(u);
    while (!s.empty())
    {
        int v = s.top();
        s.pop();
        vis[v] = true;
        for (auto e : adj[v])
        {
            if (!vis[e])
            {
                s.push(e);
            }
        }
    }
}

void dfs(int u, int j) //dfs conta o tempo de saida e de entrada;
{
    temp[u].first=timer++;
    for (int v :adj[u])
    {
        if(v!=j)
        {
            dfs(v,u);
        }
    }
    temp[v].second=timer++;
}
