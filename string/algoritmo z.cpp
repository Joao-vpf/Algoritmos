const int maxn = (10e5)*5;
int z[maxn];
int n;

void z_algorithm(string& s) 
{
    n = s.length();
    int l = 0, r = 0;
    for (int i = 1; i < n; i++) 
    {
        // Se i estiver dentro da janela [l, r], pode-se aproveitar os valores já calculados
        if (i <= r) z[i] = min(r - i + 1, z[i - l]);
        // Estende o palíndromo a partir da posição i
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;
        // Se o palíndromo atual se estende além da janela [l, r], atualiza l e r
        if (i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
    }
}
