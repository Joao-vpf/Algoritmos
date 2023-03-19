const int N = 1e5*2;
int tree[4 * N];
void build(vector<int>& arr, int node, int l, int r) 
{//array, 1, 0, tamanho do array-1
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
{//1, 0, tamanho do veto-1, l, r, vlaor que quer mudar de l a r
    push(node, l, r);
    if (ql > r || qr < l)
    {
        return;
    }
    if (ql <= l && qr >= r)
    {
        tree[node] += (r - l + 1) * val;
        if (l != r)
        {
            lazy[2 * node] += val;
            lazy[2 * node + 1] += val;
        }
        return;
    }
    int mid = (l + r) / 2;
    update(2 * node, l, mid, ql, qr, val);
    update(2 * node + 1, mid + 1, r, ql, qr, val);
    tree[node] = tree[2 * node] + tree[2 * node + 1];
}

void update(int node, int l, int r, int idx, int val) 
{//1, 0, tamanho do array-1, local do vetor base que tem que alterar, valor
    if (l == r) 
    {
        tree[node] = val;
    } 
    else 
    {
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
}

int query(int node, int l, int r, int ql, int qr)
 {//1, 0, tamanho do array-1, 0, ate onde voce quer ir
    if (qr < l || ql > r) 
    {
        return 0;
    }
    else
    { 
        if (ql <= l && qr >= r) 
        {
            return tree[node];
        }
        else 
        {
            int mid = (l + r) / 2;
            return query(2 * node, l, mid, ql, qr) + query(2 * node + 1, mid + 1, r, ql, qr);
        }
    } 
}
