//Bellman Ford	
void dfsbelman(int x, vector<int> caca[], vector<bool>& vis) //pinta todos que estao em ciclos
{
    vis[x]=true;
    for (auto e: caca[x])
    {
        if(!vis[e])
        {
            dfsbelman(e, caca,vis);
        }
    }
}

void bford(int v, int E,vector<pair<int,pair<int,int>>>& adj, vector<int>& dist, vector<bool>& vis, vector <int> caca[])
{
    dist[0]=0;
    for (int i=0; i<v-1; i++)
    {
        for (int j=0; j<E; j++) 
	{
            pair<int, pair<int, int>> e = adj[j];
            pair<int, int> l = e.second;
            if (dist[e.first] != INT_MAX && dist[l.first] > l.second + dist[e.first]) {
                dist[l.first] = l.second + dist[e.first];
            }
        }
    }
    for (int i = 0; i < E; i++) {
        pair<int, pair<int, int>> e = adj[i];
        pair<int, int> l = e.second;
        if (dist[e.first] != INT_MAX && dist[e.first] + l.second < dist[l.first]) //verifica se tem um ciclo negativo caso tenha ele  entra no if
        {
           dfsbelman(e.first, caca, vis);
        }
    }
	
    for (int i = 0; i < V; i++) //mostra a distancia de cada um
    {
        cout << i << "\t\t" << dis[i] << endl;
    }
}
