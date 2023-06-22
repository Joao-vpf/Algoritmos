// Funções para manipulação de bits em um número inteiro usando operações de bitmask.

// Função para definir (set) o bit na posição "pos" no número "N" como 1.
// Parâmetros:
//    N: o número inteiro
//    pos: a posição do bit a ser definido como 1
// Retorno:
//    O número "N" com o bit na posição "pos" definido como 1.
int Set(int N, int pos)
{
    return N = N | (1 << pos);
}

// Função para zerar (reset) o bit na posição "pos" no número "N".
// Parâmetros:
//    N: o número inteiro
//    pos: a posição do bit a ser zerado
// Retorno:
//    O número "N" com o bit na posição "pos" zerado.
int reset(int N, int pos)
{
    return N = N & ~(1 << pos);
}

// Função para verificar se o bit na posição "pos" no número "N" é 1.
// Parâmetros:
//    N: o número inteiro
//    pos: a posição do bit a ser verificado
// Retorno:
//    Retorna true se o bit na posição "pos" for 1, caso contrário, retorna false.
bool check(int N, int pos)
{
    return (bool)(N & (1 << pos));
}
