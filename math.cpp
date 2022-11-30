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
void sieve() //peneira de aristotales elimina todos que nao sao primos e ficando apenas os primos
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
