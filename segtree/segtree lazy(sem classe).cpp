const int N = 2e5+5;
int arr[N];
ll tree[4 * N];
ll lazy[4 * N];

void push(int node, int l, int r) 
{
    if(lazy[node])
    {
        tree[node] += (r-l +1) * lazy[node];
        if(l != r)
        {
            lazy[node*2] += lazy[node];
            lazy[node*2+1] += lazy[node];
        }
        lazy[node]=0;
    }
}

void build(int node, int l, int r)
{
    if (l == r) 
    {
        tree[node] = arr[l];
        lazy[node]=0;
        return;
    } 
	int mid = (l + r) / 2;
	build( 2 * node, l, mid);
	build( 2 * node + 1, mid + 1, r);
	lazy[node]=0;
    tree[node] = tree[2 * node] + tree[2 * node + 1];
}

void update(int node, int l, int r, int ql, int qr, int val) 
{
    push(node, l, r);

    if (l>r || qr < l || ql > r)  return;

    if (ql <= l && qr >= r) 
    {
        tree[node] += (r-l+1) * val;
        
        if(l != r)
        {
            lazy[node*2] += val;
            lazy[node*2+1] += val;
        }

        return;
    } 
    
    int mid = (l + r) / 2;
    update(2 * node, l, mid, ql, qr, val);
    update(2 * node + 1, mid + 1, r, ql, qr, val);
    tree[node] = tree[2 * node] + tree[2 * node + 1];
}

ll query(int node, int l, int r, int ql, int qr) 
{
    push(node, l, r);

    if (qr < l || ql > r) 
    {
        return 0;
    } 

    if (ql <= l && qr >= r) 
    {
        return tree[node];
    } 
    
    int mid = (l + r) / 2;
    return query(2 * node, l, mid, ql, qr) + query(2 * node + 1, mid + 1, r, ql, qr);
}
