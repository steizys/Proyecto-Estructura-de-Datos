#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

struct Carta{ //Nodos de cartas 
    string nombre;
    int valor;
    string pinta;
    Carta *next;
};
struct Jugador{// Nodos de Jugador
    int nombre;
    Jugador *next;
    Carta *lista_cartas; //Multilista que une a cada jugador con sus cartas
};

void InsertarJugador(Jugador **p, int valor){ //Llenar jugadores por cola
    Jugador* nuevoJugador = new Jugador;
    nuevoJugador->nombre= valor;
    nuevoJugador->next= NULL;
    nuevoJugador->lista_cartas= NULL;
    if (!(*p)){ // Si la lista está vacía
        *p = nuevoJugador; // Inserta directamente
    }else{
        Jugador *aux = *p;
        while (aux->next){ // Itera hasta el último nodo
            aux = aux->next;
        }
        aux->next = nuevoJugador; // Inserta al final
    }

};
void CrearCarta(Carta **p, string nombre, int valor, string pinta ){ //Procedimiento para Crear las cartas del mazo
    Carta* nuevo_carta = new Carta;
    nuevo_carta->nombre= nombre;
    nuevo_carta->valor= valor;
    nuevo_carta->pinta= pinta;
    nuevo_carta->next= NULL;
    if (!(*p)){ // Si la lista está vacía
        *p = nuevo_carta; // Inserta directamente
    }else{
        Carta *aux = *p;
        while (aux->next){ // Itera hasta el último nodo
            aux = aux->next;
        }
        aux->next = nuevo_carta; // Inserta al final
    }

};
Jugador *BuscarJugador (Jugador *malla, int i){ //Busca el nodo del jugador por su nombre
    while (malla){
        if (malla->nombre==i){
            return malla;
        }
        malla=malla->next;
    }
    return NULL;
};

int ContarCartas(Carta* cartas){//Contar las cartas que tiene cada jugador
    int ncartas=0;
    while(cartas){
        ncartas++;
        cartas=cartas->next;
    }
    return ncartas;
};
void RepartirCarta(Carta **mazo, Jugador **malla) {  //Reparte de forma aleatoria las cartas del mazo a los jugadores
    srand(time(NULL)); // Inicializar la semilla una vez

    while (*mazo) { 
        Carta *carta = *mazo;
        int i = rand() % 4 + 1;
        Jugador *jugador = BuscarJugador(*malla, i);
        cout << "Numero random " << i << endl;
        cout << "Jugador " << jugador->nombre<< endl;
        if (ContarCartas(jugador->lista_cartas) < 14) {
            cout<<"Numero de Cartas "<<ContarCartas(jugador->lista_cartas)<<endl;
            //AsignarCarta(&(jugador->lista_cartas), carta);
        }
        *mazo = (*mazo)->next; 
    }
}
void MostrarJugador(Jugador *p){
    cout << "P->";
    while (p){
        cout << "[" << p->nombre<< "]-> ";
        p = p->next;
    }
    cout <<"NULL"<<endl;
};
void MostrarCarta(Carta *p){
    while (p){
        cout << p->nombre<< " | "<< p->pinta<< " | "<< p->valor<<endl;
        p = p->next;
    }
};


///////////////////////////////////////////////////
///Insertar Sublista (Para Probar)
void SubLista(Carta **sublist, string nombre, int valor, string pinta)
{
    Carta *newcarta = new Carta;
    newcarta->nombre= nombre;
    newcarta->valor= valor;
    newcarta->pinta= pinta;
    newcarta->next = *sublist;
    *sublist = newcarta;
}
void InsertarCarta(Jugador *malla , int nombrej, string nombre, int valor, string pinta){
    Jugador *jugador = BuscarJugador(malla, nombrej); ////Me da el nodo del jugador al que quiero insertar una carta 
    SubLista(&(jugador->lista_cartas),nombre, valor, pinta);
};
////////////////////////////////////////////////////
int main(){
    cout<<"Proyecto 1"<<endl;
    cout<<"Autoras: Amelie Moreno"<<endl;
    cout<<"         Gabriela Cantos"<<endl;
    cout<<"         Steizy Fornica"<<endl;

    Jugador *Malla = NULL;
    Carta *Mazo = NULL;

    InsertarJugador(&Malla,1);
    InsertarJugador(&Malla,2);
    InsertarJugador(&Malla,3);
    InsertarJugador(&Malla,4);
    MostrarJugador(Malla);
    InsertarCarta(Malla , 1, "3",1, "diamante");
    InsertarCarta(Malla , 1, "3",1, "picas");
    CrearCarta(&Mazo,"3",1, "diamante");
    CrearCarta(&Mazo,"3",1, "picas");
    CrearCarta(&Mazo,"3",1, "trebol");
    MostrarCarta(Mazo);
    RepartirCarta(&Mazo, &Malla);

    system("pause");

    return 0;
}