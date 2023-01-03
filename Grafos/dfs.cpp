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
