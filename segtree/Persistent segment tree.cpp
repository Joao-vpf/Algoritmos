const int maxn = 1e6+10;
const int maxq = 1e5+10;
struct node
{
    int sum = 0;
    node* l = 0, *r = 0;
};

node* root[maxq];

node* build(int l, int r)
{
    if (l == r)
    {
        return new node();
    }
    int mid = (l + r) / 2;
    node* newroot = new node();
    newroot->l = build(l, mid);
    newroot->r = build(mid + 1, r);
    return newroot;
}

node* upd(node* prev, int low, int hi, int idx, int val)
{
    if (low > idx || hi < idx) return prev;
    if (low == hi)
    {
        node* newroot = new node();
        newroot->sum = val;
        return newroot;
    }
    int mid = (low + hi) / 2;
    node* newroot = new node();
    newroot->l = upd(prev->l, low, mid, idx, val);
    newroot->r = upd(prev->r, mid + 1, hi, idx, val);
    newroot->sum = newroot->l->sum + newroot->r->sum;
    return newroot;
}

node* upd(node* prev, int low, int hi, int l, int r, int val)
{
    if (low > r || hi < l) return prev;
    if (low == hi)
    {
        node* newroot = new node();
        newroot->sum = 1 - prev->sum;//mudar para val
        return newroot;
    }
    int mid = (low + hi) / 2;
    node* newroot = new node();  
    newroot->l = prev->l; // Reuse the left subtree
    newroot->r = prev->r; // Reuse the right subtree
    
    if (l <= mid)
        newroot->l = upd(prev->l, low, mid, l, r, val);
    if (r > mid)
        newroot->r = upd(prev->r, mid + 1, hi, l, r, val);
    
    newroot->sum = newroot->l->sum + newroot->r->sum;
    return newroot;
}
