#include <iostream>
#include <vector>
using namespace std;
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
		upd(x,l);
		up(r+1, x);
		up(r, -x);
	}
};


struct primosgold
{
	map<int,int> id;
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
