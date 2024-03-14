

class Solution {
public: 


	void comp(vector<vector<int>>& a, int& x, int& h)
	{   
        if(a.empty())
        {
            a.push_back({x, h});
            return;
        }
        
        if(a.back()[1] == h )
            return;

        if(a.back()[0] == x)
        {
            h = max(h, a.back()[1]);
            a.pop_back();
        }
        a.push_back({x, h});
            
	}

    vector<vector<int>> merge(vector<vector<int>>& l, vector<vector<int>>& r)
    {
        int n = l.size();
        int m = r.size();
        vector<vector<int>> aux;
        int i=0, j=0;
		int x, h1=INT_MIN, h2=INT_MIN;
        while(i<n and j<m)
        {
            int h=INT_MIN;
			if(l[i][0] < r[j][0])
			{
				x = l[i][0];
				h1 =l[i][1];
			    h=max(h1, h2);
				i++;
			}
			else
			{
                if(l[i][0] > r[j][0])
                {
                    x = r[j][0];
                    h2 =r[j][1];
                    h=max(h1, h2);
                    j++;
                }
                else
                {
                    x = r[j][0];
                    h1 = l[i][1];
                    h2 =r[j][1];
                    h=max(h1, h2);
                    i++,j++;
                }
			}
			comp(aux, x, h);
        }
        
		while(i<n)
		{
			int x, h=INT_MIN;
			x = l[i][0];
			h = l[i][1];
			i++;
			comp(aux, x, h);
		}

		while(j<m)
		{
			int x, h=INT_MIN;
			x = r[j][0];
			h =r[j][1];
		    j++;
			comp(aux, x, h);
		       
		}

/*
		for (auto e: aux)
		{
			for(auto u : e)
				cout << u << " ";
			cout << endl;
		}
	    cout<<endl;*/
        return aux;
    }

    vector<vector<int>> back(int l, int r, vector<vector<int>>& b)
    {
        if(l == r)
            return {{b[l][0],b[l][2]},{b[l][1],0}};

        int mid = (l+r)/2;
        vector<vector<int>> vecl = back(l, mid, b);
        vector<vector<int>> vecr = back(mid+1, r, b);
        return merge(vecl, vecr);
    }
    
    vector<vector<int>> getSkyline(vector<vector<int>>& b) 
    {
        return back(0, b.size()-1, b);
    }
};
