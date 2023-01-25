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
stack<int> mystack;

//ALOCAÇÃO DINAMICA DE MATRIZ

int **x;
//criar array n ponteiros para int
int x = new int*[n];
for (int i=0; i<elementos; i++)
{
	//cada array é um array de n elementos
	x[i] = new int[n]
}
// Vector de vector criando um elemento que tenha tamanho n e que guarde outro vector de tamanho n
vector <vector <int>> y(n, vector <int> (n));

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


void bfs(int x, int pes) //peso diminui encontra limite
{
	dist[x]=pes;
	queue <int> q;
	q.push(x);
	while (!q.empty())
	{
		int u= q.front();
		q.pop();
		for (auto e : adj[u])
		{
			if (dist[e]==-1 && dist[u]>0)
			{
				dist[e]=dist[u]-1;
				q.push(e);
			}
		}
	}
}
//FORTE MENTE CONEXO
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

oia()
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

//PINTADORES DE GRAFO 
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

void topologic(int x)
{
    vis[x]=true;
    for (auto e : adj[x])
    {
        if (!vis[e])
        {
            dfs(e);
        }
    }
    mystack.push(x);
}

void alltoplogres(vector <int>& res)
{
	bool flag = false;
	for (int i = 0; i < n; i++) //dfs normal unica diferenca é a escolha dos nos com graus menores
	{
	    if (grau[i] == 0 && !vis[i])
	    {
		for (auto e : adj[i]) //quando um no é puxado seu grau diminui
		{
		    grau[e]--;
		}

		res.push_back(i); //coloca em um vector de resposta que poderia ser uma stack contudo fica mais facil de manipular a resposta
		vis[i] = true; //marca o no visitado apos percorrer o no por inteiro
		alltoplogres(res); //chama a recursividade

		/*
		    todos os nos com graus maiores serao chamados ate seu grau chegar a zero e ele ser percorrido por completo
		*/

		vis[i] = false; //reseta o elemento i fixado
		res.erase(res.end() - 1); // retira o ultimo elemento que é colocado porque ao repetir o for pode ser adicionado na resposta
		for (auto e : adj[i])
		{
		    grau[e]++; //reseta o grau do i fixado
		}

		flag = true; //coloca flag true caso nao chame a recursividade de forma correta
	    }
	}

	if (!flag) //evita erros ao chamar a recursividade
	{
	    string x; //colocar na resposta com string
	    for (int i = 0; i < res.size(); i++) //monta a resposta caso de certo o res tem size
		{
		    x+=cid[res[i]];
		    if (i+1<res.size())
		    {
			x+=" ";
		    }
		}
	    if (res.empty()) //se nao coloca a respota como nao
	    {
		x = "NO";
	    }
	    term.push_back(x); //resposta string
	}
}

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
//Floyd Warshall
#define INF 99999
vector<vector<int>> dist(n,vector<int>(n, INF));
void fw(vector<vector<int>>& dist, int v)
{
	for(int k=0; k<v; k++)
	{
		for (int i=0; i<v; i++)
		{
			for(int j=0;j<v; j++)
			{
				if ( dist[i][k] != INF && dist[k][j] != INF && dist[i][k] + dist[k][j] < dist[i][j])
				{	
					dist[i][j] = dist[i][k] + dist[k][j];
				}
			}
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
int dx[8]={1,0,-1,0, -1, 1, -1, 1};
int dy[8]={0,1,0,-1,-1, 1,1,-1};
int back(int i, int j) //bfs flood fill[
{
    dist[i][j]=0;
    queue <p> q;
    q.push(make_pair(i,j));
    while (q.size())
    {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();
        for (int l=0; l<8; l++)
        {
            int h = x+dx[l];
            int w = y+dy[l];
            if(w>0 && w<9 && h>0 && h<9 && dist[h][w]==-1)
            {
                dist[h][w]=dist[x][y]+1;
                q.push({h,w});
            }
        }
    }
    return dist[b1][b2];
}

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

// -------operação com bitsets ------- 
bool fullAdder(bool b1, bool b2, bool& carry)// faz operacão de soma com bitset
{
    bool sum = (b1 ^ b2) ^ carry;
    carry = (b1 && b2) || (b1 && carry) || (b2 && carry);
    return sum;
}
bitset<17> bitsetAdd(bitset<17>& x)
{
    bool carry = false;
    bitset<17> ans, oi(1);//oi esta somando 1 por vez
    for (int i = 0; i < 17; i++) {
        ans[i] = fullAdder(x[i],oi[i], carry);
    }
    return ans;
}
//faz diferenca entre dois bitsets
bool fullSubtractor(bool b1, bool b2, bool& borrow)
{
    bool diff;
    if (borrow) {
        diff = !(b1 ^ b2);
        borrow = !b1 || (b1 && b2);
    }
    else {
        diff = b1 ^ b2;
        borrow = !b1 && b2;
    }
    return diff;
}

bitset<33> bitsetSubtract(bitset<32> x, bitset<32> y)
{
    bool borrow = false;
    bitset<33> ans;//resultado
    for (int i = 0; i < 32; i++) {
        ans[i] = fullSubtractor(x[i], y[i], borrow);
    }
    return ans;
}


//---------------------------------

int mdc(int num1, int num2) //maior e menor
{
    if(num1%num2 == 0)
        return num2;
    else
        return mdc(num2, num1%num2);
}

int mmc(int num1, int num2) { //mmc

    int resto, a, b;

    a = num1;
    b = num2;

    do {
        resto = a % b;

        a = b;
        b = resto;

    } while (resto != 0);

    return ( num1 * num2) / a;
}

int multiplicar_matrizes( //calcula multiplicação de matriz de mesmo tamanho
        int matA[][MAX], int na, int ma,
        int matB[][MAX], int nb, int mb,
        int matC[][MAX], int nc, int mc)
{  

    if (ma != nb || na != nc || mb != mc) return 1;

    int a = na, b = ma, c = mb;

    for (int i = 0; i < a; i++) {
        for (int k = 0; k < c; k++) {
            matC[i][k] = 0;
            for (int j = 0; j < b; j++) {
                matC[i][k] += matA[i][j] * matB[j][k];
            }
        }
    }
    return 0;
}

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

int s_int(string a) //String em inteiro
{
	int c=a.size()-1;
	int y=0;
	for (char x : a)
	{
		y+=(x-'0')*pow(10,c);
		c--;
	}
	return y;
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

//Matematica
/* Iterative Function to calculate (x ^ y)%p in
   O(log y) */
int powmod(int x, int y, int p)
{
    int res = 1;  // Initialize result
 
    x = x % p;  // Update x if it is more than or
                // equal to p
 
    while (y > 0)
    {
        // If y is odd, multiply x with result
        if (y & 1)
            res = (res*x) % p;
 
        // y must be even now
        y = y>>1; // y = y/2
        x = (x*x) % p;
    }
    return res;
}
 
// Function to calculate k for given a, b, m
int discreteLogarithm(int a, int b, int m) {
 
    int n = (int) sqrt (m) + 1;
 
    unordered_map<int, int> value;
 
    // Store all values of a^(n*i) of LHS
    for (int i = n; i >= 1; --i)
        value[ powmod (a, i * n, m) ] = i;
 
    for (int j = 0; j < n; ++j)
    {
        // Calculate (a ^ j) * b and check
        // for collision
        int cur = (powmod (a, j, m) * b) % m;
 
        // If collision occurs i.e., LHS = RHS
        if (value[cur])
        {
            int ans = value[cur] * n - j;
            // Check whether ans lies below m or not
            if (ans < m)
                return ans;
        }
    }
    return -1;
}

//conversões em arvores
 
// preorder e inorder para posorder
int preIndex = 0;
void printPost(int in[], int pre[], int inStrt,
               int inEnd, map<int, int> hm)
{
    if (inStrt > inEnd)
        return;        
 
    // Find index of next item in preorder traversal in
    // inorder.
    int inIndex = hm[pre[preIndex++]];
 
    // traverse left tree
    printPost(in, pre, inStrt, inIndex - 1, hm);
 
    // traverse right tree
    printPost(in, pre, inIndex + 1, inEnd, hm);
 
    // print root node at the end of traversal
    cout << in[inIndex] << " ";
}
 
void printPostMain(int in[], int pre[],int n)
{
    map<int,int> hm ;
    for (int i = 0; i < n; i++)
    hm[in[i]] = i;
         
    printPost(in, pre, 0, n - 1, hm);
}


 //posorder e inorder para preorder
 
int search(int in[], int data,int n)
{
    int i = 0;
    for (i = 0; i < n; i++)
        if (in[i] == data)
            return i;
    return i;
}

void fillPre(int in[], int post[], int inStrt,
            int inEnd, stack<int> &s,int n)
{
    if (inStrt > inEnd)
        return;
 
    // Find index of next item in postorder traversal in
    // inorder.
    int val = post[postIndex];
    int inIndex = search(in, val, n);
    postIndex--;
 
    // traverse right tree
    fillPre(in, post, inIndex + 1, inEnd, s, n);
 
    // traverse left tree
    fillPre(in, post, inStrt, inIndex - 1, s, n);
 
    s.push(val);
}
 
void printPreMain(int in[], int post[],int n)
{
    int len = n;
    postIndex = len - 1;
    stack<int> s ;
    fillPre(in, post, 0, len - 1, s, n);
    while (s.size() > 0)
    {
        cout << s.top() << " ";
        s.pop();
    }
}
 
//converte preorder em pos order
void findPostOrderUtil(int pre[], int n, int minval,
                       int maxval, int& preIndex)
{
 
    // If entire preorder array is traversed then
    // return as no more element is left to be
    // added to post order array.
    if (preIndex == n)
        return;
 
    // If array element does not lie in range specified,
    // then it is not part of current subtree.
    if (pre[preIndex] < minval || pre[preIndex] > maxval) {
        return;
    }
 
    // Store current value, to be printed later, after
    // printing left and right subtrees. Increment
    // preIndex to find left and right subtrees,
    // and pass this updated value to recursive calls.
    int val = pre[preIndex];
    preIndex++;
 
    // All elements with value between minval and val
    // lie in left subtree.
    findPostOrderUtil(pre, n, minval, val, preIndex);
 
    // All elements with value between val and maxval
    // lie in right subtree.
    findPostOrderUtil(pre, n, val, maxval, preIndex);
 
    cout << val << " ";
}
 
void findPostOrder(int pre[], int n)
{
 
    // To store index of element to be
    // traversed next in preorder array.
    // This is passed by reference to
    // utility function.
    int preIndex = 0;
 
    findPostOrderUtil(pre, n, INT_MIN, INT_MAX, preIndex);
}



//Fenwick fast
ull n;
ull jt[10000024];
ull query(int id)
{
	ull res = 0;
	for (;id; id = id - (id& -id)) // compara em bytes e acha o primeiro numero da direita para a esquerda
	{
		res+=jt[id];
	} 
	return res;
	
}

void upd(int id, ull x)
{
	for (; id<=n; id=id+(id&-id))
	{
		jt[id]+=x;
	}
}


ull query(int l , int r)
{
	return query(r) - (l?query(l-1):0);
}

void up(int id, int x)
{
	upd(id, x);//precisa comecar com id = 1
}

void upd(int l, int r, int x)
{
	upd(l,x);
	//~ upd(x,l);
	up(r+1,-x);
}
ios_base::sync_with_stdio(false);
cin.tie(NULL);


// terminar de corrigir
int INF = INT_MAX;
vector<int> t[4*6];

int a[5];
void build(int a[], int v, int tl, int tr) {
    if (tl == tr) {
        t[v] = vector<int>(1, a[tl]);
    } else { 
        int tm = (tl + tr) / 2;
        build(a, v*2, tl, tm);
        build(a, v*2+1, tm+1, tr);
        merge(t[v*2].begin(), t[v*2].end(), t[v*2+1].begin(), t[v*2+1].end(),
              back_inserter(t[v]));
    }
}

int query(int v, int tl, int tr, int l, int r, int x) {
    if (l > r)
        return INF;
    if (l == tl && r == tr) {
        vector<int>::iterator pos = lower_bound(t[v].begin(), t[v].end(), x);
        if (pos != t[v].end())
            return *pos;
        return INF;
    }
    int tm = (tl + tr) / 2;
    return min(query(v*2, tl, tm, l, min(r, tm), x), query(v*2+1, tm+1, tr, max(l, tm+1), r, x));
}

void update(int v, int tl, int tr, int pos, int new_val) {
    t[v].erase(find(t[v].begin(), t[v].end(), a[pos]));
    t[v].insert(v,new_val);
    if (tl != tr) {
        int tm = (tl + tr) / 2;
        if (pos <= tm)
            update(v*2, tl, tm, pos, new_val);
        else
            update(v*2+1, tm+1, tr, pos, new_val);
    } else {
        a[pos] = new_val;
    }
}


int const n=10;
int const tt=log2(n);

class aaaaa
{
	public:
	int st[tt][n];
	/*
	void build(int a[])
	{
		for(int i=0; i<n; i++)
		{
			st[0][i]=a[i];
		}
		
		for(int i=1; i<log2(n); i++)
		{
			for(int j=0; j+(1<<i)<n; j++)
			{
				st[i][j]=st[i-1][j]*st[i-1][j+(1<<i)];
			}
		}
	}
	*/
	void buildcria(int a[])
	{
		for(int i=0; i<n; i++) 
		{
			st[0][i]=a[i];
		}
		
		for(int i=0; (1<<i)<n; i++)
		{
			int *v=st[i];
			for(int s=1; s*(1<<i)<=n; s+=2)
			{
				int k=s*(1<<i);
				v[k]=a[k];
				v[k-1]=a[k-1];
				for(int j=1; (1<<j)<i; j++)
				{
					v[k+j]=v[k+j-1] *a[k+j];
					v[k-j-1]=v[k-j] * a[k-j-1];
				}
			}
		}
		
	}
	
	int querycria(int l, int r)
	{
		if(l==r) return st[0][l];
		int k = log2(r-l);
		return st[k][l]*st[k][r];
	}
	/*
	int query(int l, int r)
	{
		if(l==r) return st[0][l];
		int len=r-l+1;
		int k = log2(len);
		return st[k][l]+st[k][r-(1<<k)];
	}
	* /
	
}; 


//Mo
#include <bits/stdc++.h>
using namespace std;

int BLOCK_SIZE;

struct query {
	int l, r, idx;
};
//comparador dos blocos
bool comparator(query a, query b)
{
	if ((a.l / BLOCK_SIZE) != (b.l / BLOCK_SIZE))
		return (a.l / BLOCK_SIZE) < (b.l / BLOCK_SIZE);

	return ((a.l / BLOCK_SIZE) & 1) ? (a.r < b.r)
									: (a.r > b.r);
}

void expand(int idx, int* arr, map<int, int>& numFreq,set<pair<int, int> >& freqNum)
{
	freqNum.erase({ numFreq[arr[idx]], arr[idx] });

	++numFreq[arr[idx]];

	freqNum.insert({ numFreq[arr[idx]], arr[idx] });
}
//estudar
void shrink(int idx, int* arr, map<int, int>& numFreq,set<pair<int, int> >& freqNum)
{
	freqNum.erase({ numFreq[arr[idx]], arr[idx] });

	--numFreq[arr[idx]];

	freqNum.insert({ numFreq[arr[idx]], arr[idx] });
}

// igual a do bruno
pair<int, int>
sqrtDecomposition(int& L, int& R, int l, int r, int* arr,set<pair<int, int> >& freqNum,map<int, int>& numFreq)
{
	while (L > l) {
		--L;
		expand(L, arr, numFreq, freqNum);
	}

	while (R < r) {
		++R;
		expand(R, arr, numFreq, freqNum);
	}

	while (L < l) {
		shrink(L, arr, numFreq, freqNum);
		++L;
	}

	while (R > r) {
		shrink(R, arr, numFreq, freqNum);
		--R;
	}

	pair<int, int> last = *prev(freqNum.end());

	return last;
}
void getMaxOccuringElement(int arr[], int N, int M,pair<int, int> Q[])
{

	BLOCK_SIZE = (int)sqrt(N + .0) + 1;

	query queries[M];

	for (int i = 0; i < M; ++i) {
		queries[i].l = Q[i].first;
		queries[i].r = Q[i].second;
		queries[i].idx = i;
	}
//ordena a query para n gastar tanto tempo
	sort(queries, queries + M, comparator);

	int L = 0, R = -1;

	pair<int, int> ans[M];

	set<pair<int, int> > freqNum;
	map<int, int> numFreq;

	for (int i = 0; i < M; ++i) {

		int l = queries[i].l;
		int r = queries[i].r;
		ans[queries[i].idx] = sqrtDecomposition(
			L, R, l, r, arr, freqNum, numFreq);
	}
	for (int i = 0; i < M; ++i) 
    {
        cout << ans[i].first<< "\n";
	}
}

