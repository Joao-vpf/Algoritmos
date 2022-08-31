#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <list>
#include <limits>

using namespace std;

typedef pair<int,int> p 

vector <int> adj[1000], color(1000,-1);
vector <bool> vis(1000,false);
int dis[1000], timer;
vector <p> temp[1000];

//GRAFOS:

//BFS
void bfs(int inicio, int fim) //estilo bfs "unidimensional" conta distancia
{
   for (int i=0; i<1000; i++)
   {
        dis[i]=-1;
   }
   dis[inicio]=0;
   queue <int> q;
   q.push(inicio);
    while (q.size())
    {
        if (dis[fim]!=-1) //caso seja tenha muitos números
        {  
            break;
        }
        int u = q.front();
        q.pop();
        for (auto e : adj[u])
        {
            if (dis[e]==-1)
            {
                dis[e]=dis[u]+1;
                q.push(e);
            }
        }
    }
}

void bfs(int u) //bfs analisa por adj
{
    queue <int> q;
    q.push(u);
    while (!q.empty())
    {
        int v = q.front();
        q.pop();
        vis[v]=false
        for (auto e : adj[v])
        {
            q.push(e);
        }
    }
}

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

//DFS - CODIGOS DERIVADOS
void dfs(int u) //dfs recursivo (confere toda a raiz)
{
    //u = inicio
    vis[u]=true;
    for (auto e : adj[u])
    {
        if (!vis[e])
        {
            dfs(e);
        }
    }
}

void dfsStack(int u) //dfs stack (confere por adjacência)
{
    stack<int> s;
    s.push(u);
    while (!s.empty())
    {
        int v = s.top();
        s.pop();
        vis[v] = true;
        for (auto e : adj[v])
        {
            if (!vis[e])
            {
                s.push(e);
            }
        }
    }
}

void dfs(int u, int j) //dfs conta o tempo de saida e de entrada;
{
    temp[u].first=timer++;
    for (int v :adj[u])
    {
        if(v!=j)
        {
            dfs(v,u);
        }
    }
    temp[v].second=timer++;
}

//Finding Articulation Points - DFS
vector <int> adj[101], low(101,-1), par(101,-1), dist(101,-1);
vector <bool> ap(101,false);
int Time=1;
void dfs(int x)
{
	int filho=0;
	low[x]= dist[x] = Time;
	Time++;
	for (auto e : adj[x])
	{
		if (dist[e]==-1)
		{
			par[e]=x;
			filho++;
			dfs(e);
			low[x] = min(low[x], low[e]);
			if(par[x]==-1 && filho>1)
			{
				ap[x]=true;
			}
			else if(par[x]!=-1 && low[e]>=dist[x])
			{
				ap[x]=true;
			}
		}
		else if(par[x]!=e)
		{
			low[x] = min(low[x], dist[e]);
		}
	}
}


//FLOOD FILL
//Nao marca que vistou
void back(int i, int j) //dfs "multidimensional"
{
	mat[i][j]='T';
	if (i>0 && mat[i-1][j]=='A') 
	{
		back(i-1,j);
	}
	if (i<n-1 && mat[i+1][j]=='A') 
	{
		back(i+1,j);
	}
	if (j>0 && mat[i][j-1]=='A') 
	{
		back(i,j-1);
	}
	if (j<m-1 && mat[i][j+1]=='A') 
	{
		back(i,j+1);
	}
	
}

//Marca que visitou
void flfd(int x, int y,int m, int n) //inicio da procura, tamanho vertical, tamanho horizontal
{
	vis[x][y]=1;
	//normal
	if (y>0 && vis[x][y-1]==0 && mat[x][y-1]==1)
	{
		flfd(x, y-1,m,n);
	}
	if (x<m-1 && vis[x+1][y]==0 && mat[x+1][y]==1)
	{
		flfd(x+1, y,m,n);
	}
	if (x>0 && vis[x-1][y]==0 && mat[x-1][y]==1)
	{
		flfd(x-1, y,m,n);
	}
	if (y<n-1 && vis[x][y+1]==0 && mat[x][y+1]==1)
	{
		flfd(x, y+1,m,n);
	}
	//diagonais
	if (x<m-1 && y<n-1 && vis[x+1][y+1]==0 && mat[x+1][y+1]==1)
	{
		flfd(x+1, y+1,m,n);
	}
	if (x>0 && y>0 && vis[x-1][y-1]==0 && mat[x-1][y-1]==1)
	{
		flfd(x-1, y-1,m,n);
	}
	if (x>0 && y<n-1 && vis[x-1][y+1]==0 && mat[x-1][y+1]==1)
	{
		flfd(x-1, y+1,m,n);
	}
	if (x<m-1 && y>0 && vis[x+1][y-1]==0 && mat[x+1][y-1]==1)
	{
		flfd(x+1, y-1,m,n);
	}
}

