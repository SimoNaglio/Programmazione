//(ti commento questo codice alle 2:23 dopo due ore di bestemmie sul runtime error "bad_alloc" che hanno portato alla soluzione di un cazzo di niente.
//detto ciò spero di non essere troppo confusionario, enjoy;) rivolto al dott. Pintus

//dott. Pintus, abbiamo le fratte


//il codice è strutturato da tre classi: Point (molto comoda per l'interfaccia grafica), FofX (cioè f di x, è la classe delle funzioni polinomiali)
//e da Fract (la classe delle funzioniu polinomiali, al momento non utilizzabile ma non per un problema suo), varie freefunction ed il main;

// PER IL MOMENTO STAMPA SOLO LE POLINOMIALI, SI SPERA A BREVE DI AGGIUNGERE LE GONIOMETRICHE;

#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include <limits>

class Point {
  double x_;
  double y_;  // i valori x e y del punto;
 public:
  Point(double a, double b) : x_{a}, y_{b} {}  // costruttori;
  Point() : x_{0}, y_{0} {}
  double get_x() const { return x_; }
  double get_y() const {
    return y_;
  }  // metodi get, interfaccia pubblica (i metodi sono const altrimenti quando
     // li richiamo passandogli delle const reference...
};  //... il compilatore teme che io possa modificarli) alcuni commenti non sono strettamente indirizzati a lei, dottor Pinto;

class FofX {  //classe delle funzioni
  std::vector<double> coeff; //i coefficenti li salvo in un vettore, l'idea è: f(x)= a + bx + cx^2 + dx^3 ... dove a,b,c,d sono gli elementi di indice 0,1,2,4;
  int wfunc;  //Whichfunc al momento è una variabile totalmente inutile, ma credo possa tornare utile in futuro per distringuere il tipo di funzione;

 public:
  FofX(const std::vector<double>& v) : coeff{v}, wfunc{0} {} //costruttore che vuole in input un vettore di coefficenti;

  double calc(double x) {
    double result;
      for(int i{0}; i < coeff.size(); ++i){  //metodo bellino, ti calcola f(x) in base ai coefficenti salvati nel vettore per una x passata
      result += std::pow(x,i)*coeff[i];      //l'idea è che ogni termine della polinomiale è il prodotto tra una potenza di x e di un coefficente;
    }
    return result;
  }
  auto const get_coeff(){ //metodo get che torna utile in seguito
    return coeff;
  }
};

class Fract{ //classe delle fratte, idea molto basic di rappresentare una fratta come h(x)=f(x)/g(x) dove f e g sono polinomiali normali;
  FofX num;
  FofX den;   //sarebbe carino saper implementare l'ereditarietà delle classi, tipo Fract sottoclasse di FofX, ma non ne sono in grado T-T;
  public:
  Fract(const FofX& n, const FofX& d) : num{n}, den{d} {} //costruttore che vuole due funzioni polinomiali;

  double rndt1(double a) {    //funzione bellina che arrotonda un numero alla prima cifra decimale moltiplicando per 10, troncando le cifre decimali e poi ridividendo per 10
   return std::ceil(a * 10.0) / 10.0;
  }
  
  double calc(double x){
    //return rndt1((num.calc(x)/den.calc(x)));        //non so perchè, il metodo precedente basato sul richiamare il calc() delle polinomiali che costituiscono la...
    double r_num;                                     //...fratta non funziona bene, anzi, è abbastanza randomico. Lo lascio comunque commentato qualcuno lo...
    double r_den;                                     //...volesse debuggare;

    for(int i{0}; i< num.get_coeff().size(); ++i){ 
      r_num += std::pow(x,i)*num.get_coeff()[i];      
    }                                                 
    for(int i{0}; i< den.get_coeff().size(); ++i){
      r_den += std::pow(x,i)*den.get_coeff()[i];
    }
    return r_num/r_den;
  }
};

bool operator==(const Point& a, const Point& b) { // operatore == per i Point;
  return a.get_x() == b.get_x() &&
         a.get_y() == b.get_y();  
}

bool operator!=(const Point& a, const Point& b) { // operatore != per i Point;
  return a.get_x() != b.get_x() ||
         a.get_y() != b.get_y();
}

bool condition(Point p, FofX f) {   //allora questa è un po stoppacciosa, ma di base returna vero se il punto passato è approssimabilmente vicino al valore...
  return rndt1(p.get_y()) == rndt1(f.calc(p.get_x())) && ((rndt1(p.get_x()) >= 0.1 ||rndt1(p.get_x()) <= -0.1) && (rndt1(p.get_y()) >= 0.1 || rndt1(p.get_y()) <= -0.1));
}//... della funzione in quel x e contemporaneamente il punto non è approssimabilmente vicino agli assi cartesiani (questo serve per printare gli assi correttamente);

bool condition(Point p, Fract h) {  //idem con la fratta, nota che mettere lo stesso nome permette un overload molto ghiotto;
  return rndt1(p.get_y()) == rndt1(h.calc(p.get_x())) && ((rndt1(p.get_x()) >= 0.1 ||rndt1(p.get_x()) <= -0.1) && (rndt1(p.get_y()) >= 0.1 || rndt1(p.get_y()) <= -0.1));
}

