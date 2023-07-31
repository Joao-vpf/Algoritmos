const int MAXN = 100005; 

vector<int> adj[MAXN];
int parent[MAXN][20]; // Matriz de ancestrais (20 é o valor máximo para log2(MAXN))

void dfs(int u, int par) 
{
    parent[u][0] = par; // Definir o ancestral imediato de u como par

    // Calcular os ancestrais de u usando o princípio do "duplicar para subir"
    for (int i = 1; i < 20; i++) 
    {
        if (parent[u][i - 1] != -1) 
            parent[u][i] = parent[parent[u][i - 1]][i - 1];
        else
            parent[u][i] = -1;
    }

    // Recursão para os filhos de u
    for (int v : adj[u]) 
    {
        if (v != par) 
            dfs(v, u);
    }
}

int lca(int u, int v) 
{
    // Certificar-se de que u está mais profundamente enraizado do que v
    if (depth[u] < depth[v]) 
    {
        swap(u, v);
    }

    // Elevar u para a mesma profundidade de v
    for (int i = 19; i >= 0; i--) 
    {
        if (depth[u] - (1 << i) >= depth[v]) 
        {
          
            u = parent[u][i];
        }
    }

    // Se v era ancestral direto de u, o LCA é v
    if (u == v)
    {
        return u;
    }

    // Elevar u e v simultaneamente até encontrarem o LCA
    for (int i = 19; i >= 0; i--) 
    {
        if (parent[u][i] != parent[v][i]) 
        {
            u = parent[u][i];
            v = parent[v][i];
        }
    }

    return parent[u][0];
}

//inicialização
for (int i = 1; i <= n; i++) 
{
    adj[i].clear();
    for (int j = 0; j < 20; j++) 
    {
        parent[i][j] = -1;
    }
}
