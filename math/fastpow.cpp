// Complexidade: O(log p)

long long fastPow(long long a, long long p) {
    if (p == 0)
        return 1;

    long long res = 1;

    while (p > 0) {
        if (p & 1) // Se o bit menos significativo de p é 1
            res *= a;

        a *= a;
        p >>= 1; // Desloca p para a direita, removendo o bit menos significativo
    }

    return res;
}
// Complexidade: O(log p)

template <typename T>
T fastPow(T a, T p) {
    if (p == 0)
        return 1;

    T res = 1;

    while (p > 0) {
        if (p & 1) // Se o bit menos significativo de p é 1
            res *= a;

        a *= a;
        p >>= 1; // Desloca p para a direita, removendo o bit menos significativo
    }

    return res;
}
