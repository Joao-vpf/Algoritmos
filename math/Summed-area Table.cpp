
   //"Prefix Sum" ou "Summed-area Table"
 for (int i = 0; i < n; i++) 
 {
      for (int j = 0; j < m; j++) 
      {
          cnt[i][j] = (a[i][j] == 'C');
          if (i > 0) cnt[i][j] += cnt[i-1][j];
          if (j > 0) cnt[i][j] += cnt[i][j-1];
          if (i > 0 && j > 0) cnt[i][j] -= cnt[i-1][j-1];
      }
  }


vector<vector<int>> create_summed_area_table(vector<vector<int>> &image) 
{
    int rows = image.size();
    int cols = image[0].size();
    // Inicializa a matriz com zeros
    vector<vector<int>> summed_area_table(rows, vector<int>(cols, 0));
    // Calcula a primeira linha e a primeira coluna
    summed_area_table[0][0] = image[0][0];
    for (int j = 1; j < cols; j++) 
    {
        summed_area_table[0][j] = summed_area_table[0][j - 1] + image[0][j];
    }
    for (int i = 1; i < rows; i++) 
    {
        summed_area_table[i][0] = summed_area_table[i - 1][0] + image[i][0];
    }
    // Calcula o restante da matriz
    for (int i = 1; i < rows; i++) 
    {
        for (int j = 1; j < cols; j++) 
        {
            summed_area_table[i][j] = image[i][j] + summed_area_table[i - 1][j] +
                                      summed_area_table[i][j - 1] - summed_area_table[i - 1][j - 1];
        }
    }
    return summed_area_table;
}

int get_sum(const vector<vector<int>> &summed_area_table, int x1, int y1, int x2, int y2) 
{
    // Obtem as somas acumuladas nas bordas da região retangular
    int top = (y1 > 0) ? summed_area_table[x2][y1 - 1] : 0;
    int left = (x1 > 0) ? summed_area_table[x1 - 1][y2] : 0;
    int topLeft = (x1 > 0 && y1 > 0) ? summed_area_table[x1 - 1][y1 - 1] : 0;
    // Calcula a soma total dentro da região retangular
    return summed_area_table[x2][y2] - top - left + topLeft;
}

int main() 
{
    vector<vector<int>> image = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    // Cria a tabela de soma acumulada
    vector<vector<int>> summed_area_table = create_summed_area_table(image);
    // Obtem a soma dos elementos na região retangular delimitada pelos pontos (1, 1) e (2, 2)
    int sum = get_sum(summed_area_table, 1, 1, 2, 2);
    cout << "Soma da regiao retangular: " << sum << endl;
    return 0;
}
