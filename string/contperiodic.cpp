    // Função que retorna verdadeiro se sub-corda 
    // de comprimento k a partir do índice i também é 
    // um prefixo da corda
    bool isPrefix(string str, int len, int i, int k)
    {
        // k comprimento da sub-corda não pode começar no índice i
        if (i + k > len)
            return false;
        for (int j = 0; j < k; j++) 
        {
 
            // Descasamento de caracteres entre o prefixo
            // e a sub-corda a partir do índice i
            if (str[i] != str[j])
                return false;
            i++;
        }
        return true;
    }
 
    // Função que retorna verdadeiro se str for K-periodic
    bool isKPeriodic(string str, int len, int k)
    {
        // Verifique se todas as sub-cordas
        // str[0, k-1], str[k, 2k-1] ... são iguais
        // para o prefixo k de comprimento da corda
        for (int i = k; i < len; i += k)
            if (!isPrefix(str, len, i, k))
                return false;
        return true;
    }
 
