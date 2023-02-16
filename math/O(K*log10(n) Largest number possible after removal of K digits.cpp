//Encontra o maior numero retirando k digitos de um numero n
int maxnumber(int n, int k) // O(K*log10N)
{
    for (int j = 0; j < k; j++) {
 
        int ans = 0;
        int i = 1;
 
        while (n / i > 0)
		{
 
            int temp = (n / (i * 10))
                           * i
                       + (n % i);
            i *= 10;
 
            ans = max(ans, temp);
        }
 
        n = ans;
    }
 
    return n;
}
