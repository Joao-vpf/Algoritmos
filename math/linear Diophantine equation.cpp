// Função que resolve uma equação Diofantina linear da forma Ax + By = C,
// onde A, B e C são constantes inteiras, e x e y são variáveis inteiras desconhecidas.
// Parâmetros:
//    A, B, C: constantes da equação
//    x, y: referências para armazenar as soluções da equação
// Retorno:
//    Retorna verdadeiro se houver solução para a equação, falso caso contrário.
//    As soluções são armazenadas nas variáveis x e y.
// Complexidade: O(log min(A, B))

bool linearDiophantine(long long A, long long B, long long C, long long &x, long long &y)
{
    int g = gcd(A, B); // Calcula o máximo divisor comum de A e B
    if (C % g != 0)
        return false; // Não há solução se C não é divisível por g

    int a = A / g, b = B / g, c = C / g;
    if (g < 0) // Garante que gcd(a,b) = 1
    {
        a *= -1;
        b *= -1;
        c *= -1;
    }

    ext_gcd(a, b, x, y); // Resolve a equação ax + by = 1 usando o algoritmo de Euclides estendido

    x *= c;
    y *= c; // Multiplica as soluções por c para obter ax + by = c
    return true; // Solução existe
    // Há mais soluções da forma {x + k*(b/g), y - k*(a/g)}
}
