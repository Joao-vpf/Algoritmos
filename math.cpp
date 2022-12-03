//Arvore de fatores de um numero

// Tree node
class Node
{
    public:
    Node *left;
    Node *right;
    long long key;
    static Node* newNode(long long key)
    {
        Node* temp = new Node;
        temp->key = key;
        temp->left = temp->right = NULL;
        return temp;
    }
};
class Ftree
{
    Node* root;
    void createFactorTree(Node **node_ref, long long v)
    {
        (*node_ref) = Node::newNode(v);
        for (int i = 2 ; i < v/2 ; i++)
        {
            if (v % i != 0)
            continue;
            createFactorTree(&((*node_ref)->left), i);
            createFactorTree(&((*node_ref)->right), v/i);
            return;
        }
    }
    
    long long printLevelOrder(Node *root, queue<long long>& q) //alterando isso aqui pode mostrar a arvore
    {
        if(root)
        {
            long long l=printLevelOrder(root->left, q);
            long long r=printLevelOrder(root->right, q);
            if(l==r && r==0)
            {
                q.push(root->key);
            }
            return root->key;
        }
        return 0;
    }
    void dell(Node* root)
    {
        if(root)
        {
            dell(root->left);
            dell(root->right);
            delete root;
        }
    }
    public:
    Ftree()
    {
        Node* root = NULL;
    }
    void create (long long val)
    {
        createFactorTree(&root, val);
    }
    int print(queue<long long>& q)
    {
        return printLevelOrder(root, q); //root
    }
    ~Ftree()
    {
        dell(root);
    }
};

//Acha a altura da arvore consequentimente a quantidade de fatores
// Function to find the height of the
// Factor Tree of the integer N
int factorTree(int N)
{
    // Stores the height of Factor Tree
    int height = 0;
 
    // Loop to iterate over values of N
    while (N > 1) {
        // Stores if there exist
        // a factor of N or not
        bool flag = false;
 
        // Loop to find the smallest
        // factor of N
        for (int i = 2; i <= sqrt(N); i++) {
            // If i is a factor of N
            if (N % i == 0) {
                N = N / i;
                flag = true;
                break;
            }
        }
 
        // Increment the height
        height++;
 
        // If there are no factors of N
        // i.e, N is prime, break loop
        if (!flag) {
            break;
        }
    }
 
    // Return Answer
    return height;
}
//----------------Fatoração----------
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

vector<int> primeFactors(long long n, vector<int>& factors) {
    long long PF_idx = 0, PF = primes[PF_idx];
    while(PF * PF <= n) {
        while(n % PF == 0) {
            n /= PF;
            factors.push_back(PF);
        }
        PF = primes[++PF_idx]; // next prime
    }
    if (n != 1) factors.push_back(n); // remaining num is a prime
    return factors;
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

//Função Totiente Euler
        
int phi(int n)//verifica quantos numeros gcd o numero n tem
{
    int result = n;
    for(int p = 2; p * p <= n; ++p)
    {
         
        if (n % p == 0)
        {
             
            while (n % p == 0)
                n /= p;
                 
            result -= result / p;
        }
    }
  
    if (n > 1)
        result -= result / n;
         
    return result;
}
