string find_largest_repeated_substring(string s)
{//O(n^2logn)
    int n = s.size();

    // Cria um vetor de sufixos da string s
    vector<string> suffixes(n);
    for (int i = 0; i < n; i++) 
    {
        suffixes[i] = s.substr(i);
    }

    // Ordena o vetor de sufixos em ordem lexicográfica
    sort(suffixes.begin(), suffixes.end());

    // Compara os sufixos consecutivos em busca da maior substring que se repete
    string max_repeated_substring = "";
    for (int i = 0; i < n - 1; i++)
    {
        int j = 0;
        while (j < suffixes[i].size() && j < suffixes[i+1].size() && suffixes[i][j] == suffixes[i+1][j])
        {
            j++;
        }

        // Se a substring atual é maior do que a anterior, armazena a nova substring
        if (j > max_repeated_substring.size()) 
        {
            max_repeated_substring = suffixes[i].substr(0, j);
        }
    }

    return max_repeated_substring;
}
