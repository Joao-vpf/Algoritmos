#include <iostream>
#include <vector>
using namespace std;

struct lisestranha //busca achar a quantidade de ordens crescentes
{
//Binary Indexed Tree or Fenwick Tree + lucas
    void update(long long int rank, long long int increment, vector<long long int> &binaryIndexTree) {
        while (rank < binaryIndexTree.size()) { // Aumentar a classificação actual e todas as classificações superiores
            binaryIndexTree[rank - 1] += increment;
            rank += (rank & -rank);
        }
    }

    long long int getValue(long long int rank, const vector<long long int> &binaryIndexTree) {
        long long int result = 0;
        while (rank > 0) { // Pesquisar a classificação atual todas as classificações inferiores
            result += binaryIndexTree[rank - 1]; // Somar qualquer valor encontrado no resultado
            rank -= (rank & -rank);
        }
        return result;
    }

    void res(long long int n, long long int k) {
        vector<long long int> values(n); //entrada de valores
        for (long long int i = 0; i < n; i++) {
            cin >> values[i];
        }
        vector<vector<long long int>> cumBIT(k, vector<long long int>(n)); // 0 fora de cumBIT esta é a árvore binária
        vector<long long int> temp(n); //  vetor usado como auxiliar
        map<long long int, long long int> mapIndex; // Isto irá traduzir-se do valor em índice para a contagem baseada em 1 de valores inferiores a este no bit

        partial_sort_copy(values.cbegin(), values.cend(), temp.begin(), temp.end());

        for (long long int i = 0; i < n; ++i) {
            mapIndex.insert(make_pair(temp[i], i +
                                               1)); // a insercao só permitirá que cada numero seja adicionado ao mapa pela primeira vez
        }

        vector<vector<long long int>> binaryIndexTree(k, vector<long long int>(
                n)); // matriz usada na contagem de possibilidades
        long long int result = 0;

        for (auto it = values.cbegin(); it != values.cend(); ++it) {
            long long int rank = mapIndex[*it];
            long long int value = 1; // Número de sequências a adicionar a esta classificação e todas as classificações subsequentes
            update(rank, value,
                   binaryIndexTree[0]); // colocar a árvore binária de índice para sub-sequências de comprimento 1

            for (long long int i = 1; i < k; ++i) { // olhar todas as sequencias com k -2 elementos
                value = getValue(rank - 1, binaryIndexTree[i - 1]); // Recuperar todas as subssequencias de menor rank
                update(rank, value, binaryIndexTree[i]); // Atualizar a arvore com subseqencias desse comprimento
            }
            result += value; //e somar todas as possiveis subsequencias desse rank
        }
        cout << result << endl;
    }
};

const int N = 100000;
int tree[2 * N];
struct segtree
{
    int n;
    void build(vector<int> arr) 
    {
        for (int i = 0; i < n; i++)
            tree[n + i] = arr[i];

        for (int i = n - 1; i > 0; --i)
            tree[i] = tree[i << 1] + tree[i << 1 | 1];
    }

    void update(int p, int value) 
    {
        tree[p + n] = value;
        p = p + n;

        for (int i = p; i > 1; i >>= 1)
            tree[i >> 1] = tree[i] + tree[i ^ 1];
    }

    int query(int l, int r) 
    {
        int res = 0;

        for (l += n, r += n; l < r; l >>= 1, r >>= 1) 
        {
            if (l & 1)
                res += tree[l++];

            if (r & 1)
                res += tree[--r];
        }

        return res;
    }
}

class alltopologic
{
    public:
    int n;
    bool *vis;
    vector <int> *adj, grau; 
    vector <string> term;//transforma resposta em string

    alltopologic(int n)
    {
        this -> n = n;
        vis = new bool[n];
        adj = new vector<int>[n];
        for (int i=0 ; i<n; i++)
        {
            vis[i]=false;
            grau.push_back(0);
        }
    }

    void add(int x, int y)
    {
        adj[x].push_back(y);
        grau[y]++;//determina o grau do no (maior mais vezes pode ser puxado)
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

    void vai()
    {
       vector <int> res;//resposta em int
       alltoplogres(res);
       sort(term.begin(), term.end());
       for (string x : term)
       {
            cout << x << endl;
       }
    }

};



class fenwick_tree
{
	private:
	int n;
	vector<int> jt;
	int query(int id)
	{
		int res = 0;
		for (;id; id = id - (id& -id)) // compara em bytes e acha o primeiro numero da direita para a esquerda
		{
			res+=jt[id];
		} 
		return res;
		
	}
	
	void upd(int id, int x)
	{
		for (; id<=n; id=id+(id&-id))
		{
			jt[id]+=x;
		}
	}
	
	public:
	
	fenwick_tree(int nl)
	{
		n=nl+1;
		jt.assign(n,0);
	}
	
