const int BASE = 31;
const int MOD = 1e9 + 7;

vector<int> computePowers(int n) 
{
    vector<int> powers(n);
    powers[0] = 1;
    for (int i = 1; i < n; i++)
        powers[i] = (powers[i - 1] * 1LL * BASE) % MOD;
    return powers;
}

vector<int> computeHashes(const string& s) 
{
    int n = s.length();
    vector<int> hashes(n + 1);
    for (int i = 0; i < n; i++)
        hashes[i + 1] = (hashes[i] * 1LL * BASE + s[i] - 'a' + 1) % MOD;//colocar vetor de pesos caso as letras tenham peso
    return hashes;
}

unordered_set<int> computeRollingHashes(const string& s, const vector<int>& powers, int len) 
{
    int n = s.length();
    unordered_set<int> hashes;
    int curr_hash = 0;
    for (int i = 0; i < len; i++)
        curr_hash = (curr_hash * 1LL * BASE + s[i] - 'a' + 1) % MOD;
    hashes.insert(curr_hash);
    for (int i = len; i < n; i++) {
        curr_hash = (curr_hash - (s[i - len] - 'a' + 1) * 1LL * powers[len - 1]) % MOD;
        curr_hash = (curr_hash * 1LL * BASE + s[i] - 'a' + 1) % MOD;
        curr_hash = (curr_hash + MOD) % MOD;
        hashes.insert(curr_hash);
    }
    return hashes;
}

int findCommonLength(const string& s1, const string& s2, int len) 
{
    int n1 = s1.length();
    int n2 = s2.length();

    vector<int> powers = computePowers(max(n1, n2) + 1);
    unordered_set<int> hashes1 = computeRollingHashes(s1, powers, len);
    unordered_set<int> hashes2 = computeRollingHashes(s2, powers, len);

    for (int hash1 : hashes1) {
        if (hashes2.count(hash1))// colocar o codigo da ultima linha nesse if
            return len;
    }

    return 0;
}

int LCS(const string& s1, const string& s2) 
{
    int n1 = s1.length();
    int n2 = s2.length();
    int left = 0;
    int right = min(n1, n2) + 1;

    while (left < right - 1) {
        int mid = (left + right) / 2;
        if (findCommonLength(s1, s2, mid))
            left = mid;
        else
            right = mid;
    }

    return left;
}

/*
string findCommonWord(const string& s1, const string& s2, int len) 
{
    int n1 = s1.length();
    int n2 = s2.length();

    vector<int> powers = computePowers(max(n1, n2) + 1);
    unordered_set<int> hashes1 = computeRollingHashes(s1, powers, len);
    unordered_set<int> hashes2 = computeRollingHashes(s2, powers, len);

    string commonWord="-1";
    for (int hash1 : hashes1) {
        if (hashes2.count(hash1)) 
        {
			commonWord.clear();
            int start1 = 0, start2 = 0;
            while (start1 + len <= n1 && start2 + len <= n2) 
            {
                if (s1.substr(start1, len) == s2.substr(start2, len)) 
                {
                    commonWord = s1.substr(start1, len);
                    break;
                }
                start1++;
                start2++;
            }
            break;
        }
    }

    return commonWord;
}//tem que mudar no BSTA do lcs para verificar caras que retornam -1 e ir para left=mid

*/
