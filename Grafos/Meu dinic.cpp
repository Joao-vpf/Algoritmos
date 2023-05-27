
struct edge {
    int v=0;            // Vértice de destino da aresta
    int flow=0;         // Fluxo atual da aresta
    int cap=0;     // Capacidade máxima da aresta
    int rev=0;  // Índice da aresta reversa
    
};
vector<edge> adj[1001];
vector<int> level;

void add_edge(int u, int v, int cap) 
{
    adj[u].push_back({v, 0, cap, int(adj[v].size())});
    adj[v].push_back({u, 0, 0,int(adj[u].size())});
}

bool bfs(int source, int sink) 
{
    level.assign(sink + 1, -1);
    level[source] = 0;
    queue<int> q;
    q.push(source);

    while (!q.empty()) 
    {
        int u = q.front();
        q.pop();

        for (const auto& e : adj[u]) 
        {
            if (level[e.v] < 0 && e.flow < e.cap) 
            {
                level[e.v] = level[u] + 1;
                q.push(e.v);
            }
        }
    }

    return level[sink] >= 0;
}

int dfs(int u, int sink, int flow) 
{
    if (u == sink)
    {
        return flow;
    }
    
    for (auto& e : adj[u]) 
    {
        if (level[e.v] == level[u] + 1 && e.flow < e.cap) 
        {
            int minFlow = min(flow, e.cap - e.flow);     
            int delta = dfs(e.v, sink, minFlow);

            if (delta > 0) 
            {
                e.flow += delta;
                adj[e.v][e.rev].flow -= delta;
                return delta;
            }
        }
    }

    return 0;
}
int dinic(int source, int sink) 
{
    int maxFlow = 0;

    while (bfs(source, sink)) 
    {
        int flow;
        while ((flow = dfs(source, sink, INT_MAX)) > 0)
            maxFlow += flow;
    }

    return maxFlow;
}
