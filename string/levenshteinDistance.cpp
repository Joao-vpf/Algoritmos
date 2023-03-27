// Função que retorna a distância de Levenshtein entre duas palavras
int levenshteinDistance(const string& s1, const string& s2) 
{
    int n = s1.size();
    int m = s2.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1));
    for (int i = 0; i <= n; i++) 
    {
        dp[i][0] = i;
    }
    for (int j = 0; j <= m; j++) 
    {
        dp[0][j] = j;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++)
         {
            if (s1[i - 1] == s2[j - 1]) 
            {
                dp[i][j] = dp[i - 1][j - 1];
            } 
            else 
            {
                dp[i][j] = 1 + min({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]});
            }
        }
    }
    return dp[n][m];//retorna a distancia
}

// Função que encontra sugestões de correção ortográfica para uma palavra
string findSpellingSuggestions(const string& word, const vector<string>& dictionary) 
{
    vector<string> suggestions;
    int sizew = word.size();
    for (const string& dictWord : dictionary) 
    {
        int distance = levenshteinDistance(word, dictWord);
        if (distance == 1) 
        {
            // uma letra a mais ou a menos
            return dictWord;//retorna a primeira palavra que achou no dicionario
            suggestions.push_back(dictWord);//adiciona no sugestão de palavras
        } 
        else
        { 
            if (distance == 2) 
            {
                // uma letra diferente ou trocada na adjacencia 
                for (int i = 0; i < sizew - 1; i++) 
                {
                    string swappedWord = word;
                    swap(swappedWord[i], swappedWord[i + 1]);
                    if (swappedWord == dictWord) 
                    {
                         return dictWord;//retorna a primeira palavra que achou no dicionario
                        suggestions.push_back(dictWord);//adiciona no sugestão de palavras
                        break;
                    }
                }
            }
        }
    }
    return "";
}

