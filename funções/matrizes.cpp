int multiplicar_matrizes( //calcula multiplicação de matriz de mesmo tamanho
        int matA[][MAX], int na, int ma,
        int matB[][MAX], int nb, int mb,
        int matC[][MAX], int nc, int mc)
{  

    if (ma != nb || na != nc || mb != mc) return 1;

    int a = na, b = ma, c = mb;

    for (int i = 0; i < a; i++) {
        for (int k = 0; k < c; k++) {
            matC[i][k] = 0;
            for (int j = 0; j < b; j++) {
                matC[i][k] += matA[i][j] * matB[j][k];
            }
        }
    }
    return 0;
}
