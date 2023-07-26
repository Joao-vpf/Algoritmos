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
