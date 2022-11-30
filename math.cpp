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
