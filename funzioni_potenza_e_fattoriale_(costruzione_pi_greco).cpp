int pow(int base, int esp)
{
  int ris = 1;
  if (base == 0)
  {
      ris = 0;
      return ris;
  }
  for ( ; esp !=0 ; esp--)
  {
      ris *= base;
  }
  
  return ris;
}

int factorial(int n)
{
  int ris = 1;

  for ( ; n !=0 ; n--)
  {
      ris *= n;
  }  

  return ris;
}



int main() 
{
    double somma = 0;
    for (int k = 0 ; k<1 ; k++)
    { 
        long double num = factorial(4*k) * (1103 + 26390 * k);
        long double den = pow(factorial(k) , 4) * pow(396 , 4*k); 
        somma += num / den; 
    }


    double pi_1 = (2 * 1.4142)/9801 * somma; 
    double pi = 1 / pi_1;
    std::cout<<"\n\tIl numero vale: " << pi << std::endl;
}

