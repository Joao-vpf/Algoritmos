const int mx = 1e6 + 1; // 10^6 + 1

int mu[mx];

// Função que calcula a função de Möbius (mu) para todos os números de 1 a mx-1.
// A função de Möbius retorna os seguintes valores:
//    - mu[n] = 1 se n é uma multiplicação de um número par de fatores primos distintos.
//    - mu[n] = -1 se n é uma multiplicação de um número ímpar de fatores primos distintos.
//    - mu[n] = 0 se n contém um fator primo ao quadrado.
// Parâmetros: Nenhum
// Retorno: Nenhum
// Complexidade: O(n log log n)

void mobius()
{
    for (int i = 1; i < mx; i++)
        mu[i] = 1; // Inicializa mu[i] com 1

    int root = sqrt(mx);

    for (int i = 0; i < SZ(prime) && prime[i] <= root; i++)
    {
        int x = prime[i];
        x = sqr(x);

        for (int j = x; j < mx; j += x)
            mu[j] = 0; // Define mu[j] como 0 para números que contêm um fator primo ao quadrado
    }

    for (int i = 0; i < SZ(prime); i++)
    {
        int x = prime[i];

        for (int j = x; j < mx; j += x)
            mu[j] *= -1; // Inverte o sinal de mu[j] para números que são uma multiplicação de um número ímpar de fatores primos distintos
    }
}
