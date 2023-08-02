const int MAXN = 405000;
const int MAXLOG = 22;

int n, qn;
vector <int> g[MAXN];   
int dp[MAXN][MAXLOG];
int tin[MAXN], tout[MAXN];
int timer;

int a[MAXN];
int x, y, z;
long long ans;

void dfs(int v, int par = 1) {
    timer++;
    tin[v] = timer;

    dp[v][0] = par;
    for (int i = 1; i < MAXLOG; i++) 
        dp[v][i] = dp[dp[v][i - 1]][i - 1];

    for (int i = 0; i < (int) g[v].size(); i++) {
        int to = g[v][i];
        if (to != par)
            dfs(to, v);
    }

    timer++;
    tout[v] = timer;
}

bool isParent(int a, int b) {
    return tin[a] <= tin[b] && tout[a] >= tout[b];
}

int lca(int a, int b) {
    if (isParent(a, b))
        return a;
    if (isParent(b, a))
        return b;
    for (int i = MAXLOG - 1; i >= 0; i--) { 
        if (!isParent(dp[a][i], b))
            a = dp[a][i];
    }
    return dp[a][0];
}
//MAIN:
dfs(1);
lca(x,y)
