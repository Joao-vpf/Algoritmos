//verifica se pode formar um palindromo
bool canFormPalindrome(string a)//O(n);
{
    int bitvector = 0, mask = 0;
    for (int i=0; a[i] != '\0'; i++)
    {
        int x = a[i] - 'a';
        mask = 1 << x;
 
        bitvector = bitvector ^ mask;
    }
 
    return (bitvector & (bitvector - 1)) == 0;
}
//forma um palindro se possivel
string getPalindrome(string str)//O(n)
{
 
    unordered_map<char, int> hmap;
    for (int i = 0; i < str.length(); i++)
        hmap[str[i]]++;
 
    int oddCount = 0;
    char oddChar;
    for (auto x : hmap) {
        if (x.second % 2 != 0) {
            oddCount++;
            oddChar = x.first;
        }
    }

    if (oddCount > 1
        || oddCount == 1 && str.length() % 2 == 0)
        return "impossible";
 
    string firstHalf = "", secondHalf = "";
    for (auto x : hmap) {
 
        string s(x.second / 2, x.first);
 
        firstHalf = firstHalf + s;
        secondHalf = s + secondHalf;
    }

    return (oddCount == 1)? (firstHalf + oddChar + secondHalf): (firstHalf + secondHalf);
}
