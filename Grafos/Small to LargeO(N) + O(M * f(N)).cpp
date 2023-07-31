const int MAXN = 100005;

vector<int> adj[MAXN];
int subtreeSize[MAXN];

//Função para calcular o tamanho da subárvore de cada nó
void calculateSubtreeSizes(int u, int parent) 
{
    subtreeSize[u] = 1;
    for (int v : adj[u]) 
    {
        if (v != parent) 
        {
            calculateSubtreeSizes(v, u);
            subtreeSize[u] += subtreeSize[v];
        }
    }
}

//Função para resolver o problema em uma subárvore específica
void solveSubtree(int u, int parent) 
{
    //lógica para resolver o problema em uma subárvore específica:

    //Recursivamente resolva o problema em subárvores menores
    for (int v : adj[u]) 
    {
        if (v != parent) 
        {
            solveSubtree(v, u);
        }
    }
}

//Função para resolver o problema na árvore inteira usando Small to Large
void solveTree(int root) 
{
    calculateSubtreeSizes(root, -1);
    solveSubtree(root, -1);
}
