//Algoritmo para procurar um determinado substring na string normal
//search(string normal, substring);
# define NO_OF_CHARS 256
// The preprocessing function for Boyer Moore's
// bad character heuristic
void badCharHeuristic( string str, int size,
                        int badchar[NO_OF_CHARS])
{
    int i;
 
    // Initialize all occurrences as -1
    for (i = 0; i < NO_OF_CHARS; i++)
        badchar[i] = -1;
 
    // Fill the actual value of last occurrence
    // of a character
    for (i = 0; i < size; i++)
        badchar[(int) str[i]] = i;
}
 
/* Uma função de busca de padrões que usa Bad
Caracter Heurístico do Algoritmo Boyer Moore */
void search( string txt, string pat)
{
    int m = pat.size();
    int n = txt.size();
 
    int badchar[NO_OF_CHARS];
 
    /* Fill the bad character array by calling
    the preprocessing function badCharHeuristic()
    for given pattern */
    badCharHeuristic(pat, m, badchar);
 
    int s = 0; // s é mudança do padrão em relação ao texto
    while(s <= (n - m))
    {
        int j = m - 1;

        while(j >= 0 && pat[j] == txt[s + j])
        {

            j--;
        }
        /* Continue reduzindo o índice j de padrão enquanto
        Os caracteres de padrão e texto são
        correspondência neste turno s */
        if (j < 0)
        {
            
            cout << s << endl;//resultado
            /* Mude o padrão para que o próximo
            caracteres em texto se alinham com o último
            ocorrência do mesmo em padrão.
            A condição s+m < n é necessária para
            o caso quando o padrão ocorre no final
            de texto */
            s += (s + m < n)? m-badchar[txt[s + m]] : 1;
 
        }
        else
        {
            /* Mude o padrão de forma que o mau caráter
            em texto alinha-se com a última ocorrência de
            em padrão. A função máxima é usada para
            garantir que tenhamos uma mudança positiva.
            Podemos ter um turno negativo se o último
            ocorrência de mau caracter no padrão
            está no lado direito da corrente
            caracter. */
            s += max(1, j - badchar[txt[s + j]]);
        }
    }
}