//FLOOD FILL / BFS
void back(int i, int j) //bfs "multidimensional"
{
    int dist[n][m]=-1;
    dist[i][j]=0;
    queue <p> q;
    q.push(make_pair(i,j))
    while (q.size())
    {
        if (dist[n-1][m-1]!=-1)
        {
            return dist[n-1][m-1];
        }
        int x = q.front().first;
        int y = q.front().second;
        q.pop();
        if (mat[x-1][y]==-1 && dist[x-1][y]==-1)
        {
            dist[x-1][y]=dist[x][y]+1;
            q.push(make_pair(x-1,y));
        }
    }
}

//COMPLEMENTAR GRAFO

int contador (int v) //conta quantos nodos estão conexos funciona melhor com nao dirigidos
{
    //v quantidade de nodos
    int cont;
    for (int j=0; j<v; j++)
    {
        if(!vis[j])
        {   
            dfs(j);
            cont++;
        }
    }
    return cont;
}

//Funções: 

int trad (char x) //pega uma letra qualquer e diz qual posicao de 0 a 25 ela pertence
{
    int o=x-97;
    return o;
}

int reverse (int x) //inverte um numero inteiro
{
    int y=0;
    while (x>0)
    {
        if (y>0)
        { 
            y*=10;
        }
        y+=(x%10);
        x/=10;
    }
    return y;
}

void fib(long long int f[]) //tem em pd e cria uma fibonnaci
{
    int i=0;
    for (i=3;i<=60;i++)
    {
        f[i]=f[i-2]+f[i-1];
    }
}

int fat(int n) //cria um fatorial
{
    if (n==0)
    {
        return 1;
    }
    return fat(n-1)*n;
}

//CONVERSORES: 

string hextobin(string a)
{
	bitset<4> bis;//bitset
	string res;
	for (char x : a)
	{
		x=toupper(x);//cctype
		int b=x;
		if (b<=int ('9'))
		{
			bis=b-48;
			res+=bis.to_string();
		}
		else
		{
			bis=b-55;
			res+=bis.to_string();
		}
	}
	return res;
}

//Buscas:

int busca_binaria(int vet[], int procurado, int inicio, int fim) //faz uma busca binaria
{
    if (inicio==fim)
    {
        return (vet[inicio]==procurado ? inicio : -1);
    }
    if (vet[(inicio+fim)/2]<=procurado)
    {
       return busca_binaria(vet, procurado, ((inicio+fim)/2)+1, fim);
    }
       return busca_binaria(vet, procurado,inicio , ((inicio+fim)/2));
}

//ORDENAÇÃO:

//Marge:
void marge(int vet[], int inicio, int fim) //faz o marge sort
{
    int meio=(inicio+fim)/2, aux[(fim-inicio)+1];
    for (int i=inicio, j=meio+1, k=0; i<=meio || j<=fim;)
    {
        if (i<=meio && j<=fim)
        {
            if (vet[i]<vet[j])
            {
                aux[k]=vet[i];
                k++;
                i++;
            }
            else
            {
                aux[k]=vet[j];
                k++;
                j++;
            }
        }
        else
        {
            if (i>meio)
            {
                aux[k]=vet[j];
                k++;
                j++;
            }
            else
            {
                aux[k]=vet[i];
                k++;
                i++;
            }
        }
    }

    for (int i=0, j=inicio;i<(fim-inicio)+1; j++, i++)
    {
        vet[j]=aux[i];
    }
}

void margesort(int vet[], int inicial, int fim)
{
    if (inicial!=fim)
    {
        if (vet[(inicial+fim)/2])
        {
            margesort(vet, inicial , (inicial+fim)/2);
        }
        margesort(vet, ((inicial+fim)/2)+1, fim);
        marge(vet, inicial, fim);
    }
}

//
