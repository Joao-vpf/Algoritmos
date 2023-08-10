struct Node 
{
    int value;
    Node* left;
    Node* right;

    Node(int val) : value(val), left(nullptr), right(nullptr) {}
};

class PersistentTree 
{
private:
    vector<Node*> versions;

    Node* insert(Node* root, int val) 
    {
        if (!root) 
        {
            return new Node(val);
        }
        if (val <= root->value) 
        {
            root->left = insert(root->left, val);
        } 
        else 
        {
            root->right = insert(root->right, val);
        }
        return root;
    }

    Node* updateRange(Node* root, int left, int right, int val) 
    {
        if (!root || right < root->value || left > root->value) 
        {
            return root;
        }

        Node* newRoot = new Node(root->value);
        if (left <= root->value && root->value <= right) 
        {
            newRoot->value += val;
            newRoot->left = updateRange(root->left, left, right, val);
            newRoot->right = updateRange(root->right, left, right, val);
        } 
        if (right < root->value) 
        {
            newRoot->left = updateRange(root->left, left, right, val);
            newRoot->right = root->right;
        } 
        if (left > root->value) 
        {
            newRoot->left = root->left;
            newRoot->right = updateRange(root->right, left, right, val);
        }
        return newRoot;
    }

public:
    PersistentTree() 
    {
        versions.push_back(nullptr); 
    }

    void insert(int val) 
    {
        versions.push_back(insert(versions.back(), val));
    }

    void updateRange(int version, int left, int right, int val) 
    {
        versions.push_back(updateRange(versions[version], left, right, val));
    }

    int query(Node* root, int val) 
    {
        if (!root) 
        {
            return 0;
        }
        if (val == root->value) 
        {
            return root->value;
        } 
        if (val < root->value) 
        {
            return query(root->left, val);
        } 
        return query(root->right, val);
    }

    int query(int version, int val)
     {
        return query(versions[version], val);
    }
};
