/*
 Esta função resolve a coloração m
problema com a utilização da recursividade. Retorna
falso se as cores m não puderem ser atribuídas,
caso contrário, devolver verdadeiro e impressões
atribuições de cores a todos os vértices.
É favor notar que pode haver mais de
uma solução, esta função imprime uma
das soluções viáveis.
*/

bool isSafe(bool graph[V][V], int color[]) //olha se esse ponto foi pintado
{
    // check for every edge
    for (int i = 0; i < V; i++)
        for (int j = i + 1; j < V; j++)
            if (graph[i][j] && color[j] == color[i])
                return false;
    return true;
}

bool graphColoring(bool graph[V][V], int m, int i, int color[V]) //procura se da para pintar com esse numero de nodo
{
    // if current index reached end
    if (i == V) {
 
        // if coloring is safe
        if (isSafe(graph, color)) {
 
            // Print the solution
            printSolution(color);
            return true;
        }
        return false;
    }
 
    // Assign each color from 1 to m
    for (int j = 1; j <= m; j++) {
        color[i] = j;
 
        // Recur of the rest vertices
        if (graphColoring(graph, m, i + 1, color))
            return true;
 
        color[i] = 0;
    }
 
    return false;
}


//verifica se grafo e impar
bool bicoloring(int x)//Objetivo identificar um grafo impar
{
	queue <int> q;
	q.push(x);
	cor[x]=1;
	while (!q.empty())
	{
		int u = q.front();
		q.pop();
		
		for(auto e :  adj[u])
		{
			if (cor[e]==-1)
			{
				cor[e]=1-cor[u];
				q.push(e);
			}
			else if (cor[e]==cor[u])
			{
				return false;
			}
		}
	}
	return true;
}
