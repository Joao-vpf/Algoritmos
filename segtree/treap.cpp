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
		split(r, root, r, j-i-1);
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



struct Node 
{
    int key, priority;
    int sum;
    int lazy;
    Node *left, *right;

    Node(int k) : key(k), priority(RANDOM()), sum(k), lazy(0), left(nullptr), right(nullptr) {}
};

class treap 
{
private:
    Node *root;

    int getSum(Node* node) 
    {
        return node ? node->sum : 0;
    }

    void updateSum(Node* node) 
    {
		
        if (node) 
        {
            node->sum = node->key + getSum(node->left) + getSum(node->right);
        }
    }

    void propagateLazy(Node* node) 
    {
        if (node->left) 
        {
            node->left->lazy += node->lazy;
            node->left->key += node->lazy;
            node->left->sum += getSum(node->left) * node->lazy;
        }

        if (node->right) 
        {
            node->right->lazy += node->lazy;
            node->right->key += node->lazy;
            node->right->sum += getSum(node->right) * node->lazy;
        }
        node->lazy = 0;
    }

    void split(Node* current, int key, Node*& left, Node*& right) 
    {
        if (!current) 
        {
            left = right = nullptr;
        } 
        else 
        {
            propagateLazy(current);
            if (key < current->key) 
            {
                split(current->left, key, left, current->left);
                right = current;
            } 
            else 
            {
                split(current->right, key, current->right, right);
                left = current;
            }
        }

        updateSum(current);
    }

    void merge(Node*& current, Node* left, Node* right) 
    {
        if (!left || !right) 
        {
            current = left ? left : right;
        } 
        else 
        {
            propagateLazy(left);
            propagateLazy(right);
            if (left->priority > right->priority) 
            {
                merge(left->right, left->right, right);
                current = left;
            } 
            else 
            {
                merge(right->left, left, right->left);
                current = right;
            }
        }

        updateSum(current);
    }

    void insert(Node*& current, Node* newNode) 
    {
        if (!current) {
            current = newNode;
        } 
        else 
        {
            propagateLazy(current);

            if (newNode->priority > current->priority) 
            {
                split(current, newNode->key, newNode->left, newNode->right);
                current = newNode;
            } 
            else 
            {
                insert(newNode->key < current->key ? current->left : current->right, newNode);
            }
        }

        updateSum(current);
    }

    void erase(Node*& current, int key) 
    {
        if (!current) 
        {
            return;
        } 
        else 
        {
            propagateLazy(current);

            if (current->key == key) 
            {
                Node* temp = current;
                merge(current, current->left, current->right);
                delete temp;
            } 
            else 
            {
                erase(key < current->key ? current->left : current->right, key);
            }
        }

        updateSum(current);
    }

    void updateRange(Node*& current, int l, int r, int val) 
    {
        if (!current) 
        {
            return;
        }

        propagateLazy(current);

        if (current->key >= l && current->key <= r) 
        {
            current->key += val;
            current->sum += getSum(current) * val;

            if (current->left) 
            {
                current->left->lazy += val;
                current->left->key += val;
                current->left->sum += getSum(current->left) * val;
            }

            if (current->right) 
            {
                current->right->lazy += val;
                current->right->key += val;
                current->right->sum += getSum(current->right) * val;
            }
        } 
        else 
		{
			if (current->key < l) 
			{
				updateRange(current->right, l, r, val);
			} 
			else 
			{
				updateRange(current->left, l, r, val);
			}
		}

        updateSum(current);
    }

    int sumRange(Node*& current, int l, int r) 
    {
        if (!current) 
        {
            return 0;
        }

        propagateLazy(current);

        if (current->key >= l && current->key <= r) 
        {
            return current->key + getSum(current->left) + getSum(current->right);
        } 
        if (current->key < l) 
        {
            return sumRange(current->right, l, r);
        }  
         return sumRange(current->left, l, r);
    }

public:
    treap() : root(nullptr) {}

    void insert(int key) 
    {
        Node* newNode = new Node(key);
        insert(root, newNode);
    }

    void update(int oldKey, int newKey) 
    {
        erase(root, oldKey);
        insert(newKey);
    }

    void erase(int key) 
    {
        erase(root, key);
    }

    void updateRange(int l, int r, int val) 
    {
        updateRange(root, l, r, val);
    }

    int sumRange(int l, int r) 
    {
        return sumRange(root, l, r);
    }
};
