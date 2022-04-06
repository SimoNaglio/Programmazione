#include <iostream>
#include <cmath>

//La questione è questa: si immagina una navetta, dotata di riserve energetiche idelmente inesauribili, che parte nel punto più alto dell'atmosfera terrestre.
//La navetta percorre poi una serie di gusci sferici concentrci discendendo verso il suolo, senza attrito.
//Scendendo, per tenere traccia del percorso compiuto, la navette "brucia" l'atmosfera, che, idealmente, non si rimescola
//Ogni guscio ha raggio pari a (raggio totale - altezza nave)
//La navetta copre ogni guscio sferico percorrendo un numero di circonferenze pari a (raggio totale / larghezza nave)
//La velocità della naviietta è non relativistica e possibilmente simile a quelle raggiungibili con le attuali tecnologie
//Ciò che si vuole determinare è il tempo necessario a percorrere tutta la strada fino al suolo
//Un'idea era fissare il tempo di percorrenza del guscio più esterno (r = 500 km + R_terra) a poco meno di un anno
//Non sarebbe male se il tempo totale di percorrenza fosse compreso nella durata media di una vita umana 
//
//Ho provato ad eseguire i calcoli del tempo in due modi: 
//il primo, applicando il metodo descritto sopra (che richiederebbe una sommatoria, eseguita qui con un loop)
//il secondo, calcolando il volume della navetta (supposta per comodità rettangolare) e dell'atmosfera, eseguendo il 
    //rapporto tra le due e ricalcolando la velocità del primo metodo per renderla una sorta di velocità volumica 
    //la nuova velocità (ma questo è frutto di una supposizione particolarmente labile) dovrebbe essere v= (v / lunghezza nave)

//Due adesso sono i punti critici:
// 1] i due codici (entrambi qui sotto) portano a due risultati diversi per molti ordini di grandezza
// 2] non mi è chiaro se le ipotesi di partenza in merito a tempi e velocità confliggano

//nota: i codici compilano perfettamente ma, visti i numeri, la prima parte può richiedere un paio di decine di secondi per essere eseguita




int main (){

int R{6371000}; //Earth radius in [m]
double pi{std::acos(-1)};
int s_to_y{3600 * 24 * 365}; //conversion from seconds to years

std::cout << "Insert, in order, the width of the ship[m], its height[m], its starting altitude from soil[m] and its speed[m/s]: ";
int w_ship;
int h_ship;
int r;
int v;
std::cin >> w_ship >> h_ship >> r >> v;

int r2 = r;

double T{};
for (int i{}; i != r; ++i) { 
  double S = (2 * pi * pi * (R + r - h_ship) * (R + r - h_ship))/w_ship; // s = area of every spheric shell = current circumference - current number of passages
  r -= h_ship;
  double t = S/v; //note that S has dimensions of a lenght and not an area 
  T += t;
};

T /= s_to_y;


std::cout << "Here's the time the ship employs to completely burn the atmosphere: "<< T << " y." <<'\n';

//~~~~~~~~~~~~~~~~~~~~~~OTHER METHOD~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

std::cout << "To see a simpler model, insert also the lenght of the ship[m]: ";
int l_ship;

std::cin >> l_ship;

int V_ship = l_ship * w_ship * h_ship; //volume of the ship

double V_atmo = - (4 * r2 * pi / 3) * (3 * R * R + 3 * R * r2 + r2 * r2); // volume of atmosphere = (total volume - volume of Earth)

double n = V_atmo/V_ship;

double t2 = n/(v/l_ship);

t2 /= s_to_y;

std::cout << "The ship stays in the atmosphere " << n << " times and employs " << t2 << " years to burn it." << '\n';

}


