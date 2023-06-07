typedef struct no* item;


struct no
{
	item l=0, r=0;
	int size =1;
	int prior = rand();
	int x, sum;
	int lazy=0;
	bool rev=0;
	no(int x):x(x), sum(x){}
	void prop()
	{
		if(lazy)
		{
			x+=lazy;
			sum+=lazy*size;
			if(l)l->lazy+=lazy;
			if(r)r->lazy+=lazy;
			lazy=0;
		}
		if(rev)
		{
			swap(l, r);
			if(l)l->rev^=1;
			if(r)r->rev^=1;
			rev=0;
		}
	}
	void upd()
	{
		size=1;
		sum=x;
		if(l)
		{
			size+=l->size;
			sum+=l->sum;
		}
		if(r)
		{
			size+=r->size;
			sum+=r->sum;
		}
	}
};

struct treap
{
	item root= 0;
	void split(item t, item& l, item& r, int n)
	{
		if(!t)
		{
			l=r=0;
			return;
		}
		t->prop();
		int nl = (t->l ?  t->l->size : 0);
		if(nl+1<=n)
		{
			l=t;
			split(l->r, l->r, r, n-nl-1);
		}
		else
		{
			r=t;
			split(r->l, l, r->l, n);
		}
		t->upd();
	}
	void merge(item& t, item l, item r)
	{
		if(l)l->prop();
		if(r)r->prop();
		if(!l)t=r;
		else
		{
			if(!r)t=l;
			else 
			{
				if(l->prior > r->prior)
				{
					t=l;
					merge(t->r, t->r, r);
				}
				else
				{
					t=r;
					merge(t->l, l, t->l);
				}
			}
		}
		if(t) t->upd();
	}
	
	void run( const function<void()>& operation,int i, int j)
	{
		item l, r;
		split(root, l, r, i);
		split(r, root, r, j-i+1);
		operation();
		merge(root, l, root);
		merge(root, root, r);
	}
	
	int sum(int i, int j)
	{
		int ans;
		run([&](){ans=root->sum;}, i, j);
		return ans;
	}
	
	void insert(int i, int x)
	{
		run([&](){root=new no(x);}, i, i-1);
	}
	
	void remove(int i, int j)
	{
		run([&](){delete root;root=0;}, i, j);
	}
	
	void upd(int i, int j, int x)
	{
		run([&](){root->lazy=x;}, i, j);
	}
	
	void rotate(int i, int newi, int j)
	{
		item a, b;
		run([&](){split(root, a, b, newi-i+1);merge(root, b, a);}, i, j);
	}
	void reverse(int i, int j)
	{
		run([&](){root->rev=1},i,j);
	}
};
