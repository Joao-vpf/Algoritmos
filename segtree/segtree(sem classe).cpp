
const int N = 1e5*2;
int tree[4 * N];
int arr[N];

void build(int node, int l, int r) 
{
    if (l == r) 
    {
        tree[node] = arr[l];
       return;
    } 
    int mid = (l + r) / 2;
    build(2 * node, l, mid);
    build(2 * node + 1, mid + 1, r);
    tree[node] = tree[2 * node] + tree[2 * node + 1];
}

void update(int node, int l, int r, int idx, int val) 
{
    if (l == r) 
    {
        tree[node] += val;
        return;
    } 
    int mid = (l + r) / 2;
    if (idx <= mid) 
    {
        update(2 * node, l, mid, idx, val);
    } 
    else 
    {
        update(2 * node + 1, mid + 1, r, idx, val);
    }
    tree[node] = tree[2 * node] + tree[2 * node + 1];
}

int query(int node, int l, int r, int ql, int qr)
 {
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
