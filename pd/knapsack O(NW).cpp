int olha(int W,  vector<pii> v) //V é uma pair <peso, preco>
{
    int dp[W + 1];
    memset(dp, 0, sizeof(dp));
 
    for (int i = 1; i < n + 1; i++) {
        for (int w = W; w >= 0; w--) {
 
            if (v[i - 1].first <= w)
                dp[w] = max(dp[w],dp[w - v[i - 1].first] + v[i - 1].second);
        }
    }
    return dp[W]; 
}
