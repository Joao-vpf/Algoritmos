string menorstring(vector<string>& strings) 
{//O(n^3 * m), onde n é o número de strings na entrada e m é o comprimento máximo de uma string
    int n = strings.size();
    while (n > 1) 
    {
        int maxOverlap = INT_MIN;
        int a = -1, b = -1;
        string mergedString;

        // Calcula a matriz de sobreposição
        vector<vector<int>> overlap(n, vector<int>(n));
        for (int i = 0; i < n; i++) 
        {
            for (int j = 0; j < n; j++) {
                if (i != j) 
                {
                    int k = min(strings[i].size(), strings[j].size());
                    for (int len = k; len >= 0; len--) 
                    {
                        if (strings[i].substr(strings[i].size() - len) == strings[j].substr(0, len)) 
                        {
                            overlap[i][j] = len;
                            break;
                        }
                    }
                }
            }
        }

        // Encontra as duas strings com a maior sobreposição possível
        for (int i = 0; i < n; i++) 
        {
            for (int j = i + 1; j < n; j++) 
            {
                if (overlap[i][j] > maxOverlap) 
                {
                    maxOverlap = overlap[i][j];
                    a = i;
                    b = j;
                }
            }
        }

        // Concatena as duas strings com a maior sobreposição possível
        mergedString = strings[a] + strings[b].substr(maxOverlap);

        // Remove as duas strings originais da lista e adiciona a nova string mesclada
        strings.erase(strings.begin() + b);
        strings.erase(strings.begin() + a);
        strings.push_back(mergedString);

        n--;
    }

    return strings[0];
}
