vector<vector<int>> adj(N);
// Implementação do algoritmo de busca em profundidade (DFS) para encontrar aumentos de caminho
bool dfs(int u, const vector<vector<int>>& graph, vector<int>& matchA, vector<int>& matchB, vector<bool>& visited) {
    if (visited[u])
        return false;

    visited[u] = true;

    for (int v : graph[u]) {
        if (matchB[v] == -1 || dfs(matchB[v], graph, matchA, matchB, visited)) {
            matchA[u] = v;
            matchB[v] = u;
            return true;
        }
    }

    return false;
}

// Implementação do Teorema de König para encontrar o emparelhamento máximo
int konigTheorem(const vector<vector<int>>& graph, int A, int B) {
    int n = A + B;

    vector<int> matchA(A, -1);
    vector<int> matchB(B, -1);
    vector<bool> visited(A, false);

    int matching = 0;

    for (int i = 0; i < A; ++i) {
        fill(visited.begin(), visited.end(), false);
        if (dfs(i, graph, matchA, matchB, visited)) {
            ++matching;
        }
    }

    return matching;
}
