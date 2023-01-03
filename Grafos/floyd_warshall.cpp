#define INF 99999
vector<vector<int>> dist(n,vector<int>(n, INF));
void fw(vector<vector<int>>& dist, int v)
{
	for(int k=0; k<v; k++)
	{
		for (int i=0; i<v; i++)
		{
			for(int j=0;j<v; j++)
			{
				if ( dist[i][k] != INF && dist[k][j] != INF && dist[i][k] + dist[k][j] < dist[i][j])
				{	
					dist[i][j] = dist[i][k] + dist[k][j];
				}
			}
		}
	}
}
