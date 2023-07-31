const int MAXN = 100000;

vector<int> tree[MAXN];
vector<int> subsize(MAXN, 0); // Tamanho de cada subtree
vector<bool> centroidRemoved(MAXN, false); // Nós que já foram removidos como centros
int centroidParent[MAXN]; // Pai de cada centroide
int n; // Número de nós na árvore

// Função para calcular o tamanho de cada subtree
void calculateSubtreeSize(int u, int parent) 
{
    subsize[u] = 1;
    for (int v : tree[u])
      {
        if (v != parent && !centroidRemoved[v]) 
        {
            calculateSubtreeSize(v, u);
            subsize[u] += subsize[v];
        }
    }
}

// Função para encontrar o centroide da árvore com raiz em u
int findCentroid(int u, int parent, int totalNodes) 
{
    for (int v : tree[u]) 
    {
        if (v != parent && !centroidRemoved[v] && subsize[v] > totalNodes / 2)
            return findCentroid(v, u, totalNodes);
    }
    return u;
}

// Função recursiva para decompor a árvore em centros
void decompose(int u, int parent) 
{
    calculateSubtreeSize(u, -1);
    int centroid = findCentroid(u, -1, subsize[u]);
    centroidRemoved[centroid] = true;
    centroidParent[centroid] = parent;

    // Processar subárvores menores
    for (int v : tree[centroid]) 
    {
        if (!centroidRemoved[v]) 
            decompose(v, centroid);
    }
}

// Função para inicializar a Centroid Decomposition
void centroidDecomposition() 
{
    decompose(0, -1); // Escolha o primeiro nó como raiz
}
