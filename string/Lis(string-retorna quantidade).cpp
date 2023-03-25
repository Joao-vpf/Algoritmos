int lis(string s) 
{//O(nlogn)
    int n = s.size();
    vector<int> dp(n, 1); // vetor dp com valor 1 em todas as posições
    int res = 1; // valor máximo inicializado como 1
    for (int i = 1; i < n; i++) 
    {
        // busca binária pelo maior valor menor que dp[i]
        int lo = 0, hi = res-1, j = -1;
        while (lo <= hi)
        {
            int mid = (lo + hi) / 2;
            if (s[i] > s[j = mid]) lo = mid + 1;
            else hi = mid - 1;
        }
        // atualiza o valor de dp[j+1] se for maior que o valor atual
        dp[j+1] = max(dp[j+1], dp[j] + 1);
        // atualiza o valor máximo
        res = max(res, dp[j+1]);
    }
    return res;
}
