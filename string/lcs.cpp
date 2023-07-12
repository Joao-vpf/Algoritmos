int lcs(string a,string b)
{
  int n = a.size();
  int m = b.size();
	for(int i=1; i<=n; i++)
	{
		string r;
		for(int j=1;j<=m; j++)
		{
			if(a[i-1]==b[j-1])
			{
				dp[i][j] =dp[i-1][j-1]+vet[a[i-1]-'a']; 
			}
			else
			{ 
				dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
			}
		}
	}
}
