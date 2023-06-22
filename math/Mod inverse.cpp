// Função que calcula o inverso multiplicativo de 'a' módulo 'm'.
// Parâmetros:
//    a: o número para o qual queremos encontrar o inverso multiplicativo
//    m: o módulo
// Retorno:
//    O valor do inverso multiplicativo de 'a' módulo 'm'
// Complexidade: O(log m)

inline long long modInv(long long a, long long m)
{
    long long x, y;
    ext_gcd(a, m, x, y); // Calcula o inverso multiplicativo usando o algoritmo de Euclides estendido
    x %= m; // Toma o valor do inverso multiplicativo módulo m

    if (x < 0)
        x += m; // Garante que o inverso multiplicativo seja um número não negativo

    return x;
}