	int query(int l , int r)
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
		up(r+1, -x);
	}
};


struct primosgold
{
	map<int,int> ad;
	unsigned  long long int cont=0;
    ad[cont]=2;
    cont++;
    for (unsigned long long int i=3; i<1000000; i++)
    {
        if(i%2!=0)
        {
            unsigned long long int j=3;
            for(; j<=sqrt(i); j+=2)
            {
                if(i%j==0)
                {
                    break;
                }
            }
            if(j>sqrt(i))
            {
                cont++;
                ad[cont]=i;
            }
        }
    }
    unsigned long long int n;
    while (cin >>n && n!=0)
    {
        unsigned long long int a=2, b;
        if(n%2==0) {
            for (unsigned long long int i = 0; i < ad.size() && a < n; i++) {
                a = ad[i];
                b = n - a;
                if (b % 2 != 0) {
                    unsigned long long int j = 3;
                    for (; j <= sqrt(b); j +=2) {
                        if (b % j == 0) {
                            break;
                        }
                    }
                    if (j > sqrt(b)) {
                        cout << n << " = " << a << " + " << b << endl;
                        break;
                    }
                }
            }
        }
        if(n%2!=0 || a>=n)
        {
           cout<< "Goldbach's conjecture is wrong."<<endl;
        }
    }
}

//MST prims
class Graph
{
    int V;
    list< pair<int, int> > *adj;
    map<pair<int,int>,int> tp;
 
public:
   Graph(int V)
    {
        this->V = V;
        adj = new list<iPair> [V];
    }
 
    void addEdge(int u, int v, int w)
    {
        tp[{u,v}]=w;
        tp[{v,u}]=w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }
    
 
    void primMST(int m)
    {
        priority_queue< iPair, vector <iPair> , greater<iPair> > pq;
    
        int src = 0; 
        vector<int> key(V, INF); //pesos da mst
        vector<int> parent(V, -1); //mst
        vector<bool> inMST(V, false); //controle da mst
        pq.push({0, src});
        key[src] = 0;

        while (!pq.empty())
        {
            int u = pq.top().second;
            pq.pop();
            if(inMST[u] == true){
                continue;
            }
        
            inMST[u] = true; 
            for (auto e : adj[u])
            {
                int v = e.first;
                int weight = e.second;
                if (inMST[v] == false && key[v] > weight)
                {
                    key[v] = weight;
                    pq.push(make_pair(key[v], v));
                    parent[v] = u;
                }
            }
        }
	/*
		manipula parent[i] - i
		ou
		key[i]
	
	*/
    }
};


//union find
class DSU {
    int* parent;
    int* rank;
 
public:
    DSU(int n)
    {
        parent = new int[n];
        rank = new int[n];
 
        for (int i = 0; i < n; i++) {
            parent[i] = -1;
            rank[i] = 1;
        }
    }
 
    int find(int i)
    {
        if (parent[i] == -1)
            return i;
 
        return parent[i] = find(parent[i]);
    }
 
    void unite(int x, int y)
    {
        int s1 = find(x);
        int s2 = find(y);
 
        if (s1 != s2) {
            if (rank[s1] < rank[s2]) {
                parent[s1] = s2;
                rank[s2] += rank[s1];
            }
            else {
                parent[s2] = s1;
                rank[s1] += rank[s2];
            }
        }
    }
};




class DSU {
    int* parent;
    int* rank;
 
public:
    DSU(int n)
    {
        parent = new int[n];
        rank = new int[n];
 
        for (int i = 0; i < n; i++) {
            parent[i] = -1;
            rank[i] = 1;
        }
    }
 
    // Find function
    int find(int i)
    {
        if (parent[i] == -1)
            return i;
 
        return parent[i] = find(parent[i]);
    }
 
    // Union function
    void unite(int x, int y)
    {
        int s1 = find(x);
        int s2 = find(y);
 
        if (s1 != s2) {
            if (rank[s1] < rank[s2]) {
                parent[s1] = s2;
                rank[s2] += rank[s1];
            }
            else {
                parent[s2] = s1;
                rank[s1] += rank[s2];
            }
        }
    }
};
 
class Graph {
    vector<vector<int> > edgelist;
    int V;
 
public:
    Graph(int V) { this->V = V; }
 
    void addEdge(int x, int y, int w)
    {
        edgelist.push_back({ w, x, y });
    }
 
    void kruskals_mst()
    {
        sort(edgelist.begin(), edgelist.end());
 
        DSU s(V);
        int ans = 0; //peso total do MST
        for (auto edge : edgelist) {
            int w = edge[0];
            int x = edge[1];
            int y = edge[2];
            if (s.find(x) != s.find(y))
            {
                s.unite(x, y);
                ans += w;
                cout << x << " -- " << y << " == " << w << endl;//MST
            }
        }
    }
};
