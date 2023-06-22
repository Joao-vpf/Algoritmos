/*----------------euler totient 1 to n--------------------*/
// Função que calcula a função totiente de Euler (phi) para cada número de 1 a 'n'.
// A função totiente de Euler é o número de inteiros positivos menores ou iguais a 'n'
// que são coprimos com 'n' (ou seja, têm o máximo divisor comum igual a 1).
// Parâmetros:
//    n: o valor máximo para o qual deseja-se calcular a função totiente de Euler
// Retorno:
//    A função não retorna nenhum valor, mas atualiza o array 'phi' com os valores calculados.
// Complexidade: O(n log log n)

int phi[mx];

void euler_totient(int n)
{
    for (int i = 0; i <= n; i++)
        phi[i] = i; // Inicializa todos os valores de phi[i] com i

    for (int i = 2; i <= n; i++)
    {
        if (phi[i] == i)
        {
            for (int j = i; j <= n; j += i)
                phi[j] -= (phi[j] / i); // Atualiza os valores de phi[j] para os múltiplos de i
        }
    }
}


/*----------------euler totient for n--------------------*/

// Função que calcula a função totiente de Euler (phi) para o número 'n'.
// A função totiente de Euler é o número de inteiros positivos menores que 'n'
// que são coprimos com 'n' (ou seja, têm o máximo divisor comum igual a 1).
// Parâmetros:
//    n: o número para o qual deseja-se calcular a função totiente de Euler
// Retorno:
//    O valor da função totiente de Euler para o número 'n'
// Complexidade: O(sqrt(n))

ll euler_totient(ll n)
{
    int root = sqrt(n);
    ll ret = n;

    for (int i = 0; i < SZ(prime) && prime[i] <= root; i++)
    {
        if (n % prime[i] == 0)
        {
            while (n % prime[i] == 0)
                n /= prime[i]; // Divide n pelos fatores primos repetidamente
            root = sqrt(n);
            ret -= (ret / prime[i]); // Atualiza o valor de ret subtraindo ret dividido por prime[i]
        }
    }

    if (n > 1)
    {
        ret -= (ret / n); // Se sobrar algum fator primo, atualiza o valor de ret subtraindo ret dividido por n
    }

    return ret;
}

/*----------------euler totient para soma todos lcms--------------------*/
const int mx = 1e6 + 1; // 10^6 + 1

ll phi[mx];
ll lcm[mx];

// Função que precalcula os valores da função totiente de Euler (phi) para todos os números de 1 a mx-1,
// e também calcula o menor múltiplo comum (lcm) para todos os números de 1 a mx-1.
// Parâmetros: Nenhum
// Retorno: Nenhum
// Complexidade: O(n log log n)

void totient_sieve()
{
    for (int i = 1; i < mx; i++)
    {
        phi[i] = i; // Inicializa phi[i] com i
        lcm[i] = i; // Inicializa lcm[i] com i
    }

    for (int p = 2; p < mx; p++)
    {
        if (phi[p] == p)
        {
            phi[p] = p - 1; // Atualiza phi[p] para números primos

            for (int i = 2 * p; i < mx; i += p)
            {
                phi[i] = (phi[i] / p) * (p - 1); // Atualiza phi[i] para múltiplos de p
                lcm[i] = (lcm[i] / p) * (p); // Atualiza lcm[i] para múltiplos de p
            }
        }
    }
}

// Função que calcula a função totiente de Euler (phi) para o número 'n'*SEM PRECISAR DE CALULCAR OS PRIMOS*.
// A função totiente de Euler é o número de inteiros positivos menores que 'n'
// que são coprimos com 'n' (ou seja, têm o máximo divisor comum igual a 1).
// Parâmetros:
//    n: o número para o qual deseja-se calcular a função totiente de Euler
// Retorno:
//    O valor da função totiente de Euler para o número 'n'
// Complexidade: O(sqrt(n))

int phi(int n)
{
    int result = n;

    for (int p = 2; p * p <= n; ++p)
    {
        if (n % p == 0)
        {
            while (n % p == 0)
                n /= p; // Divide n pelos fatores primos repetidamente

            result -= result / p; // Atualiza o valor de result subtraindo result dividido por p
        }
    }

    if (n > 1)
        result -= result / n; // Se sobrar algum fator primo, atualiza o valor de result subtraindo result dividido por n

    return result;
}

