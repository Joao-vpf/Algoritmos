bool formpalindrome(string s) 
{
    int freq[26];
    memset(freq, 0, sizeof(freq));

    for (char c : s)
    {
        freq[c-'a']++;
    }

    int oddCount = 0;
    for (int i = 0; i < 26; i++)
    {
        if (freq[i] % 2 == 1)
        {
            oddCount++;
        }
        if (oddCount > 1)
        {
            return false;
        }
    }

    return true;
}
