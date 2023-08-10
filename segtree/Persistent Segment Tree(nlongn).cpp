
struct Node 
{
    int sum;
    Node* left;
    Node* right;

    Node(int val) : sum(val), left(nullptr), right(nullptr) {}
};

class PersistentSegmentTree 
{
private:
    vector<Node*> versions;

    Node* build(int left, int right, const vector<int>& arr)
     {
        if (left == right) 
        {
            return new Node(arr[left]);
        }
        int mid = left + (right - left) / 2;
        Node* leftChild = build(left, mid, arr);
        Node* rightChild = build(mid + 1, right, arr);
        Node* root = new Node(0);
        root->left = leftChild;
        root->right = rightChild;
        root->sum = leftChild->sum + rightChild->sum;
        return root;
    }

    Node* update(Node* root, int left, int right, int index, int val) 
    {
        if (left > index || right < index) 
        {
            return root;
        }
        if (left == right) 
        {
            return new Node(val);
        }
        int mid = left + (right - left) / 2;
        Node* newRoot = new Node(0);
        newRoot->left = update(root->left, left, mid, index, val);
        newRoot->right = update(root->right, mid + 1, right, index, val);
        newRoot->sum = newRoot->left->sum + newRoot->right->sum;
        return newRoot;
    }

    int query(Node* root, int left, int right, int queryLeft, int queryRight) 
    {
        if (!root || queryLeft > right || queryRight < left) 
        {
            return 0;
        }
        if (queryLeft <= left && queryRight >= right) 
        {
            return root->sum;
        }
        int mid = left + (right - left) / 2;
        int leftSum = query(root->left, left, mid, queryLeft, queryRight);
        int rightSum = query(root->right, mid + 1, right, queryLeft, queryRight);
        return leftSum + rightSum;
    }

public:
    PersistentSegmentTree(const vector<int>& arr) 
    {
        versions.push_back(build(0, arr.size() - 1, arr));
    }

    void update(int version, int index, int val) 
    {
        versions.push_back(update(versions[version], 0, versions[0]->sum - 1, index, val));
    }

    int query(int version, int queryLeft, int queryRight) 
    {
        return query(versions[version], 0, versions[0]->sum - 1, queryLeft, queryRight);
    }
};
