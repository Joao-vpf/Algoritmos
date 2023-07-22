

const int MAX_N = 2e5 + 5;

vector<int> adj[MAX_N];
bool vis[MAX_N], st[MAX_N];
vector<int> cycle;

bool dfs(int v) 
{
    vis[v] = true;
    st[v] = true;
    cycle.push_back(v);

    for (int u : adj[v])
    {
        if (!vis[u]) 
        {
            if (dfs(u))
                return true;
        } else if (st[u]) 
        {
            cycle.push_back(u);
            return true;
        }
    }

    cycle.pop_back();
    st[v] = false;
    return false;
}
