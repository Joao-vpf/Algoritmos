const int N = 1e5*2;
int tree[4 * N];
int lazy[4 * N];

void push(int node, int l, int r) 
{
    if (lazy[node]) 
    {
        tree[node] += (r - l + 1) * lazy[node];
        if (l != r) 
        {
            lazy[2 * node] += lazy[node];
            lazy[2 * node + 1] += lazy[node];
        }
        lazy[node] = 0;
    }
}

void build(vector<int>& arr, int node, int l, int r) 
{
    if (l == r) 
    {
        tree[node] = arr[l];
       
    } 
    else 
    {
        int mid = (l + r) / 2;
        build(arr, 2 * node, l, mid);
        build(arr, 2 * node + 1, mid + 1, r);
        tree[node] = tree[2 * node] + tree[2 * node + 1];
    }
}

void update(int node, int l, int r, int ql, int qr, int val) 
{
    push(node, l, r);
    if (qr < l || ql > r) 
    {
        return;
    } 
    else if (ql <= l && qr >= r) 
    {
        lazy[node] += val;
        push(node, l, r);
    } 
    else 
    {
        int mid = (l + r) / 2;
        update(2 * node, l, mid, ql, qr, val);
        update(2 * node + 1, mid + 1, r, ql, qr, val);
        tree[node] = tree[2 * node] + tree[2 * node + 1];
    }
}

int query(int node, int l, int r, int ql, int qr) 
{
    push(node, l, r);
    if (qr < l || ql > r) 
    {
        return 0;
    } 
    else if (ql <= l && qr >= r) 
    {
        return tree[node];
    } 
    else 
    {
        int mid = (l + r) / 2;
        return query(2 * node, l, mid, ql, qr) + query(2 * node + 1, mid + 1, r, ql, qr);
    }
}
