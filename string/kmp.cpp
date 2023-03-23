int kmp(const string& texto, const string& padrao)
{
    int n = texto.size(), m = padrao.size();
    vector<int> pi(m, 0);  // vector para guardar as funções prefixo
    // vector<int> ocorrencias;  // vector para guardar as posições onde o padrão ocorre
    int cont=0;
    
    // Cálculo das funções prefixo
    for (int i = 1, j = 0; i < m; ++i) 
    {
        while (j > 0 && padrao[i] != padrao[j]) j = pi[j - 1];
        if (padrao[i] == padrao[j]) ++j;
        pi[i] = j;
    }

    // Busca de padrão no texto
    for (int i = 0, j = 0; i < n; ++i) 
    {
        while (j > 0 && texto[i] != padrao[j])j = pi[j - 1];

        if (texto[i] == padrao[j])++j;

        if (j == m) 
        {
            cont++;
            //ocorrencias.push_back(i - m + 1);
            j = pi[j - 1];
        }
    }

  return cont;
}

