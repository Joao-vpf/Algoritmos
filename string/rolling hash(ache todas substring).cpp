vector<string> findSubstrings(string s) 
{//Rolling hash O(n^2)
    int n = s.length();
    vector<string> substrings;
    unordered_set<int> seen;
    // Calcula as potências de p para cada posição da string s
    const int p = 31;
    const int m = 1e9 + 9;
    // Calcula as potências de p para cada posição da string s

    vector<long long> p_pow(n);
    p_pow[0] = 1;
    for (int i = 1; i < n; i++) 
    {
        p_pow[i] = (p_pow[i-1] * p) % m;
    }
    // Calcula o hash polinomial de cada prefixo da string s
    vector<long long> h(n+1, 0);
    for (int i = 0; i < n; i++) 
    {
        h[i+1] = (h[i] + (s[i] - 'a' + 1) * p_pow[i]) % m;
    }
    // Encontra todas as substrings distintas de s
    for (int len = 1; len <= n; len++) 
    {
        for (int i = 0; i <= n-len; i++) 
        {
            int j = i + len - 1;
            // Calcula o hash polinomial da substring atual
            long long hash = (h[j+1] - h[i] + m) % m;
            hash = (hash * p_pow[n-i-1]) % m; 
            // Calcula o hash polinomial da substring atual
            if (seen.count(hash) == 0) 
            {
                substrings.push_back(s.substr(i, len));
            };
                seen.insert(hash)
        }
    }
    return substrings;
}
