#include <iostream>

double pow(double base, int esp) // metto double
{
  double ris = 1;
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

double radical(double numero)
{
    double rad = 1.;
    double ris = 0.;
    double test = 0.;
    double memory = 0.;
    double a = 0;
    double b = 0;
    double exp = -1;
    
    while (b < 100000)  //aumentare il numero di "0" per maggiori decimali
    {
        while (rad <= numero)
        {
            memory = test; 
            test = a/b + ris; 
            rad = pow(test,2); //aumentare la potenza di test per radici di indice maggiore
            a++;
        }
        ris = memory;
        test = memory; 
        exp++;
        b = pow(10,exp);
        rad = 1.;
        a = 0.;
    }
    return ris;
}

int main ()
{
    std::cout << "\n\tImmetti un numero: ";
   double num;
   std::cin>>num; 
   double value = radical(num);
   std::cout<<"\n\tLa radice di " << num <<" vale: " <<value <<'\n';
}

   