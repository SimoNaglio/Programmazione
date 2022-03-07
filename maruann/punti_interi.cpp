/*Soluzione ad un problema del libro di Lore: "prendi in input le coordinate dei vertici di un triangolo e dimmi quanti sono i punti di coordinate intere 
contenuto nella sua area.
La soluzione probabilmente è un overkill, ma sostanzialmente prende in input le coordinate dei 3 vertici, le smista in modo da poterci trovare le espressioni
delle 3 rette passanti per i 3 punti e poi tramite un sistema di 3 disequazioni delimita l'area del triangolo nel piano (due maggiorazioni ed una minorazione
nel caso del triangolo con la punta verso l'alto, due minorazioni ed una maggiorazione nel caso contrario).
Fatto ciò nel main ci sono due cicli for concatenati che scorrono le x e le y intere andando a salti di 1 e salvando in un vettore i punti che soddisfano le disequazioni."*/



#include <iostream>
#include <vector>

class Point{
    double x_;
    double y_;  //i valori x e y del punto
  public :
    Point(double a, double b)
        : x_{a}, y_{b} {}       //costruttori 
    Point()             
        : x_{0},y_{0} {}
    double get_x() const {return x_;}
    double get_y() const {return y_;}  //metodi get, interfaccia pubblica (i metodi sono const altrimenti quando li richiamo passandogli delle const reference...
};                                                                      //... il compilatore teme che io possa modificarli)

bool operator==(const Point& a, const Point& b){
    return a.get_x() == b.get_x() && a.get_y() == b.get_y();    //operatore == per i Point
}

bool operator!=(const Point& a, const Point& b){
    return a.get_x() != b.get_x() || a.get_y() != b.get_y(); //operatore != per i Point
}

Point max_x(const Point& a, const Point& b, const Point& c){ //ritorna il punto con x maggiore dati 3 punti come argomento
    if (a.get_x() > b.get_x()){
        if(a.get_x() > c.get_x()){
            return a;
            }
        else return c;
    }
    else{
        if(b.get_x() > c.get_x()){
            return b;
        }
        else return c;
    }
}

Point min_x(const Point& a, const Point& b, const Point& c){ //ritorna il punto di x minore dati 3 punti come argomento
    if (a.get_x() < b.get_x()){
        if(a.get_x() < c.get_x()){
            return a;
            }
        else return c;
    }
    else{
        if(b.get_x() < c.get_x()){
            return b;
        }
        else return c;
    }
}

Point max_y(const Point& a, const Point& b, const Point& c){ //ritorna il punto di y maggiore dati 3 punti come argomento
    if (a.get_y() > b.get_y()){
        if(a.get_y() > c.get_y()){
            return a;
            }
        else return c;
    }
    else{
        if(b.get_y() > c.get_y()){
            return b;
        }
        else return c;
    }
}

Point min_y(const Point& a, const Point& b, const Point& c){ //ritorna il punto di y minore dati 3 punti come argomento
    if (a.get_y() < b.get_y()){
        if(a.get_y() < c.get_y()){
            return a;
            }
        else return c;
    }
    else{
        if(b.get_y() < c.get_y()){
            return b;
        }
        else return c;
    }
}

