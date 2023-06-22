// Função que implementa o Teorema Chinês dos Restos (Chinese Remainder Theorem - CRT) de forma simplificada.
// Essa versão assume que os módulos dados em B são coprimos entre si.
// Parâmetros:
//    A: vetor contendo os resíduos (restos) do sistema de congruências
//    B: vetor contendo os módulos correspondentes ao sistema de congruências
// Retorno:
//    O valor da solução única do sistema de congruências usando o CRT
// Complexidade: O(N), onde N é o número de elementos nos vetores A e B

long long CRT_weak(vector<long long> A, vector<long long> B)
{
    long long X = 0;
    long long N = 1;
    long long y, z;

    for (int i = 0; i < SZ(B); i++)
        N *= B[i]; // Calcula o produto de todos os módulos

    for (int i = 0; i < SZ(A); i++)
    {
        y = N / B[i]; // Calcula o produto dos módulos exceto o atual
        z = modInv(y, B[i]); // Calcula o inverso multiplicativo de y (mod B[i])
        X += (A[i] * y * z); // Soma o produto do resíduo pelo produto dos módulos e seu inverso
        X %= N; // Toma o módulo N para evitar estouro de memória
    }

    return (X + N) % N; // Garante que a solução seja um número não negativo
}
