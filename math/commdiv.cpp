// Função para calcular todos os divisores comuns de dois números dados.

// Parâmetros:
//    a: o primeiro número inteiro
//    b: o segundo número inteiro
// Retorno:
//    O número de divisores comuns entre a e b.
// Complexidade:
// O(log(min(a, b)) + sqrt(GCD))
int commDiv(int a, int b)
{
    // Encontrar o maior divisor comum (GCD) entre a e b
    int n = gcd(a, b);

    // Contar os divisores de n.
    int result = 0;
    for (int i = 1; i <= sqrt(n); i++) {
        // Se 'i' for divisor de n
        if (n % i == 0) {
            // Verificar se os divisores são iguais
            if (n / i == i)
                result += 1; // Incrementar o resultado por 1
            else
                result += 2; // Incrementar o resultado por 2 (pois os divisores são distintos)
        }
    }
    return result;
}