auto to_symbol(bool k, const Point& p) {  //la solita funzione trafugata da Jack e riadattata, in questo caso printa un asterisco se il punto appartiene alla funzione...
  if(k){
    return (rndt1(p.get_x()) >= 0.1 || rndt1(p.get_x()) <= -0.1) && (rndt1(p.get_y()) >= 0.1 || rndt1(p.get_y()) <= -0.1) ? '*' : '.';
  } //... e contemporaneamente non è in prossimità degli assi, altrimenti se il punto sta in prossimità degli assi printa il punto;
  if(!k){ //se il punto non appartiene alla funzione e non sta in prossimtà degli assi printa lo spazio vuoto, altrimenti se sta vicino gli assi il punto;
    return ((rndt1(p.get_x()) >= 0.1 || rndt1(p.get_x()) <= -0.1) && (rndt1(p.get_y()) >= 0.1 || rndt1(p.get_y()) <= -0.1)) ? ' ' : '.';
  }
  return '@'; //messo per evitare un warning, assolutamente random e puzzone;
  }

auto richiedi_pol(){  //funzione che ti returna un vettore di coefficenti double tramite un ciclo while che va finche non premi ctrl C;
  std::vector<double> vect; //inizialmente gli passavo by reference un vettore dichiarato nel main, ma CREDO sia più efficente cosi;
  std::cout << "Inserisci i parametri della funzione polinomiale in ordine crescente di esponente (da quello di x^0 in poi), inserisci 's' per convalidare: " << '\n';
  while (true)    //metto il while sempre vero e poi me lo gestisco con continue e break
  {
    double a;
    if(std::cin >> a){      //se la lettura è di tipo double, allora entra nell'if...
      std::cin.sync();      //non so cosa faccia ma senza non funzia
      vect.push_back(a);
      continue;
  }
    else  {                 //...altrimenti no e rompi il loop
      std::cin.clear();     //pulisci il buffer del cin (sono 3 righe mistiche trafugate dall'internet, so cosa facciano giusto a recchia)
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cin.sync();
      break;
    }
  }
  return vect;
}

int main() {
  // FofX f{richiedi_pol()};
  // FofX g{richiedi_pol()};
  // Fract h{f,g};

  double const display_width = 52; //aumentando stai zoommando, l'idea è che se aumenti questo aumenti la risoluzione, però devi anche ridurre...
  double const display_height = 40; //max_x, min_x, max_y e min_y altrimenti non ti entra sullo schermo. Il concetto è che display_width e height rappresentano...
  double max_x{13}; //...letteralmente il numero di pixel, mentre max e min di x e y quanto zoommi e quindi quando schermo usi, le impostazioni che ho messo...
  double min_x{-13};//... sono piuttosto sicuro siano ottimali, sono tarate su un ottima precisione e sul centrare gli assi;
  double max_y{10};
  double min_y{-10};
  double delta_y{(max_y - min_y) / (4*display_height)};   //setto lo step tra un punto ed un altro, se te lo stai chiedendo avrei benissimo aver messo 208 pixel...
  double delta_x{(max_x - min_x) / (4*display_width)};  //... in altezza e 160 in larghezza anzi che moltiplicare per 4 i valori attuali, ma sono stronzo;
  
  std::cout << '\n' <<"Ti consiglio vivamente di mettere a schermo intero, inoltre probabilmente dovrai scorrere in su per vedere la funzione" << '\n' << '\n' << '\n';
  std::cout << "A seconda di cosa vorresti disegnare inserisci: p(Polinomiale), f(Polinomiale fratta)" << '\n';
  char scelta;
  std::cin >> scelta;
  if(scelta == 'p'){
    FofX f{richiedi_pol()};       //inizializzo la polinomiale

    for (double i{max_y}; i >= min_y; i -= delta_y) {         //solito doppio for per stampare
      std::string line;
      for (double j{min_x}; j <= max_x; j += delta_x) {
        Point p{j, i};
        line.push_back(to_symbol(condition(p, f),p));
        }
      std::cout << line << '\n';
    }
  }
  else if(scelta == 'f'){
    std::cout << "POLINOMIALE AL NUMERATORE: " << '\n';   
    FofX f{richiedi_pol()};                                   //inizializza num e denominatore della fratta
    std::cout << "POLINOMIALE AL DENOMINATORE: " << '\n';
    FofX g{richiedi_pol()};
    Fract h{f,g};

    for (double i{max_y}; i >= min_y; i -= delta_y) {         //solito doppio for per stampare
      std::string line;
      for (double j{min_x}; j <= max_x; j += delta_x) {
        Point p{j, i};
        line.push_back(to_symbol(condition(p, h),p));        
        }
      std::cout << line << '\n';
    }
  }
   else{
     std::cout << "input non riconosciuto, gestione dell'errore coming soon" << '\n';
   }
}
//maruann
