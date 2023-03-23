bool isPalindromo(string str, int start, int end) // chamar a função com os índices iniciais e finais da string
{
  if (start >= end) 
  {
    return true; // a string está vazia ou tem apenas um caractere, é um palíndromo
  }
  else 
  {
    if (str[start] != str[end]) 
    {
      return false; // os caracteres nas extremidades são diferentes, não é um palíndromo
    }
    else 
    {
      return isPalindromo(str, start+1, end-1); // verificar o restante da string
    }
  } 
}

