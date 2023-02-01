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
//log2(o)
int gcd(int a, int b)
{
    if (a == 0)
        return b;
    return gcd(b % a, a);
}
 
int phi(unsigned int n)
{
    unsigned int result = 1;
    for (int i = 2; i < n; i++)
        if (gcd(i, n) == 1)
            result++;
    return result;
}

#define ll long long int

const int mx=1e6+1; //10^6+1

ll phi[mx];
ll lcm[mx];
//soma de todos
void totient_sieve()
{
    for(int i=1;i<mx;i++)
    {
        phi[i]=i;
    }
    for(int p=2;p<mx;p++)
    {
        if(phi[p]==p)
        {
            phi[p]=p-1;
            for(int i=2*p;i<mx;i=i+p)
            {
                phi[i]=(phi[i]/p)*(p-1);
            }
        }
    }
}


    for(int i=1;i<mx;i++)
     {
        for(int j=i;j<mx;j=j+i)
        {
            lcm[j]+=(i*phi[i]);
        }
    }

//Primos determinantes

    bool tred;
    string x;
    int cont=-1, l=0, maior=0;
    map <int,pair<int,string>> dic; 
    for(int i=1; i<primes.size() && primes[i]<32000; i++)
    {
        if(cont!=primes[i]-primes[i-1])
        {
            if(tred)
            {
                l++;
                x+=to_string(primes[i-1]);
                dic[primes[i-l]]={primes[i-1],x};
            }
            l=0;
            x.clear();
            cont=primes[i]-primes[i-1];
            x=to_string(primes[i-1])+" ";
            l++;
            tred=false;
        }
        else
        {
            l++;
            maior=primes[i];
            x+=to_string(primes[i-1])+" ";
            tred=true;
        }
    }


//-------------------Frações-------------------void fraction(int p, int q,vector<int>& a) 
void fraction(int p, int q,vector<int>& a) //fração continua
{
    while(q)
    {
        a.push_back(p / q);
        tie(p, q) = make_pair(q, p % q);
    }
}


void fraction(int p, int q,vector<int>& a) 
{
    while(q)
    {
        a.push_back(p / q);
        tie(p, q) = make_pair(q, p % q);
    }
}


/-------------------------------------------/
    int gcd(int a, int b)
{
    if (a == 0)
        return b;
    return gcd(b % a, a);
}
 
// Function to calculate all common divisors
// of two given numbers
// a, b --> input integer numbers
int commDiv(int a, int b)
{
    // find gcd of a, b
    int n = gcd(a, b);
 
    // Count divisors of n.
    int result = 0;
    for (int i = 1; i <= sqrt(n); i++) {
        // if 'i' is factor of n
        if (n % i == 0) {
            // check if divisors are equal
            if (n / i == i)
                result += 1;
            else
                result += 2;
        }
    }
    return result;
}


int lastdigpower(int x, int y)
{
    x = x % 10;
    if(y!=0)
        y = y % 4 + 4;
    return (((int)(pow(x, y))) % 10);
}

/*-----------------------Bitmask------------------*/
//int Set(int N,int pos){return N=N | (1<<pos);}
//int reset(int N,int pos){return N= N & ~(1<<pos);}
//bool check(int N,int pos){return (bool)(N & (1<<pos));}
/*------------------------------------------------*/

/*-----------Number Theory Template------------*/

//#define mx 1000006


/*----------------Sieve--------------------*/
//vector<int>prime;
//bool vis[mx];

//void sieve()
//{
//    int x=sqrt((int)mx);
//    for(int i=3; i<=x; i+=2)
//    {
//        if(vis[i]==0)
//        {
//            for(int j=i*i; j<mx; j+=2*i)
//                vis[j]=1;
//        }
//    }
//    prime.pb(2);
//    for(int i=3; i<mx; i+=2)
//        if(vis[i]==0)
//            prime.pb(i);
//}


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



/*----------------Mobius--------------------*/
//int mu[mx];

