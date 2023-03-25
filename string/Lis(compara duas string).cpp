const int MAXN = 1001;//numeros de caracteres possiveis

int dp[MAXN][MAXN]; // matriz de programação dinâmica

int lis(string a, string b)
{//O(a*b)
    // Tamanhos das strings de entrada
    int n1 = a.size(), n2 = b.size();
    // preenche a primeira linha e coluna da matriz com zeros
    memset(dp, 0, sizeof(dp));

    // preenche a matriz usando programação dinâmica
    for (int i = 1; i <= n1; i++) 
    {
        for (int j = 1; j <= n2; j++) 
        {
            if (a[i-1] == b[j-1]) 
            {
                dp[i][j] = dp[i-1][j-1] + 1;
            } 
            else 
            {
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            }
        }
    }

    // recupera a LCS
    string lcs;
    int i = n1, j = n2;
    while (i > 0 && j > 0) 
    {
        if (a[i-1] == b[j-1]) 
        {
            lcs.push_back(a[i-1]);
            i--, j--;
        } 
        else 
        {
            if (dp[i-1][j] > dp[i][j-1])i--;
            else j--;

        } 
    }
    //return lcs.size();//casos que podem ter letras repetidas 

    reverse(lcs.begin(), lcs.end()); // inverte a LCS para obter a ordem correta

    // encontra a maior subsequência crescente de caracteres comuns
    int n = lcs.size(), ans = 0;
    for (int i = 0; i < n; i++) 
    {
        int j = i, k = i+1;
        while (k < n && lcs[k] >= lcs[j]) 
        {
            j = k;
            k++;
        }
        ans = max(ans, k-i);
        i = j;
    }
    return ans;
}
