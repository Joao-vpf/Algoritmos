//Arvore de fatores de um numero

// Tree node
struct Node
{
    struct Node *left, *right;
    int key;
};
 
// Utility function to create a new tree Node
Node* newNode(int key)
{
    Node* temp = new Node;
    temp->key = key;
    temp->left = temp->right = NULL;
    return temp;
}
 
// Constructs factor tree for given value and stores
// root of tree at given reference.
void createFactorTree(struct Node **node_ref, int v)
{
    (*node_ref) = newNode(v);
 
    // the number is factorized
    for (int i = 2 ; i < v/2 ; i++)
    {
        if (v % i != 0)
          continue;
 
        // If we found a factor, we construct left
        // and right subtrees and return. Since we
        // traverse factors starting from smaller
        // to greater, left child will always have
        // smaller factor
        createFactorTree(&((*node_ref)->left), i);
        createFactorTree(&((*node_ref)->right), v/i);
        return;
    }
}
 
// Iterative method to find the height of Binary Tree
void printLevelOrder(Node *root)
{
    // Base Case
    if (root == NULL)  return;
 
    queue<Node *> q;
    q.push(root);
 
    while (q.empty() == false)
    {
        // Print front of queue and remove
        // it from queue
        Node *node = q.front();
        cout << node->key << " ";
        q.pop();
        if (node->left != NULL)
            q.push(node->left);
        if (node->right != NULL)
            q.push(node->right);
    }
}

createFactorTree(&root, val);//cria o node a partir do valor que voce quer
printLevelOrder(root); //mostra os divisores

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
