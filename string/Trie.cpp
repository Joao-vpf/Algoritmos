struct node
{
	map<char, int> next;
	bool world;
	
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
