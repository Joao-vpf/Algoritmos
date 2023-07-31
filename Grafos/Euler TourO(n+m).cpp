vector<int> eulerTour;
vector<vector<int>> adj;
vector<bool> visited;

void dfs(int u) 
{
    visited[u] = true;
    eulerTour.push_back(u);

    for (int e : adj[u]) 
    {
        if (!visited[e]) 
        {
            dfs(e);
            eulerTour.push_back(u); // Volta ao nó atual após explorar o vizinho
        }
    }
}
