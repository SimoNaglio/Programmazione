#include <iostream>

int is_prime (int n) 
{
    int contatore = 0;
    int i = 2;
    while (i < n) 
    {
        int r = n % i;
        if ( r != 0) 
        {
            i++;
        } else 
        {
           contatore = 1;
           break;
        } 
    }
    return contatore;
}

int main() 
{
    int n;
    std::cout << "Scrivere un numero intero:  ";
    std::cin >> n; 
    int num = is_prime (n);
    
    if (num == 1) 
    {
        std::cout << "Il numero non è primo" << '\n';
    } else
    {
        std::cout << "Il numero " << n <<" è primo" <<'\n';
    }
    
}