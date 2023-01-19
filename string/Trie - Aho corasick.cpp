struct node
{
	map<char, int> next, go;//go == dp
	bool world;
    int p, fail=-1;
    char c;
};
vector<node> trie(1);
node root=trie[0];

void insert(string s)
{
	int u=0;
	for (char c: s)
	{
		if(!trie[u].next.count(c))
		{
			trie[u].next[c]=trie.size();
			trie.push_back({});
		}
		u=trie[u].next[c];
	}
	trie[u].world=true;
}

void remove(string s)
{
	int u=0;
	for (char c: s)
	{
		if(!trie[u].next.count(c))
		{
			return;
		}
		u=trie[u].next[c];
	}
	trie[u].world=false;
}

int go(int u,char c)
{
    if(!trie[u].go.count(c))
    {
        trie[u].go[c] = trie[u].next.count(c) ? trie[u].next[c] : u==0 ? 0 : go(find_link(u), c); 
    }
    return trie[u].go[c];
}

int find_link(int u)
{
    if(trie[u].fail==-1)
    {
        trie[u].fail= (u==0 || trie[u].p==0 ? 0 : go(find_link(trie[u].p), trie[u].c));
    }
    return trie[u].fail;
}
