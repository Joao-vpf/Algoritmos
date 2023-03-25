struct TrieNode {
    vector<TrieNode*> children; 
    bool isEndOfWord; 
    int freq; 

    TrieNode() 
    {
        children = vector<TrieNode*>(26, nullptr); // Inicializa o vetor de filhos com 26 elementos, todos nulos
        isEndOfWord = false; // Define como falso, pois ainda não representa o fim de uma palavra
        freq = 0; // Define a frequência como 0
    }

    ~TrieNode() 
    {
        for (int i = 0; i < 26; i++) 
        {
            delete children[i]; 
        }
    }
};


class Trie 
{
    private:
        TrieNode* root;

    void findWordsWithSubstringRecursive(TrieNode* node, string prefix, vector<string>& results, string x) 
    {//percorre todos os nodes e salva no results palavras que contem x
        if (node->isEndOfWord) 
        {
            if(prefix.find(x)!=string::npos)
            { 
                results.push_back(prefix);
            }
        }
        for (int i = 0; i < 26; i++) 
        {
            if (node->children[i] != nullptr) 
            {
                char c = 'a' + i;
                findWordsWithSubstringRecursive(node->children[i], prefix+c,  results, x) ;
            }
        }
    }
    
    bool removeRecursive(TrieNode* node, string word, int pos) 
    {
        if (pos == word.size()) 
        { // Verifica se chegou ao fim da palavra
            if (!node->isEndOfWord) 
            {// A palavra não está na Trie
                return false; 
            }
            node->isEndOfWord = false; 
            node->freq--; 
            return true;
        }
        int index = word[pos] - 'a';
        if (node->children[index] == nullptr) 
        { // Se o filho não existe a palavra não está na Trie
            return false;
        }
        bool shouldDelete = removeRecursive(node->children[index], word, pos + 1); // Verifica se o filho deve ser deletado
        if (shouldDelete) {
            delete node->children[index]; 
            node->children[index] = nullptr; 
            node->freq--; 
            
            if (node->freq == 0 && !node->isEndOfWord) 
            {// Verifica se o nó atual pode ser removido (não tem mais filhos e não representa o fim de uma palavra)
                delete node;
                return true; 
            }
        }
        return false;
    }

    public:
        
    Trie() 
    {
        root = new TrieNode();
    }

    ~Trie() 
    {
        delete root; 
    }

    void insert(string word) 
    {
        TrieNode* node = root;
        for (char c : word) 
        { // Percorre cada caracter da palavra
            int index = c - 'a';
            if (node->children[index] == nullptr) 
            { // Se o filho ainda não existe
                node->children[index] = new TrieNode();
            }
            node = node->children[index]; // Vai para o próximo nó (filho)
        }
        node->isEndOfWord = true; // Define o último nó como o fim de uma palavra
        node->freq++; // Incrementa a frequência da palavra
    }

    bool search(string word) 
    {
        TrieNode* node = root; 
        for (char c : word) 
        { // Percorre cada caracter da palavra
            int index = c - 'a'; 
            if (node->children[index] == nullptr) 
            { // Se o filho não existe
                return false;
            }
            node = node->children[index]; // Vai para o próximo nó (filho)
        }
        return node->isEndOfWord; // Retorna se o último nó representa o fim de uma palavra
    }

    bool remove(string word) 
    {
        return removeRecursive(root, word, 0);
    }

    bool update(string antes, string agora) 
    {
        if (search(antes)) 
        { // Verifica se a palavra antiga está na Trie
            remove(antes); 
            insert(agora); 
            return true; 
        }
        return false;
    }

   void findSubstring(string x, vector<string>& results) 
    {//metodo para procurar na trie (todas os nodes) se tem x contido em alguma palavra
        findWordsWithSubstringRecursive(root,"" ,results, x);
    }
};

