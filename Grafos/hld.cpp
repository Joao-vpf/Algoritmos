
struct Edge {
    int to, weight;
    Edge(int _to, int _weight) : to(_to), weight(_weight) {}
};

class HLDGraph {
private:
    int n; // Número de vértices
    vector<vector<Edge>> adj_list;
    vector<int> parent, depth, subtree_size, chain_head, chain_pos, chain_idx, chain_size, edge_weight;
    vector<int> chain_total_weight;
    vector<vector<int>> chain_edges;

    // Função DFS para calcular o tamanho da subárvore de cada vértice e o pai de cada vértice
    void dfs(int node, int parent_node, int current_depth) {
        parent[node] = parent_node;
        depth[node] = current_depth;
        subtree_size[node] = 1;

        for (const Edge& edge : adj_list[node]) {
            if (edge.to != parent_node) {
                dfs(edge.to, node, current_depth + 1);
                subtree_size[node] += subtree_size[edge.to];
            }
        }
    }

    // Função para construir as cadeias pesadas (chains)
    void hld(int node, int weight, int chain_head_node) {
        chain_head[node] = chain_head_node;
        chain_pos[node] = chain_size[chain_head_node]++;
        chain_idx[node] = chain_edges[chain_head_node].size();
        chain_edges[chain_head_node].push_back(node);
        edge_weight[node] = weight;
        chain_total_weight[chain_head_node] += weight;

        int heavy_child = -1;
        int max_subtree_size = -1;

        for (const Edge& edge : adj_list[node]) {
            if (edge.to != parent[node] && subtree_size[edge.to] > max_subtree_size) {
                max_subtree_size = subtree_size[edge.to];
                heavy_child = edge.to;
            }
        }

        if (heavy_child != -1) {
            hld(heavy_child, edge_weight[heavy_child], chain_head_node);
        }

        for (const Edge& edge : adj_list[node]) {
            if (edge.to != parent[node] && edge.to != heavy_child) {
                hld(edge.to, edge.weight, edge.to);
            }
        }
    }

    // Função para encontrar o LCA (Lowest Common Ancestor) de dois vértices
    int lca(int u, int v) {
        while (chain_head[u] != chain_head[v]) {
            if (depth[chain_head[u]] < depth[chain_head[v]]) {
                v = parent[chain_head[v]];
            } else {
                u = parent[chain_head[u]];
            }
        }

        return (depth[u] < depth[v]) ? u : v;
    }

public:
    HLDGraph(int _n) : n(_n) {
        adj_list.resize(n);
        parent.assign(n, -1);
        depth.assign(n, 0);
        subtree_size.assign(n, 0);
        chain_head.assign(n, -1);
        chain_pos.assign(n, 0);
        chain_idx.assign(n, 0);
        chain_size.assign(n, 1);
        chain_total_weight.assign(n, 0);
        edge_weight.assign(n, 0);
        chain_edges.resize(n);
    }

    // Função para adicionar uma aresta bidirecional ao grafo
    void addEdge(int u, int v, int weight) {
        adj_list[u].emplace_back(v, weight);
        adj_list[v].emplace_back(u, weight);
    }

    // Função para realizar a Heavy-Light Decomposition no grafo
    void buildHLD(int root = 0) {
        dfs(root, -1, 0);
        hld(root, 0, root);
    }

    // Função para remover uma aresta do grafo
    void removeEdge(int u, int v) {
        int lca_node = lca(u, v);

        // Remover u-v do caminho do LCA até u
        while (u != lca_node) {
            // A remoção da aresta deve ser tratada conforme a sua aplicação específica.
            // Neste exemplo, iremos apenas imprimir uma mensagem indicando a remoção da aresta.
            cout << "Removendo aresta: " << u << " - " << parent[u] << endl;
            u = parent[u];
        }

        // Remover u-v do caminho do LCA até v
        while (v != lca_node) {
            // A remoção da aresta deve ser tratada conforme a sua aplicação específica.
            // Neste exemplo, iremos apenas imprimir uma mensagem indicando a remoção da aresta.
            cout << "Removendo aresta: " << v << " - " << parent[v] << endl;
            v = parent[v];
        }
    }

    // Função para atualizar o peso de uma aresta do grafo
    void updateEdge(int u, int v, int new_weight) {
        int lca_node = lca(u, v);

        // Atualizar u-v do caminho do LCA até u
        while (u != lca_node) {
            // A atualização da aresta deve ser tratada conforme a sua aplicação específica.
            // Neste exemplo, iremos apenas imprimir uma mensagem indicando a atualização da aresta.
            cout << "Atualizando aresta: " << u << " - " << parent[u] << " (Novo peso: " << new_weight << ")" << endl;
            u = parent[u];
        }

        // Atualizar u-v do caminho do LCA até v
        while (v != lca_node) {
            // A atualização da aresta deve ser tratada conforme a sua aplicação específica.
            // Neste exemplo, iremos apenas imprimir uma mensagem indicando a atualização da aresta.
            cout << "Atualizando aresta: " << v << " - " << parent[v] << " (Novo peso: " << new_weight << ")" << endl;
            v = parent[v];
        }
    }

    // Função para encontrar o melhor caminho de u a v no grafo
    int findBestPath(int u, int v) {
        int lca_node = lca(u, v);

        int best_path_weight = INF;

        // Encontrar o melhor caminho de u ao LCA
        while (u != lca_node) {
            int chain_head_u = chain_head[u];
            int chain_idx_u = chain_idx[u];
            int chain_total_weight_u = chain_total_weight[chain_head_u];
            int chain_pos_u = chain_pos[u];
            int chain_size_u = chain_size[chain_head_u];

            int path_weight = edge_weight[u];

            // A redução do caminho pode variar dependendo da aplicação e da estrutura do grafo.
            // Neste exemplo, vamos subtrair o peso da aresta atual do peso total da cadeia,
            // o que nos dará a soma dos pesos das arestas remanescentes na cadeia.
            path_weight = chain_total_weight_u - path_weight;

            // Verificar se o caminho atual é melhor que o caminho anterior
            best_path_weight = min(best_path_weight, path_weight);

            // Mover para o próximo vértice na cadeia
            u = chain_edges[chain_head_u][(chain_idx_u + 1) % chain_size_u];
        }

        // Encontrar o melhor caminho do LCA a v
        while (v != lca_node) {
            int chain_head_v = chain_head[v];
            int chain_idx_v = chain_idx[v];
            int chain_total_weight_v = chain_total_weight[chain_head_v];
            int chain_pos_v = chain_pos[v];
            int chain_size_v = chain_size[chain_head_v];

            int path_weight = edge_weight[v];

            // A redução do caminho pode variar dependendo da aplicação e da estrutura do grafo.
            // Neste exemplo, vamos subtrair o peso da aresta atual do peso total da cadeia,
            // o que nos dará a soma dos pesos das arestas remanescentes na cadeia.
            path_weight = chain_total_weight_v - path_weight;

            // Verificar se o caminho atual é melhor que o caminho anterior
            best_path_weight = min(best_path_weight, path_weight);

            // Mover para o próximo vértice na cadeia
            v = chain_edges[chain_head_v][(chain_idx_v + 1) % chain_size_v];
        }

        return best_path_weight;
    }
};
