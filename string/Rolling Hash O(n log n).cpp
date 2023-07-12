const ll PRIME = 31;
const ll MOD = 1e9 + 9;

ll power(ll a, ll b, ll m) {
    ll res = 1;
    while (b > 0) {
        if (b & 1) {
            res = (res * a) % m;
        }
        a = (a * a) % m;
        b >>= 1;
    }
    return res;
}

ll calculateHash(const string& str) {
    ll hashValue = 0;
    ll p = 1;
    for (char c : str) {
        hashValue = (hashValue + (c - 'a' + 1) * p) % MOD;
        p = (p * PRIME) % MOD;
    }
    return hashValue;
}

vector<int> getRollingHashes(const string& text, int patternLength) {
    int n = text.length();
    vector<int> hashes(n - patternLength + 1);

    ll currHash = calculateHash(text.substr(n - patternLength, patternLength));
    hashes[n - patternLength] = currHash;

    ll powerValue = power(PRIME, patternLength - 1, MOD);

    for (int i = n - patternLength - 1; i >= 0; i--) {
        currHash = (currHash - (text[i + patternLength] - 'a' + 1) * powerValue) % MOD;
        currHash = (currHash * PRIME) % MOD;
        currHash = (currHash + (text[i] - 'a' + 1) + MOD) % MOD;
        hashes[i] = currHash;
    }

    return hashes;
}

int longestCommonSubsequence(const string& text1, const string& text2) {
    int m = text1.length();
    int n = text2.length();
    
    // Gerar Rolling Hashes dos dois textos
    vector<int> hashes1 = getRollingHashes(text1, m);
    vector<int> hashes2 = getRollingHashes(text2, n);

    // Converter hashes2 em um conjunto para verificação rápida de colisões
    unordered_set<int> hashSet(hashes2.begin(), hashes2.end());

    int maxLength = 0;

    // Verificar colisões dos hashes1 com os hashes2
    for (int i = 0; i < hashes1.size(); i++) {
        if (hashSet.find(hashes1[i]) != hashSet.end()) {
            // Encontrado um possível match
            int length = 0;
            int idx1 = i;
            int idx2 = 0;

            // Expandir o match
            while (idx1 < m && idx2 < n) {
                if (text1[idx1] == text2[idx2]) {
                    length++;
                    idx1++;
                    idx2++;
                } else {
                    break;
                }
            }

            maxLength = max(maxLength, length);
        }
    }

    return maxLength;
}
