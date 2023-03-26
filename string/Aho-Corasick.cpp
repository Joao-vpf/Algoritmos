// Estrutura de um nó da trie
struct Node {
    int parent; // Índice do nó pai
    char parentChar; // Caractere que conecta ao pai
    bool isEnd; // Indica se é fim de uma palavra
    int endID; // Índice da palavra que termina no nó, -1 se não houver
    int link; // Índice do nó de falha
    map<char, int> children; // Mapeamento de caractere para índice do filho
    vector<int> matchedIDs; // Índices das palavras que são sufixos da string que termina no nó
};

// Constrói a trie a partir do vetor de palavras
vector<Node> buildTrie(const vector<string>& words) {
    vector<Node> trie;
    trie.push_back({-1, '\0', false, -1, -1, {}, {}});
    int nextID = 1;
    for (int i = 0; i < words.size(); i++) {
        int nodeID = 0;
        for (char c : words[i]) {
            if (!trie[nodeID].children.count(c)) {
                trie.push_back({nodeID, c, false, -1, -1, -1, {}, {}});
                trie[nodeID].children[c] = nextID++;
            }
            nodeID = trie[nodeID].children[c];
        }
        trie[nodeID].isEnd = true;
        trie[nodeID].endID = i;
    }
    return trie;
}

// Constrói a função de falha
void buildFailureFunction(vector<Node>& trie) {
    queue<int> q;
    q.push(0);
    while (!q.empty()) {
        int nodeID = q.front();
        q.pop();
        for (auto it : trie[nodeID].children) {
            char c = it.first;
            int childID = it.second;
            int failID = trie[nodeID].link;
            while (failID != -1 && !trie[failID].children.count(c)) {
                failID = trie[failID].link;
            }
            if (failID != -1) {
                failID = trie[failID].children[c];
            }
            trie[childID].link = failID;
            trie[childID].matchedIDs = trie[failID].matchedIDs;
            if (trie[childID].isEnd) {
                trie[childID].matchedIDs.push_back(trie[childID].endID);
            }
            q.push(childID);
        }
    }
}

// Executa a busca de padrões na string s usando a trie
vector<vector<int>> search(const vector<Node>& trie, const string& s) {
    vector<vector<int>> matches(trie.size());
    int nodeID = 0;
    for (int i = 0; i < s.size(); i++) {
        while (nodeID != -1 && !trie[nodeID].children.count(s[i])) {
            nodeID = trie[nodeID].link;
        }
        if (nodeID != -1) {
            nodeID = trie[nodeID].children[s[i]];
        }
        for (int id : trie[nodeID].matchedIDs) {
            matches[id].push_back(i);
        }
    }
    return matches;
}

