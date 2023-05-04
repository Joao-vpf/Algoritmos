const int MAXN = 100005; // número máximo de vértices

vector<int> adj[MAXN]; // lista de adjacência
bool visited[MAXN]; // vetor de visitados
int entryTime[MAXN], exitTime[MAXN]; // tempo de entrada e saída de cada vértice
int t = 0; // contador de tempo
stack<int> s; // pilha para manter os vértices do caminho atual
bool ok=1;//0 houve ciclo 1 nao teve ciclo
void dfs(int u) 
{
    visited[u] = true;
    entryTime[u] = ++t;
    s.push(u); // adiciona u à pilha

    for(int v : adj[u]) 
    {
        if(!visited[v]) 
        {
            dfs(v);
        }
        else if(exitTime[v] == 0) 
        {    
            cout << "Ciclo encontrado: ";
            while(s.top() != v) 
            { // remove os vértices do caminho até encontrar v
                cout << s.top() << " ";
                s.pop();
            }
            cout << s.top() << endl; // imprime o vértice v que forma o ciclo
            s.pop();
           ok=0;
        }
    }

    exitTime[u] = ++t;
    s.pop(); // remove u da pilha
}