class Triangle{
    Point v1{0,0}; //i vertici del triangolo
    Point v2{1,1};
    Point v3{1,0};
    Point sx;  //il punto con la x minore
    Point dx;  //il punto con la x maggiore
    Point ay;  //il punto con la y maggiore
    Point my;  //il punto con la minore y
    Point c1;  
    Point c2;  //c1, c2 e c3 sono oggetti di appoggio per il calcolo delle rette, sono impostate in modo che c2 sia il punto di x intermedia
    Point c3;
    int caso{0}; //gestisce i casi: 0 se ay, sx e dx sono distinti, 1 se ay è sia ay che sx, 2 se ay è sia ay che dx
    bool punta_alto; //ci dice se il triangolo punta in alto
    public :
        Triangle(Point a, Point b, Point c) //costruttore
            : v1{a}, v2{b}, v3{c}
        {
        max_y(a,b,c) == a ? ay = a : (max_y(a,b,c) == b ? ay = b : ay = c); //capisce chi sia ay dei 3 punti passati
        min_x(a,b,c) == a ? sx = a : (min_x(a,b,c) == b ? sx = b : sx = c); //idem con sx
        max_x(a,b,c) == a ? dx = a : (max_x(a,b,c) == b ? dx = b : dx = c); //idem con dx
        min_x(a,b,c) == a ? my = a : (min_y(a,b,c) == b ? my = b : my = c); //idem con my
        
        ay == sx ? caso = 1 : (ay == dx ? caso = 2 : caso = 0); //capisce in che caso siamo (riga 94)
        c1 = sx; //assegno c1
        a != sx && a != dx ? c2 = a : (b != sx && b != dx ? c2 = b : c2 = c); //assegno c2 in modo che sia il punto di x medio
        c3 = dx; //assegno c3
        caso == 1 || caso == 2 ? punta_alto = false : punta_alto = true; //capisce se la punta è verso l'alto o verso il basso
        }
        Point get_sx() const {return sx;}
        Point get_dx() const {return dx;}  //metodi get per l'interfaccia 
        Point get_ay() const {return ay;}
        Point get_my() const {return my;}
        Point get_c1() const {return c1;}
        Point get_c2() const {return c2;}
        Point get_c3() const {return c3;}
        bool get_punta() const {return punta_alto;}
        double retta12(double x) const{
            return ((c2.get_y()-c1.get_y())*(x-c1.get_x())/(c2.get_x()-c1.get_x()))+c1.get_y();
        }
        double retta23(double x) const {
            return ((c2.get_y()-c3.get_y())*(x-c3.get_x())/(c2.get_x()-c3.get_x()))+c3.get_y();     //le 3 f(x)
        }
        double retta13(double x) const {
            return ((c3.get_y()-c1.get_y())*(x-c1.get_x())/(c3.get_x()-c1.get_x()))+c1.get_y();
        }
};

bool condition(const Point& a, const Triangle& t){
    if (t.get_punta() == true){
        if(t.get_c1().get_x() == t.get_c2().get_x()){
            return (a.get_y() >= t.retta13(a.get_x()) && a.get_y() <= t.retta23(a.get_x()));
        }
        else if(t.get_c3().get_x() == t.get_c2().get_x()){
            return (a.get_y() >= t.retta13(a.get_x()) && a.get_y() <= t.retta12(a.get_x()));  
        }       
        return (a.get_y() >= t.retta13(a.get_x()) && a.get_y() <= t.retta12(a.get_x()) && a.get_y() <= t.retta23(a.get_x()));   //delimito l'area del triangolo
    }                                                                                                                           //a seconda di dove è diretta la punta
    if(t.get_punta() == false){
        if(t.get_c1().get_x() == t.get_c2().get_x()){
            return (a.get_y() <= t.retta13(a.get_x()) && a.get_y() >= t.retta23(a.get_x()));
        }
        else if(t.get_c3().get_x() == t.get_c2().get_x()){
            return (a.get_y() <= t.retta13(a.get_x()) && a.get_y() >= t.retta12(a.get_x()));
        }
        return (a.get_y() <= t.retta13(a.get_x()) && a.get_y() >= t.retta12(a.get_x()) && a.get_y() >= t.retta23(a.get_x()));
    }
    return true; //return a buffo messo per evitare un warning
}

int main(){
    double a;
    double b;
    double c;   //variabili per recepire i punti
    double d;
    double e;
    double f;
    std::cout << "bello, sembra un programma semplice ma sono 200 righe di codice e tante bestemmie" << '\n'<< "inserisci i vertici immettendo in ordine x e y" << '\n';
    std::cout << "vertice 1: (X-Y)" << '\n';
    std::cin >> a >> b;
    std::cout << "vertice 2: (X-Y)" << '\n';
    std::cin >> c >> d;
    std::cout << "vertice 3: (X-Y)" << '\n';
    std::cin >> e >> f;
    Point v1{a,b};
    Point v2{c,d};
    Point v3{e,f};
    Triangle t{v1,v2,v3}; //inizializzo punti e triangoli

    std::vector<Point> vett;

    for(double i = static_cast<int>(t.get_my().get_y()); i <= t.get_ay().get_y(); ++i){
        for(double j = static_cast<int>(t.get_sx().get_x()); j <= t.get_dx().get_x(); ++j){     //i e j sono double solo per evitare un warning
            Point p{j,i};   
            if(condition(p,t)){
                vett.push_back(p);                  //ogni ciclo crea un punto di coordinate j,i che viene valutato da condition()...
            }                                       //...e se questa dà true lo salva in un vettore
        }
    }
    for(int i = 0; i < vett.size(); ++i){
    std::cout << vett[i].get_x() << "," << vett[i].get_y() << "    ";
    }
    std::cout << "bello, il triangolone che hai inserito contiene " << vett.size() << " punti con coordinate intere" << '\n'; 
    std::cout << '\n';
}
//maruann
