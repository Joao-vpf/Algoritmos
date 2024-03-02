bool verif_palindrome(int num, int& dupNum) 
{ 
    if (num >= 0 && num < 10) 
        return (num == (*dupNum) % 10); 
  
    if (!verif_palindrome(num / 10, dupNum)) 
        return false; 
  
    dupNum /= 10; 
  
    return (num % 10 == (dupNum) % 10); 
} 

int palindrome(int num) 
{ 
    if (num < 0) 
        num = -num; 

    int dupNum = num;  
  
    return verif_palindrome(num, dupNum); 
} 
