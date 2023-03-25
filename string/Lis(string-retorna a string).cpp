string lis(string s) 
{//O(nlogn)
    int n = s.size();

    // Vetor auxiliar de índices
    vector<int> idx(n);

    // Vetor para armazenar os caracteres da subsequência atual
    vector<char> subseq;

    for (int i = 0; i < n; i++) 
    {
        // Encontra a posição do primeiro elemento no vetor
        // de índices que é maior ou igual ao caractere atual
        auto it = lower_bound(subseq.begin(), subseq.end(), s[i]);

        if (it == subseq.end()) 
        {
            // Se o caractere atual é maior do que o último
            // caractere da subsequência, adicionamos o índice
            // desse caractere ao vetor de índices e o adicionamos
            // ao vetor de caracteres da subsequência atual
            idx[i] = subseq.size();
            subseq.push_back(s[i]);
        } 
        else 
        {
            // Se o caractere atual é menor do que o último
            // caractere da subsequência, substituímos o índice
            // correspondente no vetor de índices pelo índice
            // do caractere atual
            idx[i] = it - subseq.begin();
            *it = s[i];
        }
    }

    // Reconstrói a subsequência usando os índices armazenados
    // no vetor de índices
    string ans(subseq.size(), ' ');
    for (int i = n - 1; i >= 0; i--) 
    {
        if (idx[i] == subseq.size() - 1) 
        {
            ans[subseq.size() - 1] = s[i];
            subseq.pop_back();
        }
    }

    return ans;
}
