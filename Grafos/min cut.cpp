

// Estrutura para representar uma aresta no grafo
struct Edge {
    int src, dest;
};

vector<Edge> adj[N]

// Função auxiliar para encontrar o representante de um conjunto
int findParent(vector<int>& parent, int node) {
    if (parent[node] == node)
        return node;
    return findParent(parent, parent[node]);
}

// Função auxiliar para fazer a união de dois conjuntos
void unionSets(vector<int>& parent, int x, int y) {
    int xParent = findParent(parent, x);
    int yParent = findParent(parent, y);
    parent[yParent] = xParent;
}

// Função principal para o algoritmo de Min Cut
int minCut(vector<Edge>& edges, int n) {
    // Inicializa o vetor de representantes de conjuntos
    vector<int> parent(n);
    for (int i = 0; i < n; i++) {
        parent[i] = i;
    }

    // Continua o processo até que reste apenas 2 vértices
    while (n > 2) {
        // Escolhe aleatoriamente uma aresta para contrair
        int randomEdge = rand() % edges.size();

        // Encontra os vértices de origem e destino da aresta escolhida
        int src = findParent(parent, edges[randomEdge].src);
        int dest = findParent(parent, edges[randomEdge].dest);

        // Se os representantes dos conjuntos dos vértices forem diferentes,
        // a aresta não forma um ciclo e, portanto, pode ser contraída
        if (src != dest) {
            // Reduz o número de vértices
            n--;

            // Contrai a aresta (faz a união dos conjuntos dos vértices)
            unionSets(parent, src, dest);
        }

        // Remove a aresta do vetor de arestas
        edges[randomEdge] = edges.back();
        edges.pop_back();
    }

    // Conta o número de arestas restantes, que representa o corte mínimo
    return edges.size();
}
