/*-----------------Bitwise Sieve---------------*/

#define M 40000000
int marked[M/64 + 2];
vector<int>prime;
#define on(x) (marked[x/64] & (1<<((x%64)/2)))
#define mark(x)  marked[x/64] |= (1<<((x%64)/2))

bool isPrime(int num)
{
    return num > 1 && (num == 2 || ((num & 1) && !on(num)));
}

void sieve(int n)
{
    for (int i = 3; i * i < n; i += 2)
    {
        if (!on(i))
        {
            for (int j = i * i; j <= n; j += i + i)
            {
                mark(j);
            }
        }
    }
    prime.push_back(2);
    for(int i=3;i<M;i+=2)
    {
        if(isPrime(i))
            prime.pb(i);
    }
}

ll primeFactors(int n) //conta os fatores de um numero O(Sqrt(n))
{ 
    ll cont=0;
    while (n%2 == 0) 
    { 
        cont++;
        n = n/2; 
    } 

    for (int i = 3; i <= sqrt(n); i = i+2) 
    {  
        while (n%i == 0) 
        { 
            cont++;
            n = n/i; 
        } 
    } 

    if (n > 2) 
        cont++;

    return cont;
} 

//---------Crivo de Aristostales-------

// This functions finds all primes smaller than 'limit'
// using simple sieve of eratosthenes. It also stores
// found primes in vector prime[]

void simpleSieve(int limit, vector<int> &prime)
{

    // Create a boolean array "mark[0..n-1]" and initialize

    // all entries of it as true. A value in mark[p] will

    // finally be false if 'p' is Not a prime, else true.

    vector<bool> mark(limit + 1, true);
 

    for (int p=2; p*p<limit; p++)

    {

        // If p is not changed, then it is a prime

        if (mark[p] == true)

        {

            // Update all multiples of p

            for (int i=p*p; i<limit; i+=p)

                mark[i] = false;

        }

    }
 

    // Print all prime numbers and store them in prime

    for (int p=2; p<limit; p++)

    {

        if (mark[p] == true)

        {

            prime.push_back(p);

            cout << p << " ";

        }

    }
}
 
// Prints all prime numbers smaller than 'n'

void segmentedSieve(int n)
{

    // Compute all primes smaller than or equal

    // to square root of n using simple sieve

    int limit = floor(sqrt(n))+1;

    vector<int> prime; 

    prime.reserve(limit);

    simpleSieve(limit, prime); 
 

    // Divide the range [0..n-1] in different segments

    // We have chosen segment size as sqrt(n).

    int low = limit;

    int high = 2*limit;
 

    // While all segments of range [0..n-1] are not processed,

    // process one segment at a time

    while (low < n)

    {

        if (high >= n) 

           high = n;

         

        // To mark primes in current range. A value in mark[i]

        // will finally be false if 'i-low' is Not a prime,

        // else true.

        bool mark[limit+1];

        memset(mark, true, sizeof(mark));
 

        // Use the found primes by simpleSieve() to find

        // primes in current range

        for (int i = 0; i < prime.size(); i++)

        {

            // Find the minimum number in [low..high] that is

            // a multiple of prime[i] (divisible by prime[i])

            // For example, if low is 31 and prime[i] is 3,

            // we start with 33.

            int loLim = floor(low/prime[i]) * prime[i];

            if (loLim < low)

                loLim += prime[i];
 

            /* Mark multiples of prime[i] in [low..high]:

                We are marking j - low for j, i.e. each number

                in range [low, high] is mapped to [0, high-low]

                so if range is [50, 100] marking 50 corresponds

                to marking 0, marking 51 corresponds to 1 and

                so on. In this way we need to allocate space only

                for range */

            for (int j=loLim; j<high; j+=prime[i])

                mark[j-low] = false;

        }

        // Numbers which are not marked as false are prime

        for (int i = low; i<high; i++)

            if (mark[i - low] == true)

                cout << i << " ";
 

        // Update low and high for next segment

        low = low + limit;

        high = high + limit;

    }
}


//----------Maior divisor prim-------------------
long long maxPrimeFactors(long long n)
{
    long long maxPrime = -1;
    while (n % 2 == 0) {
        maxPrime = 2;
        n >>= 1; 
    }
     while (n % 3 == 0) {
        maxPrime = 3;
        n=n/3;
    }
 
    for (int i = 5; i <= sqrt(n); i += 6) {
        while (n % i == 0) {
            maxPrime = i;
            n = n / i;
        }
      while (n % (i+2) == 0) {
            maxPrime = i+2;
            n = n / (i+2);
        }
    }
 
    if (n > 4)
        maxPrime = n;
 
    return maxPrime;
}

vector<bool> isPrime(1121, true);
vector<int> primes;
void sieve() //peneira de eratóstenes elimina todos que nao sao primos e ficando apenas os primos
{
    primes.pb(2);
    isPrime[0] = isPrime[1] = false;
    for(int i=3;i<1121;i+=2)
    {
        if(isPrime[i])
        {
            primes.pb(i);
            for(int j=i*i;j<1121;j+=i)
                isPrime[j] = false;
        }
    }
}



void sieve() //peneira de eratóstenes elimina todos que nao sao primos e ficando apenas os primos
{
    primes.clear();
    bitset<1000001> isPrime;
    isPrime.set();
    isPrime[0] = isPrime[1] = false;
    for(long long i=2;i<1000001;i++)
    {
        if(isPrime[i])
        {
            primes.push_back(i);
            for(long long j=i*i;j<1000001;j+=i)
                isPrime[j] = false;
        }
    }
}
