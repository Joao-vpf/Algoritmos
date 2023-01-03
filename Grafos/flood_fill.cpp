void fldl(int i, int j) //dfs "multidimensional" recursiva
{
	mat[i][j]='T';
	if (i>0 && mat[i-1][j]=='A') 
	{
		fldl(i-1,j);
	}
	if (i<n-1 && mat[i+1][j]=='A') 
	{
		fldl(i+1,j);
	}
	if (j>0 && mat[i][j-1]=='A') 
	{
		fldl(i,j-1);
	}
	if (j<m-1 && mat[i][j+1]=='A') 
	{
		fldl(i,j+1);
	}
}

//completo
void flfd(int x, int y,int m, int n) //inicio da procura, tamanho vertical, tamanho horizontal
{
	vis[x][y]=1;
	//normal
	if (y>0 && vis[x][y-1]==0 && mat[x][y-1]==1)
	{
		flfd(x, y-1,m,n);
	}
	if (x<m-1 && vis[x+1][y]==0 && mat[x+1][y]==1)
	{
		flfd(x+1, y,m,n);
	}
	if (x>0 && vis[x-1][y]==0 && mat[x-1][y]==1)
	{
		flfd(x-1, y,m,n);
	}
	if (y<n-1 && vis[x][y+1]==0 && mat[x][y+1]==1)
	{
		flfd(x, y+1,m,n);
	}
	//diagonais
	if (x<m-1 && y<n-1 && vis[x+1][y+1]==0 && mat[x+1][y+1]==1)
	{
		flfd(x+1, y+1,m,n);
	}
	if (x>0 && y>0 && vis[x-1][y-1]==0 && mat[x-1][y-1]==1)
	{
		flfd(x-1, y-1,m,n);
	}
	if (x>0 && y<n-1 && vis[x-1][y+1]==0 && mat[x-1][y+1]==1)
	{
		flfd(x-1, y+1,m,n);
	}
	if (x<m-1 && y>0 && vis[x+1][y-1]==0 && mat[x+1][y-1]==1)
	{
		flfd(x+1, y-1,m,n);
	}
}

//FLOOD FILL / BFS
int dx[8]={1,0,-1,0, -1, 1, -1, 1};
int dy[8]={0,1,0,-1,-1, 1,1,-1};
int fdfl(int i, int j) //bfs flood fill
{
    dist[i][j]=0;
    queue <p> q;
    q.push(make_pair(i,j));
    while (q.size())
    {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();
        for (int l=0; l<8; l++)
        {
            int h = x+dx[l];
            int w = y+dy[l];
            if(w>0 && w<9 && h>0 && h<9 && dist[h][w]==-1)
            {
                dist[h][w]=dist[x][y]+1;
                q.push({h,w});
            }
        }
    }
    return dist[b1][b2];
}
