ullbool verif_palindrome(int x, int& aux) 
{ 
    if (x >= 0 && x < 10) 
        return (x == (aux) % 10); 
  
    if (!verif_palindrome(x / 10, aux)) 
        return false; 
  
    aux /= 10; 
  
    return (x % 10 == (aux) % 10); 
} 

int palindrome(int x) 
{ 
    if (x < 0) 
        x = -x; 

    int aux = x;  
  
    return verif_palindrome(x, aux); 
} 
