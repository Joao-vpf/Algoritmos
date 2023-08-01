
const int MAXN = 100001; // Tamanho máximo da árvore

vector<int> adj[MAXN]; // Lista de adjacências
int parent[MAXN]; // Vetor para armazenar o pai de cada nó na árvore
int depth[MAXN]; // Vetor para armazenar a profundidade de cada nó na árvore
int anc[MAXN][17]; // Vetor para armazenar os ancestrais de cada nó até o 2^17-ésimo pai (ou até a raiz)

// Função DFS para fazer o pré-processamento da árvore e preencher o vetor 'anc'
void dfs(int node, int par, int d) 
{
    parent[node] = par;
    depth[node] = d;

    for (int i = 0; i < adj[node].size(); i++) 
    {
        int child = adj[node][i];
        if (child != par)
            dfs(child, node, d + 1);
    }
}

// Função para calcular e preencher o vetor 'anc'
void precompute(int n) 
{
    for (int i = 1; i <= n; i++)
      {
        for (int j = 0; (1 << j) < n; j++) 
        {
            anc[i][j] = -1; // Inicializa todos os ancestrais como -1
        }
    }

    for (int i = 1; i <= n; i++) 
    {
        anc[i][0] = parent[i]; // O primeiro ancestral é o pai
    }

    for (int j = 1; (1 << j) < n; j++)
      {
        for (int i = 1; i <= n; i++) 
        {
            if (anc[i][j - 1] != -1)
            {
                anc[i][j] = anc[anc[i][j - 1]][j - 1]; // Preenche os ancestrais de acordo com a ideia do algoritmo
            }
        }
    }
}

// Função para encontrar o LCA entre dois nós 'u' e 'v'
int findLCA(int u, int v) 
{
    if (depth[u] < depth[v])
        swap(u, v); // Garante que 'u' esteja mais abaixo na árvore

    // Ajusta a profundidade de 'u' para ser a mesma de 'v'
    for (int i = 16; i >= 0; i--) 
    {
        if (depth[u] - (1 << i) >= depth[v]) 
        {
            u = anc[u][i];
        }
    }

    // Se 'u' já era ancestral de 'v', então 'u' é o LCA
    if (u == v)
        return u;

    // Encontra o LCA subindo a árvore a partir dos dois nós
    for (int i = 16; i >= 0; i--)
      {
        if (anc[u][i] != -1 && anc[u][i] != anc[v][i])
        {
            u = anc[u][i];
            v = anc[v][i];
        }
    }

    return parent[u];
}