//void mobius()
//{
//    for(int i=1; i<mx; i++) mu[i]=1;
//    int root=sqrt((int)mx);
//    for(int i=0; i<SZ(prime) && prime[i]<=root; i++)
//    {
//        int x=prime[i];
//        x=sqr(x);
//        for(int j=x; j<mx; j+=x)
//            mu[j]=0;
//    }
//    for(int i=0; i<SZ(prime); i++)
//    {
//        int x=prime[i];
//        for(int j=x; j<mx; j+=x)
//            mu[j]*=-1;
//    }
//}


/*----------------euler totient 1 to n--------------------*/
//int phi[mx];

//void euler_totient()
//{
//    for(int i=0; i<mx; i++) phi[i]=i;
//    for(int i=2; i<mx; i++)
//    {
//        if(phi[i]==i)
//        {
//            for(int j=i; j<mx; j+=i)
//                phi[j]-=(phi[j]/i);
//        }
//    }
//}

/*----------------euler totient for n--------------------*/
//
//ll euler_totient(ll n)
//{
//    int root=sqrt(n);
//    ll ret=n;
//    for(int i=0; i<SZ(prime) && prime[i]<=root; i++)
//    {
//        if(n%prime[i]==0)
//        {
//            while(n%prime[i]==0)
//                n/=prime[i];
//            root=sqrt(n);
//            ret-=(ret/prime[i]);
//        }
//    }
//    if(n>1)
//    {
//        ret-=(ret/n);
//    }
//    return ret;
//}

/*----------------extended euclid--------------------*/

//long long ext_gcd (long long A, long long B, long long &X, long long &Y)
//{
//    long long x2, y2, x1, y1, x, y, r2, r1, q, r;
//    x2 = 1, y2 = 0;
//    x1 = 0, y1 = 1;
//    for (r2 = A, r1 = B; r1 != 0; r2 = r1, r1 = r, x2 = x1, y2 = y1, x1 = x, y1 = y )
//    {
//        q = r2 / r1;
//        r = r2 % r1;
//        x = x2 - (q * x1);
//        y = y2 - (q * y1);
//    }
//    X = x2;
//    Y = y2;
//    return r2;
//}


/*----------------Mod Inverse--------------------*/

//inline long long modInv (long long a, long long m)
//{
//    long long x, y;
//    ext_gcd(a, m, x, y);
//    x %= m;
//    if (x < 0) x += m;
//    return x;
//}

/*----------------bigmod--------------------*/

//inline long long bigmod (long long a, long long p, long long m)
//{
//    long long res = 1 % m, x = a % m;
//    while ( p )
//    {
//        if ( p & 1 ) res = ( res * x ) % m;
//        x = ( x * x ) % m;
//        p >>= 1;
//    }
//    return res;
//}

/*----------------linear Diophantine equation--------------------*/
//
//bool linearDiophantine ( long long A, long long B, long long C, long long &x, long long &y )
//{
//    int g = gcd ( A, B );
//    if ( C % g != 0 ) return false; //No Solution
//
//    int a = A / g, b = B / g, c = C / g;
//    if ( g < 0 )   //Make Sure gcd(a,b) = 1
//    {
//        a *= -1;
//        b *= -1;
//        c *= -1;
//    }
//    ext_gcd( a, b, x, y ); //Solve ax + by = 1
//
//
//    x *= c;
//    y *= c; //ax + by = c
//    return true; //Solution Exists
//    //more solution {x+k*(b/g), y-k*(a/g)}
//}

/*-----------------Chinese Remainder-----------*/

//long long CRT_weak(vector<long long>A, vector<long long>B)
//{
//    ll X=0;
//    ll N=1;
//    ll y,z;
//    for(int i=0; i<SZ(B); i++)
//        N*=B[i];
//    for(int i=0; i<SZ(A); i++)
//    {
//        y=N/B[i];
//        z=modInv(y,B[i]);
//        X+=(A[i]*y*z);
//        X%=N;
//    }
//    return (X+N)%N;
//}

/*-----------Number Theory End------------*/

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
