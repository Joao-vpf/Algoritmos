inline long long bigmod(long long a, long long p, long long m)
{//O(log p)
    long long res = 1 % m;
    long long x = a % m; 

    while (p)
    {
        if (p & 1) //Se o bit menos significativo de p é 1
            res = (res * x) % m; //Multiplica o resultado atual por x e toma o módulo m

        x = (x * x) % m; //Calcula o quadrado da base e toma o módulo m
        p >>= 1; //Desloca p para a direita, removendo o bit menos significativo
    }

    return res; 
}
