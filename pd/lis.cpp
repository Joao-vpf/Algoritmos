int lis(vector <int>& v)
{
    if(v.size()==0)
    {
        return 0;
    }

    vector<int> tail(v.size(), 0);
    tail[0]=v[0];
    int length=1;
    for(size_t i = 0; i<v.size(); i++)
    { 
        auto b = tail.begin(), e = tail.begin() + length;
        auto it = lower_bound(b, e, v[i]);
 
        if (it == tail.begin() + length)
        {
            tail[length++] = v[i];
        }
        else
        {
            *it = v[i];
        }
    }
    return length;
}
