string removestring(string str, char c) 
{
    string newStr;
    for (char ch : str) 
    {
        if (ch != c) 
        {
            newStr += ch;
        }
    }
    return newStr;
}
