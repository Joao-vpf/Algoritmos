/*----------------extended euclid--------------------*/

// Função que calcula o algoritmo de Euclides estendido para encontrar o máximo divisor comum (MDC) entre dois números A e B,
// e também encontra os coeficientes X e Y tais que AX + BY = MDC(A, B).
// Parâmetros:
//    A: o primeiro número
//    B: o segundo número
//    X: referência para a variável que armazenará o coeficiente X
//    Y: referência para a variável que armazenará o coeficiente Y
// Retorno:
//    O máximo divisor comum entre A e B
// Complexidade: O(log(min(A, B)))

long long ext_gcd(long long A, long long B, long long &X, long long &Y)
{
    long long x2, y2, x1, y1, x, y, r2, r1, q, r;
    x2 = 1, y2 = 0;
    x1 = 0, y1 = 1;

    for (r2 = A, r1 = B; r1 != 0; r2 = r1, r1 = r, x2 = x1, y2 = y1, x1 = x, y1 = y)
    {
        q = r2 / r1;
        r = r2 % r1;
        x = x2 - (q * x1);
        y = y2 - (q * y1);
    }

    X = x2;
    Y = y2;
    return r2;
}
