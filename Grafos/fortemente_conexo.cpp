//algoritmo de kosaraju sem ser classe
void topo(int x)
{
    vis[x]=true;
    for (auto e : adj[x])
    {
        if(!vis[e])
        {
            topo(e);
        }
    }
    s.push(x);
}

void trans(int x)
{
    for (int i=0; i<x; i++)
    {
        for (auto e:adj[i])
        {
            gr[e].pb(i);
        }
    }
}

void dfs(int x)
{
    vis[x]=true;
    for (auto e : gr[x])
    {
        if(!vis[e])
        {
            dfs(e);
        }
    }
}

verifica()
{
	while (s.size())
	{
	    int u = s.top();
	    s.pop();
	    if(!vis[u])
	    {
		dfs(u);
		//resultado dos nos
	    }
	}
}

/*int main()
{
	topo();
	trans();
	oia()
}
*/

//algortimo tarjan 

int min(int a, int b) {
  return (a < b) ? a : b;
}

void findComponent(int u, int disc[], int lowLink[], stack < int > & stk, bool stkItem[]) {
  static int time = 0;
  disc[u] = lowLink[u] = ++time;
  stk.push(u);
  stkItem[u] = true;

  for (int v = 0; v < v; v++) {
    if (graph[u][v]) {
      if (disc[v] == -1) {
        findComponent(v, disc, lowLink, stk, stkItem);
        lowLink[u] = min(lowLink[u], lowLink[v]);
      } else if (stkItem[v])
        lowLink[u] = min(lowLink[u], disc[v]);
    }
  }

  int poppedItem = 0;
  if (lowLink[u] == disc[u]) {
    while (stk.top() != u) {
      poppedItem = stk.top();
      cout << poppedItem << " ";
      stkItem[poppedItem] = false;
      stk.pop();
    }
    poppedItem = stk.top();
    cout << poppedItem << endl;
    stkItem[poppedItem] = false;
    stk.pop();
  }
}

void strongConComponent() {
  int disc[v], lowLink[v];
  bool stkItem[v];
  stack < int > stk;

  for (int i = 0; i < v; i++) {
    disc[i] = lowLink[i] = -1;
    stkItem[i] = false;
  }

  for (int i = 0; i < v; i++)
    if (disc[i] == -1)
      findComponent(i, disc, lowLink, stk, stkItem);
}
