//topologico basico
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
//verifica todos os tipos de topologico
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
