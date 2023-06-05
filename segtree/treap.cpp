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


struct Node {
    int key;
    int priority;
    int sum;
    int lazy;
    Node* left;
    Node* right;

    Node(int k) : key(k), priority(rand()), sum(k), lazy(0), left(NULL), right(NULL) {}
};

class Treap {
private:
    Node* root;

    int getSum(Node* node) {
        return node ? node->sum + (node->lazy * (node->right - node->left + 1)) : 0;
    }

    void updateSum(Node* node) {
        if (node) {
            node->sum = getSum(node->left) + getSum(node->right) + node->key;
        }
    }

    void updateLazy(Node* node, int lazy) {
        if (node) {
            node->sum += lazy * (node->right - node->left + 1);
            node->lazy += lazy;
        }
    }

    void propagateLazy(Node* node) {
        if (node && node->lazy != 0) {
            updateLazy(node->left, node->lazy);
            updateLazy(node->right, node->lazy);
            node->lazy = 0;
        }
    }

    void split(Node* node, int key, Node*& left, Node*& right) {
        if (!node) {
            left = right = NULL;
        } else {
            propagateLazy(node);
            if (node->key <= key) {
                split(node->right, key, node->right, right);
                left = node;
            } else {
                split(node->left, key, left, node->left);
                right = node;
            }
            updateSum(node);
        }
    }

    void merge(Node*& node, Node* left, Node* right) {
        propagateLazy(left);
        propagateLazy(right);
        if (!left || !right) {
            node = left ? left : right;
        } else if (left->priority > right->priority) {
            merge(left->right, left->right, right);
            node = left;
        } else {
            merge(right->left, left, right->left);
            node = right;
        }
        updateSum(node);
    }

    void insert(Node*& node, Node* newNode) {
        if (!node) {
            node = newNode;
        } else if (newNode->priority > node->priority) {
            split(node, newNode->key, newNode->left, newNode->right);
            node = newNode;
        } else {
            insert(newNode->key <= node->key ? node->left : node->right, newNode);
        }
        updateSum(node);
    }

    void remove(Node*& node, int key) {
        if (!node) {
            return;
        } else if (node->key == key) {
            Node* temp = node;
            merge(node, node->left, node->right);
            delete temp;
        } else {
            remove(key < node->key ? node->left : node->right, key);
        }
        updateSum(node);
    }

public:
    void updateRange(int left, int right, int value) {
        Node* leftNode, *middleNode, *rightNode;
        split(root, left - 1, leftNode, middleNode);
        split(middleNode, right, middleNode, rightNode);
        updateLazy(middleNode, value);
        merge(middleNode, middleNode, rightNode);
        merge(root, leftNode, middleNode);
    }

    int sumRange(int left, int right) {
        Node* leftNode, *middleNode, *rightNode;
        split(root, left - 1, leftNode, middleNode);
        split(middleNode, right, middleNode, rightNode);
        int result = getSum(middleNode);
        merge(middleNode, middleNode, rightNode);
        merge(root, leftNode, middleNode);
        return result;
    }

    void insertRange(int left, int right, int value) {
        Node* leftNode, *rightNode;
        split(root, left - 1, leftNode, rightNode);
        Node* newNode = new Node(value);
        merge(leftNode, leftNode, newNode);
        merge(root, leftNode, rightNode);
    }

    void removeRange(int left, int right) {
        Node* leftNode, *middleNode, *rightNode;
        split(root, left - 1, leftNode, middleNode);
        split(middleNode, right, middleNode, rightNode);
        merge(root, leftNode, rightNode);
    }
};
