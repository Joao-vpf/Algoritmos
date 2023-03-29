bool isPalindrome(string s) 
{
    int n = s.length();
    int i = 0, j = n - 1;
    while (i < j) 
    {
        if (s[i] != s[j]) 
        {
            return false;
        }
        i++;
        j--;
    }
    return true;
}
