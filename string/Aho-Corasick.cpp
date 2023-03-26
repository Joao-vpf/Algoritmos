// Estrutura de um nó da trie
struct Node 
{
    int parent; // Índice do nó pai
    char parentChar; // Caractere que conecta ao pai
    bool isEnd; // Indica se é fim de uma palavra
    int endID; // Índice da palavra que termina no nó, -1 se não houver
    int link; // Índice do nó de falha
    map<char, int> children; // Mapeamento de caractere para índice do filho
    vector<int> matchedIDs; // Índices das palavras que são sufixos da string que termina no nó
    Node(int x, char y, bool b, int id, int lin)
    {
        parent = x;
        parentChar=y;
        isEnd=b;
        endID=id;
        link=lin;
    }
    Node() : parent(-1), parentChar('\0'), isEnd(false), endID(-1), link(0) {}
    ~Node() {}
};

class AhoCorasick
{/*Tamanho constante K, então a complexidade da Trie é O(NK), onde N é o número total de palavras armazenadas na Trie.*/
    vector<Node*> trie;
    // Constrói a função de falha
    void buildFailureFunction() 
    {//O(N * L), onde N é o número de palavras no dicionário e L é o comprimento da maior palavra.
        queue<int> q;
        q.push(0);//posição do root no vetor
        while (!q.empty()) 
        {
            int nodeID = q.front();
            q.pop();
            for (auto it : trie[nodeID]->children) 
            {
                char c = it.first;
                int childID = it.second;
                int failID = trie[nodeID]->link;
                while (failID != 0 && !trie[failID]->children.count(c)) 
                {
                    failID = trie[failID]->link;
                }
                if (trie[failID]->children.count(c)) 
                {
                    failID = trie[failID]->children[c];
                }
                else
                {
                    failID=0;
                }
                trie[childID]->link = failID;
                if (failID >= 0) 
                {
                    trie[childID]->matchedIDs = trie[failID]->matchedIDs;
                } 
                else 
                {
                    trie[childID]->matchedIDs.clear();
                }
                if (trie[childID]->isEnd) 
                {
                    trie[childID]->matchedIDs.push_back(trie[childID]->endID);
                }
                q.push(childID);
            }
        }
    }


    public:
    
    vector<string> words;// nao pode mudar
    // Constrói a trie a partir do vetor de palavras
   void buildTrie(vector<string>& a)
    {//O(N * L), onde N é o número de palavras no dicionário e L é o comprimento da maior palavra.
        words=a;
        trie.push_back(new Node);
        int nextID = 1;
        int size= words.size();
        for (int i = 0; i <size; i++)
        {
            int nodeID = 0;
            for (char c : words[i])
            {
                if (!trie[nodeID]->children.count(c))
                {//verifica se tem a letra naquele nodeid
                    trie.push_back(new Node(nodeID, c, false, -1, 0));//cria um novo node naquele nodeid inserindo a letra que nao existia
                    trie[nodeID]->children[c] = nextID++;//salva a posição do filho
                }
                //se tiver vai para o proximo node que esta na salvo no filho daquela letra 
                nodeID = trie[nodeID]->children[c];
            }
            trie[nodeID]->isEnd = true;
            trie[nodeID]->endID = i;
        }
        buildFailureFunction();
    }
    
  
    // Adiciona uma nova palavra à trie
    void insert(const string& word) 
    {
        int nodeID = 0;
        for (char c : word) 
        {
            if (!trie[nodeID]->children.count(c))
            {
                trie[nodeID]->children[c] = trie.size();
                trie.push_back(new Node(nodeID, c, false, -1, 0));
            }
            nodeID = trie[nodeID]->children[c];
        }
        trie[nodeID]->isEnd = true;
        trie[nodeID]->endID = trie.size() - 1;
        buildFailureFunction();
    }

    // Atualiza uma palavra existente na trie
    void update(int wordIndex, const string& newWord)
    {
        int nodeID = 0;
        for (char c : newWord) 
        {
            if (!trie[nodeID]->children.count(c))
            {
                trie[nodeID]->children[c] = trie.size();
                trie.push_back(new Node(nodeID, c, false, -1, 0));
            }
            nodeID = trie[nodeID]->children[c];
        }
        trie[nodeID]->isEnd = true;
        trie[nodeID]->endID = wordIndex;
        buildFailureFunction();
    }

    // Remove uma palavra da trie
    void remove(const string& word) 
    {
        int nodeID = 0;
        for (char c : word) 
        {
            if (!trie[nodeID]->children.count(c)) 
            {
                // A palavra não existe na trie
                return;
            }
            nodeID = trie[nodeID]->children[c];
        }
        // Se o nó final não é uma folha, simplesmente desmarcamos a flag isEnd
        if (!trie[nodeID]->isEnd) 
        {
            return;
        }
        trie[nodeID]->isEnd = false;
        // Percorre a árvore a partir do nó removido, removendo nós desnecessários
        while (nodeID > 0 && trie[nodeID]->children.empty() && !trie[nodeID]->isEnd)
        {
            int parentID = trie[nodeID]->parent;
            char parentChar = trie[nodeID]->parentChar;
            trie[parentID]->children.erase(parentChar);
            delete trie[nodeID];
            trie[nodeID] = nullptr;
            nodeID = parentID;
        }
    }

    // Busca por uma palavra na trie
    bool search(const string& word) 
    {// O(m), onde m é o comprimento da palavra sendo buscada.
        int nodeID = 0;
        for (char c : word) 
        {
            if (!trie[nodeID]->children.count(c)) 
            {
                // A palavra não existe na trie
                return false;
            }
            nodeID = trie[nodeID]->children[c];
        }
        return trie[nodeID]->isEnd;
    }

    // Busca pela primeira ocorrência de uma palavra da trie em um texto
    pair<int, int> findFirst(const string& text)
    {//pair<qual palavra do dicionario, onde terminou>
    //O(n), onde n é o comprimento do texto em que a palavra está sendo buscada
        int nodeID = 0;
        int size = text.size();
        for (int i = 0; i < size; i++) 
        {
            while (nodeID != 0 && !trie[nodeID]->children.count(text[i])) 
            {
                nodeID = trie[nodeID]->link;
            }
            if (trie[nodeID]->children.count(text[i])) 
            {
                nodeID = trie[nodeID]->children[text[i]];
            }
            if (trie[nodeID]->isEnd) 
            {
                return {i - words[trie[nodeID]->endID].length() + 1, trie[nodeID]->endID};
            }
        }
        return {-1, -1};
    }

};
